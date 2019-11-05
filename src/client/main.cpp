#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
using namespace std;
using namespace state;
#include "render.h"
namespace render{
  class Surface;
};

int main(int argc,char* argv[])
{

    //cout << "bonjour " << argv[1]<< endl;
    
    // create the window
    
    sf::RenderWindow window(sf::VideoMode(700, 700), "Tilemap");
    /*Correspondence tab_corres = Correspondence();
    unsigned int long_cases = 25, larg_cases = 25;*/
	//std::string m = "/home/ensea/plt/ressources/map.txt";    
     // define the level with an array of tile indices
    const int level[] =
    {
        0, 0, 5, 8, 0, 0, 1, 1, 1, 1, 1, 1, 3, 7, 8, 5,8,7,4,5,2,3,7,4,
        0, 1, 1, 1, 1, 1, 1, 5, 4, 4, 0, 2, 0, 0, 0, 5,8,7,4,5,2,3,7,4,
        1, 1, 0, 0, 0, 0, 4, 4, 3, 3, 3, 3, 3, 3, 3, 4,8,7,4,5,2,3,7,4,
        0, 1, 0, 0, 2, 7, 3, 3, 3, 8, 1, 1, 1, 0, 0, 3,8,7,4,5,2,3,7,4,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 2,8,7,4,5,2,3,7,4,
        0, 0, 1, 0, 3, 0, 6, 6, 4, 0, 1, 1, 1, 1, 2, 1,8,7,4,5,2,3,7,4,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 5, 5, 6, 0,8,7,4,5,2,3,7,4,
        0, 0, 1, 0, 3, 5, 5, 2, 0, 0, 0, 0, 1, 1, 1, 6,8,7,4,5,1,3,7,4,
    };
    
    /*const int level_u[] =
    {
        0, 1, 2, 3, 4, 
	};*/
    /*State s;
    s.initGrid(level,long_cases,larg_cases,tab_corres);*/
    // create the tilemap from the level definition
    render::Surface map;
    if (!map.loadGrid("/home/ensea/plt/ressources/spritee.PNG", level, sf::Vector2u(46, 48), 25, 8))
        return -1;
    // run the main loop
    sf::Texture texture;
    sf::RectangleShape rectangle(sf::Vector2f(150, 60));
    
    if (!texture.loadFromFile("/home/ensea/plt/ressources/UnityArmy.png"))
     return -1;
     
    rectangle.setTexture(&texture);
    rectangle.setPosition(0.f, 430.f);
    render::Surface army;
    /*if (!army.loadGrid("/home/ensea/plt/ressources/UnityArmy.png", level_u, sf::Vector2u(46, 48), 5, 1))
        return -1;*/
        
    sf::Font police;
    police.loadFromFile("/home/ensea/plt/ressources/Pixellari.ttf");
    std::string chaine = "Army Choice";
    sf::Text text;
	text.setFont(police);
	text.setString(chaine);
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(sf::Vector2f(10.f, 390.f));
	
	sf::RectangleShape rectangle_1(sf::Vector2f(80, 60));
	rectangle_1.setFillColor(sf::Color::Red);
	rectangle_1.setPosition(10.f, 390.f);
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // draw the map
        window.clear();
        window.draw(map);
        window.draw(rectangle);
        window.draw(text);
        window.draw(rectangle_1);
        //window.draw(army);
        window.display();
    }
    return 0;
}
