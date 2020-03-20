/*
 * TestConfig.cpp
 *
 *  Created on: 16 mars 2020
 *      Author: ludovic
 */

#define BOOST_TEST_MODULE Config
#include <iostream>
#include "Config.h"
#include "ParameterSet.h"
#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>

using namespace std;

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

BOOST_AUTO_TEST_CASE(ParameterSet1)
{
   Config foo("/home/ludovic/workspaceCDT/isabelle/config/analyse.xml");
   auto paramSet = foo.getParameterSet("conductivity");
   BOOST_CHECK_EQUAL(paramSet.getNameset(), "conductivity");
   BOOST_CHECK_EQUAL(paramSet.getTitle(), "conductivité Maguy BMPyrroTFSI et TaF5 variable");
}

BOOST_AUTO_TEST_CASE(ParameterSet2)
{
   Config foo("/home/ludovic/workspaceCDT/isabelle/config/analyse.xml");
   auto paramSet = foo.getParameterSet("conductivity");
   BOOST_CHECK_EQUAL(paramSet.getNameset(), "conductivity");
   //BOOST_CHECK_EQUAL(paramSet.getString("unstring"),"une chaine de texte");
   //BOOST_CHECK_EQUAL(paramSet.getInteger("unentier"),32);
}

BOOST_AUTO_TEST_SUITE_END()

