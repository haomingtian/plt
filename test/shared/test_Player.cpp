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
  }

}

/* vim: set sw=2 sts=2 et : */
