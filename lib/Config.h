/*
 * Config.h
 *
 *      Author: ludovic leau-mercier
 *     Licence: see LICENSE file in source repository
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <memory>
#include <vector>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "DataDescription.h"
#include "ParameterSet.h"

using namespace std;
namespace logging = boost::log;

class Config {
public:
    Config(logging::trivial::severity_level loglevel);
    Config(void);
    virtual ~Config();
    void read(string filename);
    void read(string filename, string defaultnameset);
    void show();
    shared_ptr<DataDescription> getInputDataDescription(string dataname);
    ParameterSet getParameterSet(string setname);
private:
    logging::trivial::severity_level m_log_level;
    vector<ParameterSet> m_parameterSetVector;
};

#endif /* CONFIG_H_ */
