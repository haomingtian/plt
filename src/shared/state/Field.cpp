#include <iostream> 
#include "Field.h"
 
using namespace std;
namespace state {
	Field::Field(int n_x, int n_y, int n_codetuile){
	position.setX(n_x);
	position.setY(n_y);
	codetuile = n_codetuile;
	}
	bool Field::isField (){
	return true;
	}
	/*bool Field::isOccupated (State& s){
		int resultat=-1;
		std::vector<std::unique_ptr<UnityArmy>>& list_unity=s.getUnityArmy();
		// On compare la position de la case evaluee avec celles des personnages pour savoir si
			//une unite est dessus 
		for(size_t i=0; i < list_unity.size(); i++){
			if (position.equals(list_unity[i]->getPosition())){
				resultat = i;
				break;
			
			}
		
	}	
	
	return resultat;
	}*/
}
