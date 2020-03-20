/*
 * Config.h
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <memory>
#include <vector>

using namespace std;

#include "DataDescription.h"
#include "ParameterSet.h"

//typedef shared_ptr<ParameterSet> ptrParameterSet;

class Config {
public:
    Config(string filename);
    virtual ~Config();
    shared_ptr<DataDescription> getInputDataDescription(string dataname);
    ParameterSet getParameterSet(string setname);
private:
    vector<ParameterSet> m_parameterSetVector;
};

#endif /* CONFIG_H_ */
