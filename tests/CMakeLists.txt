
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

add_executable(testConfig 
    TestConfig.cpp
    )
    
add_executable(testFile
    TestFile.cpp
    )

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")

target_include_directories(testConfig PRIVATE ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/config)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
#message(${Boost_LIBRARIES})

target_link_libraries(testConfig
                      scidata
                      ${Boost_LIBRARIES}
                      )
                      

target_include_directories(testFile PRIVATE ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/config)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
#message(${Boost_LIBRARIES})

target_link_libraries(testFile
                      scidata
                      ${Boost_LIBRARIES}
                      )

