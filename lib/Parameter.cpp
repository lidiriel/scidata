/*
 * Param.cpp
 *
 *  Created on: 18 mars 2020
 *      Author: ludovic
 */

#include "Parameter.h"

using namespace std;

//template <class T>
//Param<T>::Param(string name):
//    m_name(name){
//
//}

template <typename AType>
Parameter<AType>::Parameter(string name, AType value) :
            m_name(name), m_value(value){

}

template <typename AType>
Parameter<AType>::~Parameter(void) {
    // TODO Auto-generated destructor stub
}

template <typename AType>
bool Parameter<AType>::operator==(const Parameter& other) const{
    if(this->m_name.compare(other.m_name) == 0)
        return true;
    else
        return false;
}
