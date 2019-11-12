#include <SFML/Graphics.hpp>
#include <string>
#include "Observable.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

using namespace state;
using namespace std;

namespace render{
	void Observable::registerObserver (IObserver* observer){
		observers.push_back(observer);
	}
	void Observable::notifyObserver (state::State& s, render::CursorEventID& key, int actor, int target, state::Position& position, bool rollback){
			for(auto observer : observers){
		
		observer->cursorChanged(s, key, actor, target, position, rollback);
	}
	}
}
