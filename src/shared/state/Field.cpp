#include <iostream>
#include <memory>
#include "state.h"

using namespace std;
namespace state {
Field::Field(int n_x, int n_y, int n_codetuile){
	position.setX(n_x);
	position.setY(n_y);
    codeTuile = n_codetuile;
}
bool Field::isField (){
	return true;
}
int Field::isOccupated (State& state){
    int resultat=-1;
    vector<std::unique_ptr<UnityArmy>> & listePersonnages = state.getUnityArmys();

    /* On compare la position de la case evaluee avec celles des personnages pour savoir si
        une unite est dessus */
    for(size_t i=0; i < listePersonnages.size(); i++){
        if (position.equals(listePersonnages[i]->getPosition())){
            resultat = i;
            break;

        }

    }

    return resultat;
}
}
