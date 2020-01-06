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
	} else if (id==GRASS)
    {
	    name = "GRASS";
    }
}
TypePraticableId Praticable::getTypeId() {
	return type_id;
}
bool Praticable::isPraticable (){
	return true;
}

bool Praticable::equals (Elements& other){
        bool resultat;
        if(other.isField()){
            Field& other_terrain = static_cast<Field&>(other);
            if(other_terrain.isPraticable()){
                Praticable& other_terrain_praticable = static_cast<Praticable&>(other_terrain);
                if(	this->Elements::equals(other_terrain_praticable) &&
                       type_id==other_terrain_praticable.getTypeId()){
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
