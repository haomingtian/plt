#include "Statistics.h"

namespace state {
  class Statistics;
}

namespace state {

    int Statistics::getPV()const { return pv; }
    int Statistics::getAttack () const { return attack; }
    int Statistics::getDefense () const { return defense; }
    int Statistics::getDodge () const { return dodge; }
    int Statistics::getCritical () const { return critical; }
    void Statistics::setPV (int newPV) { pv = newPV; }
    void Statistics::setAttack (int newAttack) { attack = newAttack; }
    void Statistics::setDefense (int newDefense) { defense = newDefense; }
    void Statistics::setDodge (int newDodge) { dodge = newDodge; }
    void Statistics::setCritical (int newCritical) { critical = newCritical; }
    bool Statistics::operator== (Statistics& other)
    {
        if(pv==other.getPV() && attack == other.getAttack() &&
        defense == other.getDefense() &&
        dodge == other.getDodge() &&
        critical == other.getCritical()){
            return true;
        }
        else{
            return false;
        }
    }

    // Setters and Getters
};

