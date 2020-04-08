
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

add_executable(testConfig TestConfig.cpp)

set (CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")

target_include_directories(testConfig PRIVATE ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/config)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
#message(${Boost_LIBRARIES})

target_link_libraries(testConfig
                      scidata
                      #${CMAKE_THREAD_LIBS_INIT}
                      ${Boost_LIBRARIES}
                      #Threads::Threads
                      )
                      

