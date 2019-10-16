
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Praticable.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestPraticable)
{
  /*{
	Praticable p(LAND,0,0,2);
    BOOST_CHECK_EQUAL(p.getType(),LAND);
    BOOST_CHECK_EQUAL(p.getCodeTuile,2);
  }*/

  /*{
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
}

/* vim: set sw=2 sts=2 et : */
