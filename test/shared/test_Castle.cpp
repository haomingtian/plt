
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Castle.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCastle)
{
  {
	Castle c(FIRSTLEVEL,1,2,2);
    BOOST_CHECK_EQUAL(c.getType(),FIRSTLEVEL);
    BOOST_CHECK_EQUAL(c.getName(),"FIRSTLEVEL");
    BOOST_CHECK_LE(c.getCodeTuile(), 32);
    c.setCodeTuile(4);
    BOOST_CHECK_EQUAL(c.getCodeTuile(),4);
  }

  /*{
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
}

/* vim: set sw=2 sts=2 et : */
