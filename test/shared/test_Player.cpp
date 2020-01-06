#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestPlayer)
{
  {
    //Player p("joueur1") {};
    Player p("joueur1");
    BOOST_CHECK_EQUAL(p.name, "joueur1");
    p.name="marly";
    BOOST_CHECK_EQUAL(p.name, "marly");
    p.setNbCastle(7);
    BOOST_CHECK_EQUAL(p.getNbCasle (), 7);
    p.setNbGold(22);
    BOOST_CHECK_LE(p.getNbGold (), 32); // Less than equal
    BOOST_CHECK_GT(p.getNbGold (), 11); // Greater than equl
    
  }

}

/* vim: set sw=2 sts=2 et : */
