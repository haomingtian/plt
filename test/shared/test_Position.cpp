
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Position.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestPosition)
{
  {
	  Position p(5,2);
	  p.setX(8);
	  BOOST_CHECK_EQUAL(p.getX (), 8);
	  p.setY(5);
	  BOOST_CHECK_GT(p.y, 3);
  }

  /*{
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
}

/* vim: set sw=2 sts=2 et : */
