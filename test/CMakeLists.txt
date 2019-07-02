enable_testing()
find_package(Boost COMPONENTS system filesystem regex thread unit_test_framework REQUIRED)

include_directories (${TEST_SOURCE_DIR}/src) 

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

add_executable (test EDSAC_unit_tests.cpp) 

target_link_libraries(test
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )

enable_testing()
add_test(EDSAC_test test)