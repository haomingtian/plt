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
bool Praticable::equals (Elements& other){
	bool resultat;
	if(other.isField()){
		Field& other_field = static_cast<Field&>(other);
		if(other_field.isPraticable()){
			Praticable& other_field_praticable = static_cast<Praticable&>(other_field);
			if(	this->Elements::equals(other_field_praticable) &&
				type_id==other_field_praticable.getType()){
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
