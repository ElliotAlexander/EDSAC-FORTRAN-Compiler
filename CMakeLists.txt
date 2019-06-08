cmake_minimum_required (VERSION 2.6)
Project(EDSAC)

set (EDSAC_Compiler_Version_Major 1)
set (EDASC_Compiler_Version_Minor 1)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_ADDITIONAL_VERSIONS 1.68.0 1.68 1.69)

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/src")

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

file(GLOB_RECURSE Foo_SOURCES "src/*.cpp" "src/*.cc")

find_package(Boost 1.68 REQUIRED COMPONENTS  thread filesystem regex system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(EDSAC ${Foo_SOURCES})
  target_link_libraries(EDSAC ${Boost_LIBRARIES} ${Boost_SYSTEM_LIBRARY})
endif()