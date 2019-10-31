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
/*bool Field::isOccupated (){
	int resultat=-1;
	vector<UnityArmy> & list_unity=state.getUnityArmy();
}*/
}
