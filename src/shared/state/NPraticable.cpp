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
bool NPraticable::equals (Elements& other){
	bool resultat;
	if(other.isField()){
		Field& other_field = static_cast<Field&>(other);
		if(!other_field.isPraticable()){
			NPraticable& other_terrain_n_praticable=static_cast<NPraticable&>(other_field);
			if(	this->Elements::equals(other_terrain_n_praticable) &&
				type_id==other_terrain_n_praticable.getType()){
				resultat=true;
			}
			else{resultat=false;}
		}
		else{ resultat=false;}
	}
	else{resultat=false;}
	
	return resultat;
}
}
