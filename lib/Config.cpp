/*
 * Config.cpp
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "Config.h"
#include "ParameterSet.h"
#include "Parameter.h"

using namespace std;
namespace logging = boost::log;
namespace pt = boost::property_tree;

Config::Config(logging::trivial::severity_level loglevel) : m_log_level(loglevel)
{
    logging::core::get()->set_filter(
            logging::trivial::severity >= m_log_level
    );
}

Config::Config(void) : Config(logging::trivial::info) {
}

Config::~Config() {
}

void Config::read(string filename){
    //TODO
}

void Config::read(string filename, string defaultnameset){
    // Create empty property tree object
    pt::ptree tree;
    // Parse the XML into the property tree.
    BOOST_LOG_TRIVIAL(debug)<<"XML filename : "<<filename;
    if(!boost::filesystem::exists(filename)){
        throw logic_error("Invalid filename : "+filename);
    }
    try{
        read_xml(filename, tree);
    }catch(...){
        throw logic_error("Error reading file : "+filename);
    }
    for(auto it: tree.get_child("experiment")){
        string tree_balise = it.first; //child_tree.first;
        if (tree_balise.compare("parameterset") == 0){
            string nameset = it.second.get<string>("<xmlattr>.nameset");
            BOOST_LOG_TRIVIAL(debug)<<"XML parameterset nameset : "<<nameset;
            if(defaultnameset.compare(nameset)){
                ParameterSet current(nameset);
                try{
                    string title = it.second.get<string>("<xmlattr>.title");
                    current.setTitle(title);
                }catch(exception & e){
                    BOOST_LOG_TRIVIAL(warning)<<"nameset : "<<nameset<<" has no title";
                }
                // list param
                for(auto it2: it.second){
                    tree_balise = it2.first; //child_tree.first;
                    if(tree_balise.compare("param") == 0){
                        string name = it2.second.get<string>("<xmlattr>.name");
                        BOOST_LOG_TRIVIAL(debug)<<"XML param name : "<<name;
                        string type = it2.second.get<string>("<xmlattr>.type");
                        bool typeUnknown = true;
                        if(type.compare("string")){
                            string value =  it2.second.get_value<string>();
                            current.appendString(name, value);
                            typeUnknown = false;
                        }
                        if(type.compare("integer")){
                            //long value = it2.second.get_value<long>();
                            //current.appendInteger(name, value);
                            typeUnknown = false;
                        }
                        if(typeUnknown){
                            throw logic_error("Unknow type in parameterset "+nameset+" type = "+type);
                        }
                    }
                }
                m_parameterSetVector.push_back(current);
            }
        }
    }
}

void Config::show(){
    //TODO
    cout<<"show config"<<endl;
}


shared_ptr<DataDescription> Config::getInputDataDescription(string dataname){
    shared_ptr<DataDescription> ptr(new DataDescription());
    return ptr;
}

ParameterSet Config::getParameterSet(string setname){
    std::vector<ParameterSet>::iterator it;
    it = find(m_parameterSetVector.begin(), m_parameterSetVector.end(), ParameterSet(setname));
    if (it != m_parameterSetVector.end()){
        return *it;
    }else{
        BOOST_LOG_TRIVIAL(debug) << "parameterset not found : " << setname;
    }
    return ParameterSet();
}
