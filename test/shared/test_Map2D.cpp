
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Map2D.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestMap2D)
{
  {
	Map2D mp(5,2);
    BOOST_CHECK_EQUAL(mp.getWidth (),5);
    BOOST_CHECK_LE(mp.getHeigth (), 10);
  }

  /*{
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
}

/* vim: set sw=2 sts=2 et : */
