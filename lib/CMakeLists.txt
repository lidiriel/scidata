add_library(SciData SHARED
    SConfig.cpp
    SParameterSet.cpp
    SInputData.cpp
)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")

target_include_directories (SciData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries( SciData ${Boost_LIBRARIES})