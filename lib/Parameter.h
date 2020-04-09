/*
 * Param.h
 *
 *  Created on: 18 mars 2020
 *      Author: ludovic
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include <string>

using namespace std;

class ParameterInterface{
public:
    virtual ~ParameterInterface() {};
    virtual bool someFunction() {return true;}

};

template <class AType>
class Parameter : public ParameterInterface {
public:
    Parameter(){

    }

    Parameter(string name, AType value) : m_name(name), m_value(value){

    }

    ~Parameter(void){

    }

    bool someFunction() {return false;}

    bool operator==(const Parameter& other) const {
        if(this->m_name.compare(other.m_name) == 0)
            return true;
        else
            return false;
    }

private:
    string m_name;
    AType m_value;
};


#endif /* PARAMETER_H_ */
