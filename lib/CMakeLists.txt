add_library(scidata SHARED
    Config.cpp
    DataColumn.cpp
    DataContainer.cpp
    DataDescription.cpp
    DataParser.cpp
    ParameterSet.cpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")

target_include_directories (scidata PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries( scidata ${Boost_LIBRARIES})