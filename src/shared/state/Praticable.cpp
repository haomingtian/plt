#include <iostream> 
#include "Praticable.h"
 
using namespace std;
namespace state {
Praticable ::Praticable(TypePraticableId id, int n_x, int n_y, int n_codetuile):Field (n_x, n_y, n_codetuile){
	type_id=id;
	if(id==LAND){
		name="LAND";
	}
	else if(id==HILL){
		name="HILL";
	}
}
TypePraticableId Praticable::getType (){
	return type_id;
}
bool isPraticable (){
	return true;
}
}
