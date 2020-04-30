/*
 * ParameterSet.h
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */

#ifndef PARAMETERSET_H_
#define PARAMETERSET_H_

#include <string>
#include <vector>
#include <memory>
#include "Parameter.h"

using namespace std;

class ParameterSet {
public:
    ParameterSet();
    ParameterSet(string name);
    //ParameterSet(const ParameterSet& other);
    virtual ~ParameterSet();

    //ParameterSet& operator=(const ParameterSet& other);
    bool operator==(const ParameterSet& other) const;

    void setNameset(string name) { m_nameset = name; }
    string getNameset(){ return m_nameset; }

    void setTitle(string title) { m_title = title; }
    string getTitle() { return m_title; }

    //void getInterface(string name, shared_ptr<ParameterInterface>  & ptr);
    string getString(string name);
    long getInteger(string name);
    double getReal(string name);
    bool getLogical(string name);
    template <class RType> RType getValue(string name);

    void appendLogical(string name, bool value);
    void appendReal(string name, double value);
    void appendInteger(string name, long value);
    void appendString(string name, string value);

private:
    string m_nameset;
    string m_title;
    vector<shared_ptr<ParameterInterface>> m_paramObjects;
    vector<shared_ptr<ParameterInterface> >::iterator getIterator(const string &name);
};

#endif /* PARAMETERSET_H_ */
