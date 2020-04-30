/*
 * ParameterSet.cpp
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
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
/*
ParameterSet::ParameterSet(const ParameterSet& other){
    m_nameset = other.m_nameset;
    m_title = other.m_title;
    // begin deep copy code:
    m_params.reserve(m_params.size()); // optional to improve performance
    for(auto& ptr : other.m_params)
        m_params.emplace_back( new ParameterInterface(*ptr) );
    //m_params.push_back(move(ptr));
}
 */

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

void ParameterSet::appendLogical(string name, bool value) {
    BOOST_LOG_TRIVIAL(debug)<<"call append integer";
    m_paramObjects.push_back(make_shared<Parameter<bool>>(name, value));
}

void ParameterSet::appendReal(string name, double value) {
    BOOST_LOG_TRIVIAL(debug)<<"call append integer";
    m_paramObjects.push_back(make_shared<Parameter<double>>(name, value));
}

void ParameterSet::appendInteger(string name, long value) {
    BOOST_LOG_TRIVIAL(debug)<<"call append integer";
    m_paramObjects.push_back(make_shared<Parameter<long>>(name, value));
}

void ParameterSet::appendString(string name, string value) {
    BOOST_LOG_TRIVIAL(debug)<<"call append string";
    shared_ptr<ParameterInterface> ptr(nullptr);
    m_paramObjects.push_back(make_shared<Parameter<string>>(name, value));
}

string ParameterSet::getString(string name){
    return getValue<string>(name);
}

long ParameterSet::getInteger(string name){
    return getValue<long>(name);
}

double ParameterSet::getReal(string name){
    return getValue<double>(name);
}

bool ParameterSet::getLogical(string name){
    return getValue<bool>(name);
}

template <class RType>
RType ParameterSet::getValue(string name){
    vector<shared_ptr<ParameterInterface> >::iterator it = getIterator(name);
    shared_ptr<Parameter<RType>> p = static_pointer_cast<Parameter<RType>>(*it);
    RType value;
    if(p != nullptr){
        BOOST_LOG_TRIVIAL(debug)<<"value="<<p->getValue();
        value = p->getValue();
    }else{
        BOOST_LOG_TRIVIAL(error)<<"null ptr";
        throw logic_error("null pointer in getString !");
    }
    return value;
}

vector<shared_ptr<ParameterInterface> >::iterator ParameterSet::getIterator(
        const string &name) {
    vector<shared_ptr<ParameterInterface> >::iterator it =
            m_paramObjects.begin();
    for (; it != m_paramObjects.end(); ++it) {
        if (name.compare((*it)->getName()) == 0) {
            BOOST_LOG_TRIVIAL(debug)
                    << name << " entry found";
            break;
        }
    }
    if (it == m_paramObjects.end()) {
        throw logic_error("param " + name + " not found.");
    }
    return it;
}


