/*
 * TestConfig.cpp
 *
 *  Created on: 16 mars 2020
 *      Author: ludovic
 */

#define BOOST_TEST_MODULE Config
#include <iostream>
#include <exception>
#include <limits>
#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

#include "config/global_build_config.h"
#include "../lib/SConfig.h"
#include "SParameterSet.h"


using namespace std;
namespace logging = boost::log;

BOOST_AUTO_TEST_SUITE(SuiteBasics)

BOOST_AUTO_TEST_CASE(FileNotExist)
{
    try{
        SConfig foo;
        foo.read("invalid.xml");
    }catch(logic_error & e){
        BOOST_CHECK_EQUAL(e.what(), "Invalid filename : invalid.xml");
    }
}

BOOST_AUTO_TEST_CASE(ParameterSetNoTitle)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    SConfig foo;
    foo.read(testdatapath.string(), "notitle");
    auto paramSet = foo.getParameterSet("notitle");
}

BOOST_AUTO_TEST_CASE(ParameterSetConductivity)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    SConfig foo;
    foo.read(testdatapath.string(), "conductivity");
    auto paramSet = foo.getParameterSet("conductivity");
    BOOST_CHECK_EQUAL(paramSet.getNameset(),"conductivity");
    BOOST_CHECK_EQUAL(paramSet.getTitle(),"conductivity title");
}

bool unknowTypeMsg(const std::logic_error& ex)
{
    BOOST_CHECK_EQUAL(ex.what(), std::string("Unknow type in parameterset unknowtype type = OohAah"));
    return true;
}

BOOST_AUTO_TEST_CASE(ParameterSetUnknowType)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    SConfig foo;
    BOOST_CHECK_EXCEPTION(foo.read(testdatapath.string(), "unknowtype"), std::logic_error, unknowTypeMsg);
}

BOOST_AUTO_TEST_CASE(ParameterSetBasicType)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    SConfig foo(logging::trivial::debug);
    foo.read(testdatapath.string(), "basictype");
    auto paramSet = foo.getParameterSet("basictype");
    BOOST_CHECK_EQUAL(paramSet.getNameset(), "basictype");
    BOOST_CHECK_EQUAL(paramSet.getString("astring"),"accessing to example texte !");
    BOOST_CHECK( paramSet.getInteger("aninteger") == 32);
    BOOST_CHECK( paramSet.getInteger("anintegerwithunit") == 3);
    BOOST_CHECK_CLOSE(paramSet.getReal("areal"),3300.89,numeric_limits<double>::epsilon());
    BOOST_CHECK_CLOSE(paramSet.getReal("arealwithunit"),38.56,numeric_limits<double>::epsilon());
    BOOST_CHECK_CLOSE(paramSet.getReal("arealscientific"),1.234E8,numeric_limits<double>::epsilon());
    BOOST_CHECK(paramSet.getLogical("aboolean1"));
    BOOST_CHECK(paramSet.getLogical("aboolean2"));
    BOOST_CHECK(!paramSet.getLogical("aboolean3"));
    BOOST_CHECK(!paramSet.getLogical("aboolean4"));
}

BOOST_AUTO_TEST_SUITE_END()

