/*
 * Config.h
 *
 * Author: ludovic leau-mercier
 * Licence: GPLv3 see LICENSE file in source repository
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <memory>
#include <vector>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "ParameterSet.h"
#include "InputData.h"

using namespace std;
namespace logging = boost::log;

class Config {
public:
    Config(logging::trivial::severity_level loglevel);
    Config(void);
    virtual ~Config();
    void read(string filename);
    void read(string filename, string defaultnameset);
    void load(string filename, string defaultinput);
    void show();
    ParameterSet getParameterSet(string setname);
    InputData getInputData(string name);
private:
    logging::trivial::severity_level m_log_level;
    vector<ParameterSet> m_parameterSetVector;
    vector<InputData> m_inputDataVector;
};

#endif /* CONFIG_H_ */
