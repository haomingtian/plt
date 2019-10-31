#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "StateLayer.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <unistd.h>
using namespace state;
namespace render{
/*StateLayer::StateLayer(state::State& s, sf::RenderWindow& wind){
	//Dessin de la Grille
	TileSet tilesetGrid(GRIDTILESET);
	std::unique_ptr<TileSet> ptr_tilesetGrid (new TileSet(tilesetGrid));
	tileset.push_back(move(ptr_tilesetGrid));	
}
void StateLayer::draw (sf::RenderWindow& window){
	window.clear();
	window.create(sf::VideoMode(400,400),"ecran")
	sf::Texture map;
	map.loadFromFile("/home/ensea/plt/ressources/sprites_grille.png")
	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(0.f, 400.f);
	quad[1].position = sf::Vector2f(400.f, 400.f);
	quad[2].position = sf::Vector2f(400.f, 600.f);
	quad[3].position = sf::Vector2f(0.f, 600.f);
	
	quad[0].color = sf::Color::Blue;
	quad[1].color = sf::Color::Red;
	quad[2].color = sf::Color::Black;
	quad[3].color = sf::Color::Black; 
	
}
void StateLayer::initSurfaces (state::State& e){
	Surface surfGrid;
	
	surfGrid.loadGrid(e, tileset[0]->getTexture(), sf::Vector2u(tileset[0]->getCellWidth(), tileset[0]->getCellHeight()), e.getGrid().size(), e.getGrid()[0].size());
	
}*/
}
