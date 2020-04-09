/*
 * TestConfig.cpp
 *
 *  Created on: 16 mars 2020
 *      Author: ludovic
 */

#define BOOST_TEST_MODULE Config
#include <iostream>
#include <exception>
#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

#include "config/global_build_config.h"
#include "Config.h"
#include "ParameterSet.h"


using namespace std;
namespace logging = boost::log;

BOOST_AUTO_TEST_SUITE(Suite1)

//struct ConfigTestFixture
//{
//    ConfigTestFixture()
//    : m_configFile("test.tmp")
//    {
//        // TODO: Common set-up each test case here.
//        fclose( fopen(m_configFile.c_str(), "w+") );
//    }
//
//    ~ConfigTestFixture()
//    {
//        // TODO: Common tear-down for each test case here.
//        remove(m_configFile.c_str());
//    }
//
////    // TODO: Possibly put some common tests.
////    void TestSaveLoad(CMyFoo& foo, bool asBinary)
////    {
////        BOOST_CHECK(foo.Save(asBinary));
////    }
//
//    // TODO: Declare some common values accesses in tests here.
//    string m_configFile;
//};

//BOOST_FIXTURE_TEST_SUITE(ConfigTest, ConfigTestFixture);

BOOST_AUTO_TEST_CASE(FileNotExist)
{
    try{
        Config foo;
        foo.read("invalid.xml");
    }catch(logic_error & e){
        BOOST_CHECK_EQUAL(e.what(), "Invalid filename : invalid.xml");
    }
}

BOOST_AUTO_TEST_CASE(ParameterSetNoTitle)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    Config foo;
    foo.read(testdatapath.string(), "notitle");
    auto paramSet = foo.getParameterSet("notitle");
}

BOOST_AUTO_TEST_CASE(ParameterSetConductivity)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    Config foo;
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
    Config foo;
    BOOST_CHECK_EXCEPTION(foo.read(testdatapath.string(), "unknowtype"), std::logic_error, unknowTypeMsg);
}

BOOST_AUTO_TEST_CASE(ParameterSetBasicType)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    Config foo;
    foo.read(testdatapath.string(), "basictype");
    auto paramSet = foo.getParameterSet("basictype");
    BOOST_CHECK_EQUAL(paramSet.getNameset(), "basictype");
    BOOST_CHECK_EQUAL(paramSet.getString("astring"),"accessing to example texte !");
    //long i = paramSet.getInteger("aninteger");
    //BOOST_CHECK_EQUAL(i,32);
}

BOOST_AUTO_TEST_SUITE_END()

