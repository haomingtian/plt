#include <string>
#include <iostream> 
#include "Engine.h"
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace render;
using namespace state;
using namespace std;
namespace engine{
	Engine::Engine (){
		change_turn=false;
		actif_player=true;
		record["RealSize"] = 0;
		record["tabCmd"][0] = "";
	}
	Engine::~Engine (){
	}
	state::State& Engine::getState (){
		state::State& ref_s=current_state;
		return ref_s;
	}
	/*void Engine::addOrder (int priority, std::unique_ptr<Order> ptr_cmd){
		if (enableRecord){
			Json::Value newCmd = ptr_ord->serialize();
			record["tabCmd"][record["tailleReelle"].asUInt()] = newCmd;
			record["tailleReelle"] = record["tailleReelle"].asUInt() + 1;
	}
		current_orders[priority]=move(ptr_ord);	
	}*/
	void Engine::update (){
	}
	bool Engine::verificationEndTurn (){
	}
	void Engine::verificationStartTurn (){
	}
	void Engine::undo (Action* action){
	}
	void Engine::addAction (Action* newAction){
	}
	void Engine::cursorChanged (state::State& s, render::CursorEventID& key, int actor, int target, state::Position& position, bool rollback){
	}
	void Engine::setEnableRecord (bool val){
	}
	Json::Value Engine::getRecord (){
	}
    std::map<int, std::unique_ptr<Order>>& Engine::getCurrentOrders (){
	}
	bool Engine::getEnableRecord() const{
	}
    void Engine::setRecord(const Json::Value& record){
	}
	bool Engine::getPlayerActif (){
		return actif_player;
	}
	bool Engine::getStop() const{
	}
}
