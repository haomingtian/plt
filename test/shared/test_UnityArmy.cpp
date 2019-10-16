
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
    BOOST_CHECK_EQUAL(u.getMoveField (), 2);
    BOOST_CHECK_EQUAL(u.getAttack (), 150);
    BOOST_CHECK_EQUAL(u.getDefense (), 150);
  }
  {
	UnityArmy v(INGENEER,"ing",true);
    BOOST_CHECK_EQUAL(v.getType (),INGENEER);
    v.setCurrentlife(7);
    BOOST_CHECK_EQUAL(v.getCurrentlife (), 7);
    BOOST_CHECK_EQUAL(v.getMoveField (), 2);
    BOOST_CHECK_EQUAL(v.getAttack (), 200);
    BOOST_CHECK_EQUAL(v.getDefense (), 200);
  }
  {
	UnityArmy w(INFANTRY,"inf",true);
    BOOST_CHECK_EQUAL(w.getType (),INFANTRY);
    w.setCurrentlife(7);
    BOOST_CHECK_EQUAL(w.getCurrentlife (), 7);
    BOOST_CHECK_EQUAL(w.getMoveField (), 1);
    BOOST_CHECK_EQUAL(w.getAttack (), 250);
    BOOST_CHECK_EQUAL(w.getDefense (), 250);
  }
  {
	UnityArmy x(ARCHER,"arch",true);
    BOOST_CHECK_EQUAL(x.getType (),ARCHER);
    x.setCurrentlife(7);
    BOOST_CHECK_EQUAL(x.getCurrentlife (), 7);
    BOOST_CHECK_EQUAL(x.getMoveField (), 1);
    BOOST_CHECK_EQUAL(x.getAttack (), 100);
    BOOST_CHECK_EQUAL(x.getDefense (), 100);
  }

  /*{
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }*/
}

/* vim: set sw=2 sts=2 et : */
