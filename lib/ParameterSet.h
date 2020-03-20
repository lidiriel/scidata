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
    virtual ~ParameterSet();
    bool operator==(const ParameterSet& other) const;

    void setNameset(string name) { m_nameset = name; }
    string getNameset(){ return m_nameset; }

    void setTitle(string title) { m_title = title; }
    string getTitle() { return m_title; }

    //string getString(string name);
    long int getInteger(string name);
    double getReal(string name);

    void appendInteger(string name, long value);

private:
    string m_nameset;
    string m_title;
    vector<std::unique_ptr<ParameterInterface>> m_params;

};

#endif /* PARAMETERSET_H_ */
