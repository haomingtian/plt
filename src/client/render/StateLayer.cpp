#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "StateLayer.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <unistd.h>
#include "state.h"

using namespace state;
namespace render{
StateLayer::StateLayer(state::State& newState, sf::RenderWindow& newWindow)
: state(newState)
{
	//Dessin de la Grille
	TileSet tilesetGrid(GRIDTILESET);
	std::unique_ptr<TileSet> ptr_tilesetGrid (new TileSet(tilesetGrid));
    tileSets.push_back(move(ptr_tilesetGrid));
}

StateLayer::StateLayer(state::State &newState)
        : state(newState)
{
    police.loadFromFile("./ressources/Pixellari.ttf");

    TileSet tilesetGrille(GRIDTILESET);
    std::unique_ptr<TileSet> ptr_tilesetGrille (new TileSet(tilesetGrille));
    tileSets.push_back(move(ptr_tilesetGrille));

    TileSet tilesetPersonnages(UNITYARMYTILESET);
    std::unique_ptr<TileSet> ptr_tilesetPersonnages (new TileSet(tilesetPersonnages));
    tileSets.push_back(move(ptr_tilesetPersonnages));

    TileSet tilesetCursor(CURSORTILESET);
    std::unique_ptr<TileSet> ptr_tilesetCursor (new TileSet(tilesetCursor));
    tileSets.push_back(move(ptr_tilesetCursor));

    TileSet tilesetInfos(INFOSTILESET);
    std::unique_ptr<TileSet> ptr_tilesetInfos (new TileSet(tilesetInfos));
    tileSets.push_back(move(ptr_tilesetInfos));
}

void StateLayer::draw (sf::RenderWindow& window, const state::StateEvent& e){
    window.clear();

    // Rectangle degrade en (0,400) et de taille 400x200
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(0.f, 775.0f);
    quad[1].position = sf::Vector2f(775.0f, 775.0f);
    quad[2].position = sf::Vector2f(775.0f, 975.0f);
    quad[3].position = sf::Vector2f(0.f, 975.0f);
    quad[0].color = sf::Color::Blue;
    quad[1].color = sf::Color::Red;
    quad[2].color = sf::Color::Black;
    quad[3].color = sf::Color::Black;

    // Rectangle noir pour les messages
    sf::RectangleShape rectangle(sf::Vector2f(765.f, 30.f));
    rectangle.setPosition(5.f, 780.f);
    rectangle.setFillColor(sf::Color::Black);

    window.draw(*surfaces[0]);	// Draw grid
    window.draw(*surfaces[1]);	// Draw unity armies
    window.draw(*surfaces[2]);  // Draw cursor
    window.draw(quad);
    window.draw(rectangle);
    window.draw(*surfaces[3]); // Draw infos

    if (e.eventId == TEXTCHANGED)
    {
        writeTexteAction(e.text, window);
    }

    window.display();
}
void StateLayer::initSurfaces (state::State& e){
	Surface surfaceGrid;
    Surface surfaceUnityArmy;
    Surface surfaceCursor;
    Surface surfInfos;

    surfaceGrid.loadGrid(e, tileSets[0]->getImageFile(), sf::Vector2u(tileSets[0]->getCellWidth(), tileSets[0]->getCellHeight()), e.getGrid().size(), e.getGrid()[0].size());

    surfaceUnityArmy.loadUnityArmy(e, tileSets[1]->getImageFile(), sf::Vector2u(tileSets[1]->getCellWidth(), tileSets[1]->getCellHeight()), e.getUnityArmys().size(), 1);

    surfaceCursor.loadCursor(e, tileSets[2]->getImageFile(), sf::Vector2u(tileSets[2]->getCellWidth(), tileSets[2]->getCellHeight()), 1, 1);

    surfInfos.loadInfos(e, tileSets[3]->getTexture(), sf::Vector2u(tileSets[3]->getCellWidth(), tileSets[3]->getCellHeight()), 1, 1);

    std::unique_ptr<Surface> ptr_surfaceGrid (new Surface(surfaceGrid));
    std::unique_ptr<Surface> ptr_surfaceUnityArmy (new Surface(surfaceUnityArmy));
    std::unique_ptr<Surface> ptr_surfaceCursor(new Surface(surfaceCursor));
    std::unique_ptr<Surface> ptr_surfInfos (new Surface(surfInfos));

    if(surfaces.size()!=0){
        while(surfaces.size()!=0){
            surfaces.pop_back();
        }
    }

    surfaces.push_back(move(ptr_surfaceGrid));
    surfaces.push_back(move(ptr_surfaceUnityArmy));
    surfaces.push_back(move(ptr_surfaceCursor));
    surfaces.push_back(move(ptr_surfInfos));
}

void StateLayer::stateChanged (const state::StateEvent& e, state::State& s, sf::RenderWindow& window)
{
    initSurfaces(s);
    draw(window, e);

    if (e.eventId == PLAYERCHANGED)
    {
        writeStatistiques(e.text, e.infos, window);
    }
}

std::vector<std::unique_ptr<TileSet>>& StateLayer::getTileSets (){
    std::vector<std::unique_ptr<TileSet>>& ref_tilesets = tileSets;
    return ref_tilesets;
}

std::vector<std::unique_ptr<Surface>>& StateLayer::getSurfaces ()
{
    std::vector<std::unique_ptr<Surface>>& ref_surfaces = surfaces;
    return ref_surfaces;
}

// Setters and Getters
const sf::Font& StateLayer::getPolice() const
{
    return police;
}

void StateLayer::writeTexteAction(const std::string& chaine, sf::RenderWindow& window){
//    window.clear();

    sf::RectangleShape rectangle(sf::Vector2f(765.f, 30.f));
    rectangle.setPosition(5.f, 780.f);
    rectangle.setFillColor(sf::Color::Black);

    sf::Text text;
    text.setFont(police);
    text.setString(chaine);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 775.f);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin((int)(textRect.left + textRect.width/2.0f),
                   (int)(textRect.top  + textRect.height/2.0f));
    text.setPosition(sf::Vector2f(775/2.0f, 795));

    window.draw(rectangle);
    window.draw(text);
//    window.display();
}

void StateLayer::writeStatistiques(const std::string& name, const std::string& statisticValue, sf::RenderWindow& window){
    // Rectangle noir de Statistiques
    sf::RectangleShape rectangle2(sf::Vector2f(100.f, 102.f));
    rectangle2.setPosition(5+64+5, 775+5+30+5);
    rectangle2.setFillColor(sf::Color::Black);

    char buffer[256];

    sprintf(buffer, "%s\nPV\nAtk\nDef\nEsq\nCrt", name.c_str());

    std::string chaine0 = "Oliver\nPV\nAtk\nDef\nEsq\nCrt";
    sf::Text text;
    text.setFont(police);
    text.setString(buffer);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setPosition(5+64+5+4,775+5+30+5+2);

    std::string chaine2 = "\n:\t100\n:\t50\n:\t30\n:\t10\n:\t30";
    sf::Text text2;
    text2.setFont(police);
    text2.setString(statisticValue);
    text2.setCharacterSize(15);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(5+64+5+4+30,775+5+30+5+2);

    window.draw(rectangle2);
    window.draw(text);
    window.draw(text2);
//    window.display();
}


}
