#include <iostream> 
#include "Player.h"
 
using namespace std;
namespace state {
Player::Player(std::string n_name){
	name=n_name;
}
std::string Player:: getName (){
	return name;
}
int Player::getNbCasle (){
	return castle;
}
void Player::setNbCastle (int n_nb_castle){
	castle=n_nb_castle;
}
int Player::getNbGold (){
	return gold;
}
void Player::setNbGold (int n_nb_gold){
	gold=n_nb_gold;
}
std::vector<UnityArmy> Player::getUnityArmy (){
	return list_pions;
}
}
