#include <iostream>
#include "UnityArmy.h"
#include "state.h"

using namespace std;
namespace state {
    UnityArmy::UnityArmy(ArmyTypeId newTypeId, std::string newName, bool newCamp) {
        typeId = newTypeId;
        name = newName;
        camp = newCamp;
        currentlife = 10;
        if (typeId == ARCHER) {
            move_field = 1;
            attack = 100;
            defense = 100;
        } else if (typeId == CAVLRY) {
            move_field = 2;
            attack = 150;
            defense = 150;
        } else if (typeId == INGENEER) {
            move_field = 2;
            attack = 200;
            defense = 200;
        } else if (typeId == INFANTRY) {
            move_field = 1;
            attack = 250;
            defense = 250;
        }
    }

    UnityArmy::UnityArmy(ArmyTypeId newTypeId, bool newCamp, std::string newName, int newX, int newY) {
        typeId = newTypeId;
        camp = newCamp;
        status = AVAILABLE;
        name = newName;
        position.setX(newX);
        position.setY(newY);

        if (typeId == ARCHER) {
            armorName = "Arc";
            armorId = 1;
            move = 3;
            attack = 2;
            statistics.setPV(20);
            statistics.setAttack(11);
            statistics.setDefense(6);
            statistics.setDodge(10);
            statistics.setCritical(50);
            if (newCamp == true) {
                codeTuile = 0;
            } else { codeTuile = 4; }
        } else if (typeId == INFANTRY) {
            armorName = "Axe";
            armorId = 2;
            move = 3;
            attack = 1;
            statistics.setPV(20);
            statistics.setAttack(15);
            statistics.setDefense(8);
            statistics.setDodge(15);
            statistics.setCritical(10);
            if (newCamp == true) {
                codeTuile = 1;
            } else { codeTuile = 5; }
        } else if (typeId == LANCER) {
            armorName = "Lance";
            armorId = 3;
            move = 5;
            attack = 1;
            statistics.setPV(25);
            statistics.setAttack(15);
            statistics.setDefense(8);
            statistics.setDodge(15);
            statistics.setCritical(0);
            if (newCamp == true) {
                codeTuile = 3;
            } else { codeTuile = 7; }
        } else if (typeId == CAVLRY) {
            armorName = "Epee";
            armorId = 4;
            move = 3;
            attack = 1;
            statistics.setPV(20);
            statistics.setAttack(15);
            statistics.setDefense(10);
            statistics.setDodge(0);
            statistics.setCritical(10);
            if (newCamp == true) {
                codeTuile = 2;
            } else { codeTuile = 6; }
        }
    }

    std::vector<Position> UnityArmy::getLegalMove(State &inState) {
        // Note : On n'autorise pas le deplacement sur sa propre case car elle est considérée comme occupée

        vector<Position> ListePosMouv;
        Position positionAjoutee;

        //On parcourt les abscissas puis les ordonnees de la grille
        for (int abscissa = position.getX() - 1; abscissa <= position.getX() + 1; abscissa++) {
            for (int ordonnee = position.getY() - 1; ordonnee <= position.getY() + 1; ordonnee++) {

                // On teste les cases qui sont dans la zone de deplacement du personnage
                if (abs(abscissa - position.getX()) + abs(ordonnee - position.getY()) <= 1 && abscissa >= 0 &&
                    ordonnee >= 0 && abs(abscissa) < inState.getGrid().size() &&
                    abs(ordonnee) < inState.getGrid()[abscissa].size()) {

                    if (inState.getGrid()[abscissa][ordonnee]->isPraticable()) {
                        if (inState.getGrid()[abscissa][ordonnee]->isOccupated(inState) == -1) {
                            positionAjoutee.setX(abscissa);
                            positionAjoutee.setY(ordonnee);
                            ListePosMouv.push_back(positionAjoutee);

                        }
                    }
                }
            }
        }
        return ListePosMouv;
    }

