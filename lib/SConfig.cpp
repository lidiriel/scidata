/*
 * Config.cpp
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */
#include "SConfig.h"

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
#include <boost/algorithm/string.hpp>

#include "SParameterSet.h"
#include "SParameter.h"
#include "SInputData.h"

using namespace std;
namespace logging = boost::log;
namespace pt = boost::property_tree;

SConfig::SConfig(logging::trivial::severity_level loglevel) : m_log_level(loglevel)
{
    logging::core::get()->set_filter(
            logging::trivial::severity >= m_log_level
    );
}

SConfig::SConfig(void) : SConfig(logging::trivial::info) {
}

SConfig::~SConfig() {
}

void SConfig::load(string filename, string defaultinput){
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
        if (tree_balise.compare("inputdata") == 0){
            boost::filesystem::path  dir, file;
            string name = it.second.get<string>("<xmlattr>.name");
            BOOST_LOG_TRIVIAL(debug)<<"XML inputdata name : "<<name;
            if(defaultinput.compare(name) == 0){
                SInputData current(name);
                try{
                    string structure = it.second.get<string>("<xmlattr>.structure");
                    current.setStructure(structure);
                }catch(exception & e){
                    BOOST_LOG_TRIVIAL(warning)<<"name : "<<name<<" has no structure";
                }

                for(auto it2: it.second){
                    tree_balise = it2.first; //child_tree.first;
                    if(tree_balise.compare("inputdatadir") == 0){
                        dir = boost::filesystem::path(it2.second.get_value<string>());
                    }
                    if(tree_balise.compare("inputfile") == 0){
                        file = boost::filesystem::path(it2.second.get_value<string>());
                    }
                    if(tree_balise.compare("separator") == 0){
                        current.setSeparator(it2.second.get_value<string>());
                    }
                    if(tree_balise.compare("locale") == 0){
                        current.setLocale(it2.second.get_value<string>());
                    }
                    if(tree_balise.compare("header") == 0){
                        current.setHeaderLineNumber(it2.second.get<int>("<xmlattr>.line"));
                    }
                    if(tree_balise.compare("comments") == 0){
                        current.setCommentsStartWith(it2.second.get<string>("<xmlattr>.startwith"));
                    }
                    if(tree_balise.compare("column") == 0){
                        string name = it2.second.get<string>("<xmlattr>.name");
                        BOOST_LOG_TRIVIAL(debug)<<"XML column name : "<<name;
                        string type = it2.second.get<string>("<xmlattr>.type");
                        shared_ptr<ColumnInterface> pColInterface = current.createColumn(name, type);
                        try {
                            string comment = it2.second.get<string>("<xmlattr>.comment");
                            pColInterface->setComment(comment);
                        }catch(exception & e){
                            BOOST_LOG_TRIVIAL(warning)<<"column : "<<name<<" has no comment";
                        }
                        try {
                            string unit = it2.second.get<string>("<xmlattr>.unit");
                            pColInterface->setUnit(unit);
                        }catch(exception & e){
                            BOOST_LOG_TRIVIAL(warning)<<"column : "<<name<<" has no unit";
                        }
                    }
                }
                dir /= file;
                current.setFile(dir);
                m_inputDataVector.push_back(current);
            }
        }
    }

}

void SConfig::read(string filename){
    //TODO
}

void SConfig::read(string filename, string defaultnameset){
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
            if(defaultnameset.compare(nameset) == 0){
                SParameterSet current(nameset);
                try{
                    string title = it.second.get<string>("<xmlattr>.title");
                    BOOST_LOG_TRIVIAL(debug)<<"XML parameterset title : "<<title;
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
                        if(type.compare("string") == 0){
                            string value =  it2.second.get_value<string>();
                            current.appendString(name, value);
                            typeUnknown = false;
                        }
                        if(type.compare("integer") == 0){
                            long value = it2.second.get_value<long>();
                            current.appendInteger(name, value);
                            typeUnknown = false;
                        }
                        if(type.compare("real") == 0){
                            double value = it2.second.get_value<double>();
                            current.appendReal(name, value);
                            typeUnknown = false;
                        }
                        if(type.compare("logical") == 0){
                            string value = it2.second.get_value<string>();
                            boost::to_upper(value);
                            if(value.compare("TRUE") or value.compare("FALSE")){
                                current.appendLogical(name, value.compare("TRUE") == 0);
                            }else{
                                logic_error("Invalid boolean value "+value);
                            }
                            typeUnknown = false;
                        }
                        if(typeUnknown){
                            throw logic_error("Unknow type in parameterset "+nameset+" type = "+type);
                        }
                    }
                }// end for list param
                m_parameterSetVector.push_back(current);
            } // end if(defaultnameset.comapre
        }
    }
}

void SConfig::show(){
    //TODO
    cout<<"show config"<<endl;
}


//shared_ptr<DataDescription> Config::getInputDataDescription(string dataname){
//    shared_ptr<DataDescription> ptr(new DataDescription());
//    return ptr;
//}

SInputData SConfig::getInputData(string name){
    std::vector<SInputData>::iterator it;
    BOOST_LOG_TRIVIAL(debug) << "nb inputdata "<<m_inputDataVector.size();
    it = find(m_inputDataVector.begin(), m_inputDataVector.end(), SInputData(name));
    if (it != m_inputDataVector.end()){
        return *it;
    }else{
        BOOST_LOG_TRIVIAL(info) << "getInputData() : not found : " << name;
    }
    return SInputData();
}

SParameterSet SConfig::getParameterSet(string setname){
    std::vector<SParameterSet>::iterator it;
    BOOST_LOG_TRIVIAL(debug) << "nb parameterset "<<m_parameterSetVector.size();
    it = find(m_parameterSetVector.begin(), m_parameterSetVector.end(), SParameterSet(setname));
    if (it != m_parameterSetVector.end()){
        return *it;
    }else{
        BOOST_LOG_TRIVIAL(info) << "getParameterSet() : not found : " << setname;
    }
    return SParameterSet();
}
