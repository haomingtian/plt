#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "StateLayer.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <unistd.h>
using namespace std;
using namespace state;
namespace render{
StateLayer::StateLayer(state::State& s, sf::RenderWindow& wind): window(wind){
	police.loadFromFile("/home/ensea/plt/ressources/Pixellari.ttf");
	//Dessin de la Grille
	TileSet tilesetGrid(GRIDTILESET);
	std::unique_ptr<TileSet> ptr_tilesetGrid (new TileSet(tilesetGrid));
	tileset.push_back(move(ptr_tilesetGrid));
	
	TileSet tilesetunity(UNITYARMYTILESET);
	std::unique_ptr<TileSet> ptr_tilesetu (new TileSet(tilesetunity));
	tileset.push_back(move(ptr_tilesetu));
	
	TileSet tilesetcur(CURSORTILESET);
	std::unique_ptr<TileSet> ptr_tilesetCurseur (new TileSet(tilesetcur));
	tileset.push_back(move(ptr_tilesetCurseur));

	TileSet tilesetInfos(INFOSTILESET);
	std::unique_ptr<TileSet> ptr_tilesetInfos (new TileSet(tilesetInfos));
	tileset.push_back(move(ptr_tilesetInfos));	
}

void StateLayer::initSurfaces (state::State& e){
	Surface surf_grid;
	Surface surf_unity;
	Surface surf_infos;
	Surface surf_castle;
	Surface surf_cursor;
	
	surf_grid.loadGrid(e, tileset[0]->getTexture(), sf::Vector2u(tileset[0]->getCellWidth(), tileset[0]->getCellHeight()), e.getGrid().size(), e.getGrid()[0].size());
	surf_unity.loadUnityArmy(e, tileset[1]->getTexture(), sf::Vector2u(tileset[1]->getCellWidth(), tileset[1]->getCellHeight()), e.getUnityArmy().size(), e.getUnityArmy().size());
	surf_castle.loadCastles(e, tileset[2]->getTexture(), sf::Vector2u(tileset[2]->getCellWidth(), tileset[2]->getCellHeight()), e.getCastle().size(), e.getCastle().size());
	surf_castle.loadCursor(e, tileset[3]->getTexture(), sf::Vector2u(tileset[3]->getCellWidth(), tileset[3]->getCellHeight()), 1,1);
	
	std::unique_ptr<Surface> ptr_surf_g (new Surface(surf_grid));
	std::unique_ptr<Surface> ptr_surf_u (new Surface(surf_unity));
	std::unique_ptr<Surface> ptr_surf_c (new Surface(surf_castle));
	std::unique_ptr<Surface> ptr_surf_cu (new Surface(surf_cursor));
	//std::unique_ptr<Surface> ptr_surfInfos (new Surface(surfInfos));
	
	if(surface.size()!=0){
		while(surface.size()!=0){
			surface.pop_back();
		}
	}
	
	surface.push_back(move(ptr_surf_g));
	surface.push_back(move(ptr_surf_u));
	surface.push_back(move(ptr_surf_c));
	//surface.push_back(move(ptr_surf_c));
	
}
void StateLayer::stateChanged (const state::Event& e, state::State& s){
		if (e.event_id == ALLCHANGED){
		initSurfaces(s);
		draw(window);
	}
	if (e.event_id == TEXTCHANGED){
		draw(window);
		writeTexteAction(e.text, window);
		//writeStatistiques(e.texte, e.texteSup, window);
	}
	if (e.event_id == UNITYARMYCHANGED){
		writeStatistiques(e.text_infos, e.text_stats, window, e.camp);
	}
}
void StateLayer::writeTexteAction (const std::string chaine, sf::RenderWindow& window){
}
void StateLayer::writeStatistiques (const std::string chaine1, const std::string chaine2, sf::RenderWindow& window, bool camp){
}
void StateLayer::draw (sf::RenderWindow& window){
	window.clear();
	window.create(sf::VideoMode(400,400),"ecran");
	sf::Texture map;
	map.loadFromFile("/home/ensea/plt/ressources/spritee.PNG");
	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(0.f, 400.f);
	quad[1].position = sf::Vector2f(400.f, 400.f);
	quad[2].position = sf::Vector2f(400.f, 600.f);
	quad[3].position = sf::Vector2f(0.f, 600.f);
	
	quad[0].color = sf::Color::Blue;
	quad[1].color = sf::Color::Red;
	quad[2].color = sf::Color::Black;
	quad[3].color = sf::Color::Black; 
	
	// Rectangle noir pour les messages
	sf::RectangleShape rectangle(sf::Vector2f(390.f, 30.f));
	rectangle.setPosition(5.f, 405.f);
	
	sf::Color colorRect(0,0,0,150);
	rectangle.setFillColor(colorRect);
	
	window.draw(*surface[0]);	// Dessin de la grille				
	window.draw(*surface[1]);	// Dessin des unity
	window.draw(*surface[2]);	// Dessin des chateaux
	window.draw(*surface[3]);	// Dessin du curseur
	window.draw(quad);
	window.draw(rectangle);
	//window.draw(*surfaces[3]); // Dessin des infos
	window.display();
	
}
void StateLayer::gestionCursor (sf::Event n_event, unsigned int width_map_cases, unsigned int height_map_cases, state::State& current_state, bool rollback){
	Event stateevent(ALLCHANGED);
	if (n_event.type==sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
		 cout << "ROLLBACK ! : ";
		 
		CursorEvent cursorevent0(R);
		Position nextPos0(0, 0);
		notifyObservers(current_state, cursorevent0.key, -1, -1, nextPos0,rollback);
		
		// Test pour changement de couleur du curseur si le rollback est declenché alors qu'un personnage est selectionne et n'a effectue aucune action
		bool unity_selected = false;
		for (size_t i = 0; i<current_state.getUnityArmy().size(); i++){
			if (current_state.getUnityArmy()[i]->getStatus() == state::SELECTED){
				unity_selected = true;
				break;
			}
		}
		if(!unity_selected){
			current_state.getCursor()->setCodeTuile(0);
		}
		current_state.notifyObservers(stateevent, current_state);
		cout << "FIN DU ROLLBACK" << endl;
	}
	// Actions avec personnage selectionne
	else if(n_event.type==sf::Event::KeyPressed && (current_state.verifStatus()!=-1)){
		
		int changementX = 0, changementY = 0;
		int num_unit=current_state.verifStatus();
		size_t x_unit=current_state.getUnityArmy()[num_unit]->getPosition().getX();
		size_t y_unit=current_state.getUnityArmy()[num_unit]->getPosition().getY();
		
		// Fleches directionnelles (deplacement du curseur et du personnage)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(x_unit!=width_map_cases-1){changementX = 1;}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(x_unit!=0){changementX = -1;}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if(y_unit!=0){changementY = -1;}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if(y_unit!=height_map_cases-1){changementY = 1;}
		}
		
		// Touche Z : Fin de tour d'actions
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){							

			CursorEvent cursor_event3(Z);
			CursorEvent cursor_event4(UPDATE);		
			Position nextPos1(0, 0);
			notifyObservers(current_state, cursor_event3.key, num_unit, -1, nextPos1, rollback);						
			current_state.getCursor()->setCodeTuile(0);
			//update();
			notifyObservers(current_state, cursor_event4.key, -1, -1, nextPos1, rollback);
		}
		
		// Deplacement du curseur et du personnage selectionne
		if (changementX != 0 || changementY != 0){
			Position nextPos(x_unit+changementX, y_unit+changementY);
			Position nextPos3(0, 0);

			CursorEvent cursorevent5(M);
			CursorEvent cursorevent6(UPDATE);
			notifyObservers(current_state, cursorevent5.key, num_unit, -1, nextPos, rollback);				
			current_state.getCursor()->move(nextPos);
			//update();
			notifyObservers(current_state, cursorevent6.key, -1, -1, nextPos3, rollback);
								
			changementX = 0;
			changementY = 0;
		}
	
	}
}
std::vector<std::unique_ptr<Surface>>& StateLayer::getSurface (){
	std::vector<std::unique_ptr<Surface>>& ref_surfaces = surface;
	return ref_surfaces;
}
std::vector<std::unique_ptr<TileSet>>& StateLayer::getTileset (){
	std::vector<std::unique_ptr<TileSet>>& ref_tilesets = tileset;
	return ref_tilesets;
}
}
