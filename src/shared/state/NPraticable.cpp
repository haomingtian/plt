#include <iostream> 
#include "NPraticable.h"
 
using namespace std;
namespace state {

NPraticable::NPraticable (TypeNPraticableId id, int x, int y, int codetuile):Field (x, y, codetuile){
	type_id=id;
	if(id==TREE){
		name="TREE";
	}
	else if(id==WATER){
		name="WATER";
	}
	else if(id==WALL){
		name="WALL";
	}
}
bool NPraticable::isPraticable (){
	return false;
}
TypeNPraticableId NPraticable:: getType (){
	return type_id;
}
}
