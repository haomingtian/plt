#include <iostream> 
#include "Scene.h"
using namespace std;
namespace render {
void draw (sf::RenderWindow window){
	window.create(sf::VideoMode(900,900),"ecran");
	sf::Texture map;
	sf::VertexArray quad(sf::Quads, 4);
	map.loadFromFile("/home/ensea/plt/ressources/sprites_grille.png");
	quad[0].position = sf::Vector2f(0.f, 400.f);
	quad[1].position = sf::Vector2f(400.f, 400.f);
	quad[2].position = sf::Vector2f(400.f, 600.f);
	quad[3].position = sf::Vector2f(0.f, 600.f);
	
	quad[0].color = sf::Color::Blue;
	quad[1].color = sf::Color::Red;
	quad[2].color = sf::Color::Black;
	quad[3].color = sf::Color::Black; 
	 while(window.isOpen())
    {
		sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(quad, &map);
        window.display();
    }
}
}
