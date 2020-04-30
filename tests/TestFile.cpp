#define BOOST_TEST_MODULE Config
#include <iostream>
#include <exception>
#include <limits>
#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

#include "config/global_build_config.h"
#include "Config.h"
#include "ParameterSet.h"
#include "InputData.h"

using namespace std;
namespace logging = boost::log;

BOOST_AUTO_TEST_SUITE(SuiteFile)

BOOST_AUTO_TEST_CASE(FileNotExist)
{
    try{
        Config foo;
        foo.read("invalid.xml");
    }catch(logic_error & e){
        BOOST_CHECK_EQUAL(e.what(), "Invalid filename : invalid.xml");
    }
}

bool dataFileNotExistMsg(const std::logic_error& ex)
{
    BOOST_CHECK_EQUAL(ex.what(), std::string("Data file doesn't exist : /examples/data/invalid_file_for_test.csv"));
    return true;
}

bool invalidColumnType(const std::logic_error& ex)
{
    BOOST_CHECK_EQUAL(ex.what(), std::string("Invalid type : unknown for column name : R"));
    return true;
}

BOOST_AUTO_TEST_CASE(InputDataFileNotExist)
{
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    Config foo(logging::trivial::debug);
    foo.load(testdatapath.string(), "InputDataFileNotExist");
    auto inputData = foo.getInputData("InputDataFileNotExist");
    BOOST_CHECK_EXCEPTION(inputData.parse(), std::logic_error, dataFileNotExistMsg);
}

BOOST_AUTO_TEST_CASE(InvalidColumnType){
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    Config foo(logging::trivial::debug);
    BOOST_CHECK_EXCEPTION(foo.load(testdatapath.string(), "invalidColumnType"), std::logic_error, invalidColumnType);
}

BOOST_AUTO_TEST_CASE(InputData1){
    vector<double> expectedDataCol1 = {0.5 , 0.75, 1, 1.5, 2, 2.5, 3,
                                   3.5, 4, 4.5, 5, 5.5, 6, 6.5,
                                   7, 7.5, 8, 8.5, 9, 10, 11, 12};
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    Config foo(logging::trivial::debug);
    foo.load(testdatapath.string(), "concentration1");
    auto inputData = foo.getInputData("concentration1");
    inputData.parse();
    int ncol = inputData.columnsCount();
    BOOST_CHECK_EQUAL(5, ncol);
    ColumnOfReal firstCol = inputData.column(0);
    BOOST_CHECK_EQUAL(expectedDataCol1.size(), firstCol.data.size());
    BOOST_CHECK_EQUAL_COLLECTIONS(firstCol.data.begin(), firstCol.data.end(),
            expectedDataCol1.begin(), expectedDataCol1.end());
    // check value of 2nd column 3th line
    ColumnOfReal secCol = inputData.column(1);
    BOOST_CHECK_CLOSE(secCol.data[2],416.666666666667,numeric_limits<double>::epsilon());
}

BOOST_AUTO_TEST_CASE(InputData2){
    vector<double> expectedDataCol1 = {0.5 , 0.75, 1, 1.5, 2, 2.5, 3,
                                   3.5, 4, 4.5, 5, 5.5, 6, 6.5,
                                   7, 7.5, 8, 8.5, 9, 10, 11, 12};
    boost::filesystem::path testdatapath(global_testdatapath);
    testdatapath /= "analyse.xml";
    Config foo(logging::trivial::debug);
    foo.load(testdatapath.string(), "concentration1");
    auto inputData = foo.getInputData("concentration1");
    inputData.parse();
    int ncol = inputData.columnsCount();
    BOOST_CHECK_EQUAL(5, ncol);
    ColumnOfReal firstCol = inputData.column("HCl");
    BOOST_CHECK_EQUAL(expectedDataCol1.size(), firstCol.data.size());
    BOOST_CHECK_EQUAL_COLLECTIONS(firstCol.data.begin(), firstCol.data.end(),
            expectedDataCol1.begin(), expectedDataCol1.end());
    // check value of 2nd column 3th line
    ColumnOfReal secCol = inputData.column("R");
    BOOST_CHECK_CLOSE(secCol.data[2],416.666666666667,numeric_limits<double>::epsilon());
}



BOOST_AUTO_TEST_SUITE_END()
