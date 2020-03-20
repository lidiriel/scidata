/*
 * Config.cpp
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */
#include <memory>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/log/trivial.hpp>
#include "ParameterSet.h"
#include "Config.h"

#include "Parameter.h"

using namespace std;
using boost::property_tree::ptree;
//using namespace boost::log::trivial;

Config::Config(string filename) {
    // Create empty property tree object
    ptree tree;
    // Parse the XML into the property tree.
    read_xml(filename, tree);
    BOOST_LOG_TRIVIAL(debug)<<"XML filename : "<<filename;
    for(auto it: tree.get_child("experiment")){
    string tree_balise = it.first; //child_tree.first;
        if (tree_balise.compare("parameterset") == 0){
            string nameset = it.second.get<string>("<xmlattr>.nameset");
            BOOST_LOG_TRIVIAL(debug)<<"XML parameterset nameset : "<<nameset;
            string title = it.second.get<string>("<xmlattr>.title");
            ParameterSet current(nameset);
            current.setTitle(title);
            // list param
            for(auto it2: it.second){
                tree_balise = it2.first; //child_tree.first;
                if(tree_balise.compare("param") == 0){
                    string name = it2.second.get<string>("<xmlattr>.name");
                    BOOST_LOG_TRIVIAL(debug)<<"XML param name : "<<name;
                    string type = it2.second.get<string>("<xmlattr>.type");

                    if(type == "string"){
//                        shared_ptr<Param<string>> ptrParam;
//                        string value =  it2.second.get_value<string>();
//                        ptrParam = new Param<string>(name,value);
                    }
                    if(type == "integer"){
//                        long value = it2.second.get_value<long>();
//                        shared_ptr<Param<long>> ptrParam(new Param<long>(name,value));
//                        //current.appendIntegerParam(*ptrParam);
                    }

                }
            }
            m_parameterSetVector.push_back(current);
        }
    }
}

Config::~Config() {
    // TODO Auto-generated destructor stub
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
