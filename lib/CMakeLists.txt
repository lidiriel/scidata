# list of source files
set(libsrc 
    SConfig.cpp
    SParameterSet.cpp
    SInputData.cpp
    )

# this is the "object library" target: compiles the sources only once
add_library(objlib OBJECT ${libsrc})

# shared libraries need PIC
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

# shared and static libraries built from the same object files
add_library(SciData SHARED $<TARGET_OBJECTS:objlib>)
add_library(SciData-static STATIC $<TARGET_OBJECTS:objlib>)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")

target_include_directories (SciData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries( SciData ${Boost_LIBRARIES})