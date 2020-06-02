/*
 * SColumn.h
 *
 * Author: ludovic leau-mercier
 * Licence: GPLv3 see LICENSE file in source repository
 */

#ifndef SCIDATA_COLUMN_H_
#define SCIDATA_COLUMN_H_

#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;

class ColumnInterface {
public:
    ColumnInterface(string name) : m_name(name) {};
    virtual ~ColumnInterface() {};

    virtual void foo() = 0;
    virtual void append(string str) = 0;
    virtual void append(string str, string locale) = 0;

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
class SColumn : public ColumnInterface {
public:
    SColumn(string name) : ColumnInterface(name){

    }

    virtual void foo(){ return; };

    void append(string str){
        _data.push_back(boost::lexical_cast<CType>(str));
    }

    void append(string str, string locale){
        std::stringstream ss{ str };
        ss.imbue( std::locale(locale) );
        CType result;
        ss >> result;
        _data.push_back(result);
    }

    CType* data(){
        return _data.data();
    }

    int size(){
        return _data.size();
    }

    vector<CType> _data;

};

template class SColumn<string>;
template class SColumn<double>;
template class SColumn<long>;

typedef SColumn<double> ColumnOfReal;

#endif /* SCIDATA_COLUMN_H_ */
