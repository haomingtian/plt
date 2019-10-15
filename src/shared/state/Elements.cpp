#include <iostream> 
 
using namespace std;
Elements::Elements (){
	name="";
	position.setX(0);
	position.setY(0);
}
bool isStatic ();
Position& Elements::getPosition (){
	Position & refPosition = position;
	return refPosition 
}
int Elements::getCodeTuile (){
	return codetuile;
}
void Elements::setCodeTuile (int n_codetuile){
	codetuile=n_codetuile;	
}
void Elements::equals (Elements& o){
	bool resultat;
	if(this->position.equals(other.getPosition())==1 && this->nom==other.getNom()){
		resultat = true;}
	else{
		resultat = false;
	}
	return resultat;
}
