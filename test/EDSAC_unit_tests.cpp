#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include "./../include/Logging.h"

using namespace boost::unit_test;
using namespace Logging;

BOOST_AUTO_TEST_SUITE( LoggingTestSuite )

struct cout_redirect {
    cout_redirect( std::streambuf * new_buffer ) 
        : old( std::cout.rdbuf( new_buffer ) )
    { }

    ~cout_redirect( ) {
        std::cout.rdbuf( old );
    }

private:
    std::streambuf * old;
};


BOOST_AUTO_TEST_CASE( LoggingOutputTest )
{
    boost::test_tools::output_test_stream output;
    {
        cout_redirect guard( output.rdbuf( ) );
		logInfoMessage("Test Info Logging");
    }

    BOOST_CHECK( output.is_equal( "[INFO] Test Info Logging\n" ) );
}

BOOST_AUTO_TEST_SUITE_END()