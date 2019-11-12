#include "Action.h"
#include <string>
#include <iostream> 
namespace engine{
bool Action::getPlayer (){
	return player;
}
ActionID Action::getActionID (){
	return id;
}
}
