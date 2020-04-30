/*
 * InputData.h
 *
 *  Created on: 27 avr. 2020
 *      Author: ludovic
 */

#ifndef LIB_INPUTDATA_H_
#define LIB_INPUTDATA_H_

#include <string>
#include <vector>
#include <memory>
#include <boost/filesystem.hpp>
 #include <boost/locale.hpp>
#include "Column.h"

using namespace std;



class InputData {
public:
    InputData();
    InputData(string name);
    virtual ~InputData();

    bool operator==(const InputData& other) const;

    void setStructure(string s) { m_structure = s; }
    int columnsCount() { return m_columnObjects.size(); }
    void createColumn(string name, string type);
    void setFile(boost::filesystem::path file){ m_file = file; }
    void parse();
    ColumnOfReal column(int index);
    ColumnOfReal column(string name);
    void setSeparator(string sep){ m_separator = sep; }
    void setLocale(string loc);
    void setHeaderLine(int line){ m_headerLine = line; }
private:
    string m_name;
    string m_structure;
    string m_separator;
    string m_locale;
    int m_headerLine;
    boost::filesystem::path m_file;
    vector<shared_ptr<ColumnInterface>> m_columnObjects;

    typedef vector<shared_ptr<ColumnInterface>>::iterator itColumnObjects;

};

#endif /* LIB_INPUTDATA_H_ */
