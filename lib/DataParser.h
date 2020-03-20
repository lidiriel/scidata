/*
 * DataParser.h
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */

#ifndef DATAPARSER_H_
#define DATAPARSER_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "DataContainer.h"
#include "DataDescription.h"

using namespace std;

class DataParser {
public:
    DataParser(DataDescription dataDesc);
    virtual ~DataParser();
    DataContainer* read();

};

#endif /* DATAPARSER_H_ */
