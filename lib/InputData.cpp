/*
 * InputData.cpp
 *
 *  Created on: 27 avr. 2020
 *      Author: ludovic
 */

#include "InputData.h"
#include <memory>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/locale.hpp>

using boost::bad_lexical_cast;
using namespace std;


InputData::InputData() : m_locale("fr_FR.UTF-8"), m_headerLine(0)  {

}

InputData::InputData(string name) : m_name(name), m_headerLine(0)    {

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


void InputData::createColumn(string name, string type){
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
}

void InputData::parse(){
    BOOST_LOG_TRIVIAL(debug) << "parse file "<< m_file.string();
    if(!boost::filesystem::exists(m_file)){
        throw logic_error("Data file doesn't exist : "+m_file.string());
    }
    std::locale::global(std::locale(m_locale));
    boost::filesystem::ifstream infile(m_file);
    string currentLine;
    int nline = 0;
    while(getline(infile, currentLine)){
        nline++;
        if(nline != m_headerLine){
            list<string> cells;
            split(cells, currentLine, boost::is_any_of("\t"));
            if(cells.size() != m_columnObjects.size()){
                BOOST_LOG_TRIVIAL(debug) << "cell size "<<cells.size()<< " col number "<<m_columnObjects.size();
                stringstream ss;
                ss << "Invalid number of cell in row " << nline;
                throw logic_error(ss.str());
            }
            itColumnObjects it = m_columnObjects.begin();
            list<string>::iterator itcell = cells.begin();
            try{
                while(it != m_columnObjects.end()){
                    (*it)->append(*itcell);
                    ++it;
                    ++itcell;
                }
            }catch(const bad_lexical_cast & e){
                stringstream ss;
                ss << "lexical cast error in row " << nline << " error "<<e.what();
                throw logic_error(ss.str());
            }
        }else{
            //TODO get save header line
        }
    }
    infile.close();
}
