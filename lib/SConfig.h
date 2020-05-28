/*
 * SConfig.h
 *
 * Author: ludovic leau-mercier
 * Licence: GPLv3 see LICENSE file in source repository
 */

#ifndef SCONFIG_H_
#define SCIDATA_SCONFIG_H_

#include <string>
#include <memory>
#include <vector>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "SParameterSet.h"
#include "SInputData.h"

using namespace std;
namespace logging = boost::log;

class SConfig {
public:
    SConfig(logging::trivial::severity_level loglevel);
    SConfig(void);
    virtual ~SConfig();
    void read(string filename);
    void read(string filename, string defaultnameset);
    void load(string filename, string defaultinput);
    void show();
    SParameterSet getParameterSet(string setname);
    SInputData getInputData(string name);
private:
    logging::trivial::severity_level m_log_level;
    vector<SParameterSet> m_parameterSetVector;
    vector<SInputData> m_inputDataVector;
};

#endif /* SCIDATA_SCONFIG_H_ */
