/*
 * DataContainer.h
 *
 *  Created on: 10 mars 2020
 *      Author: ludovic
 */

#ifndef DATACONTAINER_H_
#define DATACONTAINER_H_

#include <string>
#include <vector>
#include "boost/multi_array.hpp"
#include "DataColumn.h"

using namespace std;

class DataContainer {

    //typedef boost::multi_array<double, 2> array_type;
    //typedef array_type::index index;
public:
    DataContainer();
    virtual ~DataContainer();

    vector<double> getRawDataById(string colID);

    DataColumn* getColumnById(string colID);

//    void extents(int line, int cols){
//        _raw(boost::extents[3][5]);
//    }
/*
    array_type* raw(){
        //return &_raw;
    }
*/
//    double getByIndex(int i, int j){
//        //return _raw[i][j];
//    }

    int columnsCount(){
        return 0;
    }

private:
    boost::multi_array<double, 2> _raw;
};

#endif /* DATACONTAINER_H_ */
