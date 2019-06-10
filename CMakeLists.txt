cmake_minimum_required (VERSION 2.6)
Project(EDSAC)

set (EDSAC_Compiler_Version_Major 1)
set (EDASC_Compiler_Version_Minor 1)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME})
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/src")

if(APPLE)
  add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
endif()

add_definitions(-BOOST_SYSTEM_NO_DEPRECATED)

file(GLOB_RECURSE Foo_SOURCES "src/*.cpp" "src/*.cc")

find_package(Boost 1.50.0 REQUIRED COMPONENTS  thread filesystem regex system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(EDSAC ${Foo_SOURCES})
  target_link_libraries(EDSAC ${Boost_LIBRARIES})
endif()