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
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");
    Correspondence tab_corres = Correspondence();
    unsigned int long_cases = 25, larg_cases = 25;
	std::string map = "/home/ensea/plt/ressources/map.txt";    
    State s;
    s.initGrid(map,long_cases,larg_cases,tab_corres);
     // define the level with an array of tile indices
    /*const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 4, 4, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 6, 6, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 5, 5, 6, 6,
        0, 0, 1, 0, 3, 5, 5, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };*/
     // create the tilemap from the level definition
    render::Surface map;
    if (!map.loadGrid("/home/ensea/plt/ressources/tile.png", sf::Vector2u(32, 32), map, 16, 8))
        return -1;

    // run the main loop
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
        window.display();
    }
    return 0;
}
