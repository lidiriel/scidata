/*
 * SParameter.h
 *
 * Author: ludovic leau-mercier
 * Licence: GPLv3 see LICENSE file in source repository
 */

#ifndef SCIDATA_SPARAMETER_H_
#define SCIDATA_SPARAMETER_H_

#include <string>

using namespace std;

class ParameterInterface{
public:
//    ParameterInterface(){};
    ParameterInterface(string name) : m_name(name) {};
    virtual ~ParameterInterface() {};

    virtual void foo() = 0;

    string getName() { return m_name; }
    void setName(string name) { m_name = name; }
    string getUnit() { return m_unit; }
    void setUnit(string unit) { m_unit = unit; }

/*
    bool operator==(const ParameterInterface& other) const {
        if(this->m_name.compare(other.m_name) == 0)
            return true;
        else
            return false;
    }
    */
private:
    string m_name;
    string m_unit;
};

template <class AType>
class SParameter : public ParameterInterface {
public:
/*
    Parameter(string name) : ParameterInterface(name) {
    }
*/
    SParameter(string name, AType value) : ParameterInterface(name), m_value(value){
    }

  //  ~Parameter(void){
  //  }

    virtual void foo(){ return; };

    AType getValue(){ return m_value; }

//    Parameter<AType>& operator=(const Parameter<AType>& other){
//        //setName(other.getName());
//        m_value = other.m_value;
//        return *this;
//    }


private:
    AType m_value;
};

template class SParameter<string>;
template class SParameter<long>;

#endif /* SCIDATA_SPARAMETER_H_ */
