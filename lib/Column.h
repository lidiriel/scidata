/*
 * Column.h
 *
 *  Created on: 27 avr. 2020
 *      Author: ludovic
 */

#ifndef LIB_COLUMN_H_
#define LIB_COLUMN_H_

#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

using boost::bad_lexical_cast;
using boost::lexical_cast;

using namespace std;

class ColumnInterface {
public:
    ColumnInterface(string name) : m_name(name) {};
    virtual ~ColumnInterface() {};

    virtual void foo() = 0;
    virtual void append(string str) = 0;

    void setName(string name) { m_name = name; }
    string getName() { return m_name; }
    void setUnit(string unit) { m_unit = unit; }
    string getUnit() { return m_unit; }
    void setComment(string comment) { m_comment = comment; }
    string getComment() { return m_comment; }

private:
    string m_name;
    string m_unit;
    string m_comment;

};

template <class CType>
class Column : public ColumnInterface {
public:
    Column(string name) : ColumnInterface(name){

    }

    virtual void foo(){ return; };

    void append(string str){
        data.push_back(lexical_cast<CType>(str));
    }

    vector<CType> data;

};

template class Column<string>;
template class Column<double>;
template class Column<long>;

typedef Column<double> ColumnOfReal;

#endif /* LIB_COLUMN_H_ */
