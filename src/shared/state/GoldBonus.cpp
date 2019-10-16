#include <iostream> 
#include "GoldBonus.h"
using namespace std;

namespace state {
GoldBonus ::GoldBonus(TypeGoldId id, int n_x, int n_y, int n_codetuile){
	type_id=id;
	if(id==GOLDLAND){
		name="GOLDLAND";
		nb_gold=1;
	}
	else if(id==GOLDCASTLE){
		name="GOLDLAND";
		nb_gold=5;
	}
}
int GoldBonus::getNbGold(){
	return nb_gold;
}
void GoldBonus::setNbGold (int n_nbgold){
	nb_gold=n_nbgold;
}
TypeGoldId GoldBonus::getType (){
	return type_id;
}
}

