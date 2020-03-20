/*
 * Param.h
 *
 *  Created on: 18 mars 2020
 *      Author: ludovic
 */

#ifndef LIB_PARAMETER_H_
#define LIB_PARAMETER_H_

#include <string>

using namespace std;

class ParameterInterface{
public:
    virtual ~ParameterInterface() {};
    virtual bool someFunction() {return true;}

};

template <typename AType>
class Parameter : public ParameterInterface {
public:
    //Param(string name);
    Parameter(string name, AType value);
    ~Parameter(void);
    bool someFunction() {return false;}
    //Param & operator=(const Param& other) const;
    bool operator==(const Parameter& other) const;

private:
    string m_name;
    AType m_value;
};

#endif /* LIB_PARAMETER_H_ */
