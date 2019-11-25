#include <iostream> 
#include "Statistics.h"

namespace state{
	int Statistics::getDefense (){
		return pdefense;
	}
    int Statistics::getAttack (){
		return pattack;
	}
    int Statistics::getCurrentLife (){
		return current_life;
	}
    int Statistics::getPriceUnity (){
		return price_unity;
	}
    int Statistics::getPriceCastle (){
		return price_castle;
	}
    void Statistics::setDefense (int def){
		if(def<0) pdefense=0;
		else pdefense=def;
	}
    void Statistics::setAttack (int at){
		if(at<0) pattack=0;
		else pattack=at;		
	}
    void Statistics::setCurrentLife (int c_l){
		if(c_l<0) current_life=0;
		else current_life=c_l;		
	}
}
