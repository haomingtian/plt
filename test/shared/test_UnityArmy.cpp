
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/UnityArmy.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestUnityArmy)
{
  {
	UnityArmy u(CAVLRY,"cav",true);
    BOOST_CHECK_EQUAL(u.getType (),CAVLRY);
    u.setCurrentlife(8);
    BOOST_CHECK_EQUAL(u.getCurrentlife (), 8);
  }

  /*{
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
}

/* vim: set sw=2 sts=2 et : */
