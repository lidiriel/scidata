cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(scidata)

# pour améliorer l'analyse des erreurs par eclipse
IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")

# for boost LOG
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
SET(Boost_USE_MULTITHREADED ON)  
#SET(Boost_LOG_DYN_LINK
find_package(Boost COMPONENTS unit_test_framework thread log log_setup REQUIRED)
include_directories( ${CMAKE_BINARY_DIR} )

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(config)
add_subdirectory(temp)
