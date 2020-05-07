/*
 * InputData.cpp
 *
 *  Created on: 27 avr. 2020
 *      Author: ludovic
 */

#include "InputData.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/locale.hpp>

using namespace std;

#define MYLOCALE "fr_FR.UTF-8"

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

InputData::InputData() : m_locale(MYLOCALE), m_headerLineNumber(0)  {

}

InputData::InputData(string name) : m_name(name), m_locale(MYLOCALE),  m_headerLineNumber(0)    {

}

InputData::~InputData() {
}

bool InputData::operator==(const InputData& other) const{
    if(this->m_name.compare(other.m_name) == 0)
        return true;
    else
        return false;
}

void InputData::setLocale(string loc){
    list<string> locales = { "de_DE", "en_US", "nl_NL", "nl_BE", "fr_FR", "ru_RU" };
    bool lfound = false;
    for(auto l : locales){
        string ll = l+".UTF-8";
        if(loc.compare(ll) == 0){
            lfound = true;
        }
    }
    if(!lfound){
        throw logic_error("invalid locale "+loc+" try fr_FR.UTF-8 or en_US.UTF-8");
    }
    m_locale = loc;

}

void InputData::setSeparator(string sep){
    boost::replace_all(sep,"\\s"," ");
    boost::replace_all(sep,"\\t","\t");
    m_separator = sep;
}

ColumnOfReal InputData::column(int index){
    shared_ptr<ColumnOfReal> column = static_pointer_cast<ColumnOfReal> (m_columnObjects[index]);
    return *column;
}

ColumnOfReal InputData::column(string name){
    itColumnObjects it = m_columnObjects.begin();
    for(; it != m_columnObjects.end(); ++it){
        if(name.compare((*it)->getName()) == 0){
            break;
        }
    }
    if (it == m_columnObjects.end()) {
        throw logic_error("inputdata " + name + " not found.");
    }
    shared_ptr<ColumnOfReal> column = static_pointer_cast<ColumnOfReal> (*it);
    return *column;
}


shared_ptr<ColumnInterface> InputData::createColumn(string name, string type){
    shared_ptr<ColumnInterface> ptr(nullptr);
    bool typeUnknown = true;
    if(type.compare("string") == 0){
        m_columnObjects.push_back(make_shared<Column<string>>(name));
        typeUnknown = false;
    }
    if(type.compare("real") == 0){
        m_columnObjects.push_back(make_shared<Column<double>>(name));
        typeUnknown = false;
    }
    if(type.compare("integer") == 0){
        m_columnObjects.push_back(make_shared<Column<long>>(name));
        typeUnknown = false;
    }
    if(typeUnknown){
        throw logic_error("Invalid type : "+type+" for column name : "+name);
    }
    return m_columnObjects.back();
}

void InputData::changeLocale(){
    BOOST_LOG_TRIVIAL(debug) << "current locale attribut :"<<m_locale;
    string  spi = "3,14";
    BOOST_LOG_TRIVIAL(debug) << "try to convert " << spi << " with locale "<<m_locale;
    std::locale loc= boost::locale::generator().generate(m_locale);
    std::locale oldloc = std::locale::global(loc);
    BOOST_LOG_TRIVIAL(debug) << "change locale from : "<< oldloc.name().c_str() << " to : "<<loc.name().c_str();
    char point = std::use_facet< std::numpunct<char> >(std::cin.getloc()).decimal_point();
    std::locale l1;
    BOOST_LOG_TRIVIAL(debug) << "locale l1 :"<<l1.name().c_str()<<" decimal sep :"<<point;
    try{
        double pi = boost::lexical_cast<double>(spi);
        BOOST_LOG_TRIVIAL(debug) << "pi=" << pi;
    }catch(boost::bad_lexical_cast & e){
        BOOST_LOG_TRIVIAL(debug) << "lexical cast error : " << e.what();
    }
}

void InputData::parse(){
    BOOST_LOG_TRIVIAL(debug) << "parse file "<< m_file.string();
    if(!boost::filesystem::exists(m_file)){
        throw logic_error("Data file doesn't exist : "+m_file.string());
    }
    //changeLocale();
    boost::filesystem::ifstream infile(m_file);
    string currentLine;
    int nline = 0;
    while(getline(infile, currentLine)){
        nline++;
        trim(currentLine);
        if(nline != m_headerLineNumber){
            if(currentLine.size() !=0 && currentLine.rfind(m_commentStartWith, 0) != 0) {
                vector<string> cells;
                split(cells, currentLine, boost::is_any_of(m_separator), boost::token_compress_on);
                if(cells.size() != m_columnObjects.size()){
                    BOOST_LOG_TRIVIAL(debug) << "cells size "<<cells.size()<< " col number "<<m_columnObjects.size();
                    BOOST_LOG_TRIVIAL(debug) << currentLine;
                    //BOOST_LOG_TRIVIAL(debug) << cells[0] << "|" << cells[1];
                    stringstream ss;
                    ss << "Invalid number of cells in row " << nline;
                    throw logic_error(ss.str());
                }
                itColumnObjects it = m_columnObjects.begin();
                vector<string>::iterator itcell = cells.begin();
                try{
                    while(it != m_columnObjects.end()){
                        //(*it)->append(*itcell);
                        (*it)->append(*itcell, m_locale);
                        ++it;
                        ++itcell;
                    }
                }catch(const boost::bad_lexical_cast & e){
                    BOOST_LOG_TRIVIAL(debug)<<"Error in current cell ["<<*itcell<<"]";
                    stringstream ss;
                    ss << "lexical cast error in row " << nline << " error "<<e.what();
                    throw logic_error(ss.str());
                }catch(const std::runtime_error & e){
                    BOOST_LOG_TRIVIAL(debug)<<"Error in current cell ["<<*itcell<<"]";
                    stringstream ss;
                    ss << "runtime error in row " << nline << " error "<<e.what();
                    throw logic_error(ss.str());
                }
            }
        }else{
            split(m_headers, currentLine, boost::is_any_of(m_separator));
        }
    }
    infile.close();
}
