/*
 * ParameterSet.cpp
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */
#include <vector>
#include <memory>
#include <iostream>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/log/trivial.hpp>
#include "ParameterSet.h"
#include "Parameter.h"

using namespace std;

ParameterSet::ParameterSet() {
}

ParameterSet::ParameterSet(string name):
            m_nameset(name){
}

ParameterSet::ParameterSet(const ParameterSet& other){
    m_nameset = other.m_nameset;
    // begin deep copy code:
    m_params.reserve(m_params.size()); // optional to improve performance
    for(auto& ptr : other.m_params)
        m_params.emplace_back( new ParameterInterface(*ptr) );
        //m_params.push_back(move(ptr));
}

ParameterSet::~ParameterSet() {
}

//ParameterSet& ParameterSet::operator=(const ParameterSet& other) {
//
//    m_nameset = other.m_nameset;
//}

bool ParameterSet::operator==(const ParameterSet& other) const{
    if(this->m_nameset.compare(other.m_nameset) == 0)
        return true;
    else
        return false;
}

void ParameterSet::appendInteger(string name, long value) {
    //m_params.emplace_back(new Parameter<long>(name, value));
}

void ParameterSet::appendString(string name, string value) {

}

string ParameterSet::getString(string name){
//    std::vector<Param>::iterator it;
//    it = find(m_params.begin(), m_params.end(), Param(name));
//    if (it != m_params.end()){
//        return it.get;
//    }else{
//        BOOST_LOG_TRIVIAL(debug) << "param not found : " << name;
//    }
//    return ParameterSet();
    return string("");
}

long getInteger(string name){
    return 0;
}


