/*
 * ParameterSet.cpp
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */
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

ParameterSet::~ParameterSet() {
}

bool ParameterSet::operator==(const ParameterSet& other) const{
    if(this->m_nameset.compare(other.m_nameset) == 0)
        return true;
    else
        return false;
}

void ParameterSet::appendInteger(string name, long value) {
    m_params.emplace_back(new Parameter<long>(name, value));
}

//string ParameterSet::getString(string name){
//    std::vector<Param>::iterator it;
//    it = find(m_params.begin(), m_params.end(), Param(name));
//    if (it != m_params.end()){
//        return it.get;
//    }else{
//        BOOST_LOG_TRIVIAL(debug) << "param not found : " << name;
//    }
//    return ParameterSet();
//}

long getInteger(string name){
    return 0;
}