    std::vector<Position> UnityArmy::getLegalAttack(State &inState) {
        vector<Position> ListePosAtq;
        Position positionAjoutee;

        //On parcourt les abscissas puis les ordonnees de la grille
        for (int abscissa = this->position.getX() - attack; abscissa <= this->position.getX() + attack; abscissa++) {
            for (int ordonnee = this->position.getY() - attack;
                 ordonnee <= this->position.getY() + attack; ordonnee++) {
                // On teste les cases qui sont dans la zone d'attaque du personnage
                if (abs(abscissa - position.getX()) + abs(ordonnee - position.getY()) <= attack && abscissa >= 0 &&
                    ordonnee >= 0 && abs(abscissa) < inState.getGrid().size() &&
                    abs(ordonnee) < inState.getGrid()[abscissa].size()) {
                    if (inState.getGrid()[abscissa][ordonnee]->isPraticable()) {
                        int res = inState.getGrid()[abscissa][ordonnee]->isOccupated(inState);
                        if (res != -1) {
                            if (this->camp != inState.getUnityArmys()[res]->getCamp()) {
                                positionAjoutee.setX(abscissa);
                                positionAjoutee.setY(ordonnee);
                                // On ne peut attaquer sa propre case
                                if (!positionAjoutee.equals(this->position)) {
                                    ListePosAtq.push_back(positionAjoutee);
                                }
                            }
                        }
                    }
                }
            }
        }
        return ListePosAtq;
    }

    ArmyTypeId UnityArmy::getType() {
        return typeId;
    }

    int UnityArmy::getCurrentlife() {
        return currentlife;
    }

    void UnityArmy::setCurrentlife(int n_currentlife) {
        currentlife = n_currentlife;
    }

    int UnityArmy::getAttack() {
        return attack;
    }

    void UnityArmy::setAttack(int newAttack) {
        attack = newAttack;
    }

    int UnityArmy::getDefense() {
        return defense;
    }

    void UnityArmy::setDefense(int newDefense) {
        defense = newDefense;
    }

    bool UnityArmy::getCamp() {
        return camp;
    }

    Status UnityArmy::getStatus() {
        return status;
    }

    bool UnityArmy::isField() {
        return false;
    }

    int UnityArmy::getDodge() {
        return dodge;
    }

    int UnityArmy::getCritical() {
        return critical;
    }

    void UnityArmy::setCritical(int newCritical) {
        critical = newCritical;
    }

    void UnityArmy::setDodge(int newDodge) {
        dodge = newDodge;
    }

    void UnityArmy::setCamp(bool newCamp) {
        camp = newCamp;
    }

    ArmyTypeId UnityArmy::getTypeId() const {
        return typeId;
    }

    void UnityArmy::setTypeId(ArmyTypeId newTypeId) {
        typeId = newTypeId;
    }

    void UnityArmy::setStatus(Status newStatus)
    {
        status = newStatus;
    }

    void UnityArmy::setMove(int newMove)
    {
        move = newMove;
    }
    const std::string& UnityArmy::getArmorName() const
    {
        return armorName;
    }
    void UnityArmy::setArmorName(const std::string& newArmorName)
    {
        armorName = newArmorName;
    }

    int UnityArmy::getArmorId() const
    {
        return armorId;
    }
    void UnityArmy::setArmorId(int newArmorId)
    {
        armorId = newArmorId;
    }

    int UnityArmy::getMove()
    {
        return move;
    }

    bool UnityArmy::equals(state::Elements &other)
    {
        bool resultat;
        if(!other.isField()){
            UnityArmy& other_personnage = static_cast<UnityArmy&>(other);

            if(	this->Elements::equals(other_personnage) &&
                   armorName==other_personnage.getArmorName() &&
                   armorId==other_personnage.getArmorId() &&
                   typeId==other_personnage.getType() &&
                   move==other_personnage.getMove() &&
                   attack==other_personnage.getAttack()){
                resultat=true;
            }
            else{resultat=false;}
        }
        else{resultat=false;}
        return resultat;
    }
}



