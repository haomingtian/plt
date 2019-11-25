#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <memory>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include "render.h"
#include "engine.h"
using namespace std;
using namespace state;
using namespace render;
using namespace engine;

namespace render{
  class Surface;
};

int main(int argc,char* argv[])
{
	 if (argc>1){
		 if(strcmp(argv[1],"hello")==0){
		 cout << "bonjour tout le monde" << endl;
		}
		else if(strcmp(argv[1],"state")==0){
			UnityArmy unity = UnityArmy(ARCHER,"archerTest",true, 0, 0);
			int count_err = 0;
			
			cout<<"--- Tests unitaires ---"<<endl;
			
			unity.getStatistics().setCurrentLife(-5);
			unity.getStatistics().setAttack(-5);
			unity.getStatistics().setDefense(-5);
			
			if (unity.getStatistics().getCurrentLife() < 0){
				cerr << "Warning : Attribut PV negatif interdit" <<endl;
				count_err++;
			}
			if (unity.getStatistics().getAttack() < 0){
				cerr << "Warning : Attribut Attaque negatif interdit" <<endl;
				count_err++;
			}
			if (unity.getStatistics().getDefense() < 0){
				cerr << "Warning : Attribut Defense negatif interdit" <<endl;
				count_err++;
			}
			
			cout << "Tests unitaires termines avec " << count_err << " erreur(s)" <<endl;
			
		}
		else if(strcmp(argv[1],"render")==0){
			cout<<"--- Affichage d'un Etat ---"<<endl;
			
			unsigned int height_map_cases = 25, width_map_cases = 25;
			std::string chemin_fichier_map_txt = "/home/ensea/plt/ressources/map1.txt";
			Correspondence tab_corres = Correspondence();
			
			// -- Initialisation d'un state --
			
			State initial_state;
			if(initial_state.initGrid(chemin_fichier_map_txt, height_map_cases, width_map_cases, tab_corres)){
			cout << "Taille grille : " <<initial_state.getGrid().size() << "x" << initial_state.getGrid()[0].size() << endl;
			
			initial_state.initUnityArmy(tab_corres);
			initial_state.initCursor();
			cout << "Taille liste de personnages : " << initial_state.getUnityArmy().size() << endl;
			sf::RenderWindow window(sf::VideoMode(400,400),"Map");
			// -- Affichage de cet Etat --
			StateLayer layer(initial_state,window);	
			layer.initSurfaces(initial_state);
			
				while (window.isOpen()){
				sf::Event event;
				while (window.pollEvent(event)){
					if (event.type == sf::Event::Closed){
						window.close();
					}
				}
				
				window.clear();
				
				window.draw(*layer.getSurface()[0]);	// Dessin de la grille				
				window.draw(*layer.getSurface()[1]);	// Dessin des personnages
				window.display();
			}
			
		}
	 }
    
    /*
    // create the window
   
    sf::RenderWindow window(sf::VideoMode(700, 700), "Tilemap");
    //Correspondence tab_corres = Correspondence();
    //unsigned int long_cases = 25, larg_cases = 25;
	//std::string m = "/home/ensea/plt/ressources/map.txt";    
     // define the level with an array of tile indices
    const int level[] =
    {
        0, 1, 2, 3, 0, 1, 2, 3, 7, 1, 1, 2, 3, 4, 5, 5,8,7,4,5,2,3,7,4,
        0, 1, 1, 1, 1, 1, 1, 2, 4, 4, 0, 2, 0, 8, 1, 5,8,7,4,5,2,3,7,4,
        1, 1, 2, 3, 4, 0, 5, 4, 3, 3, 3, 3, 3, 3, 3, 4,8,7,4,5,2,0,7,4,
        0, 1, 0, 7, 2, 7, 3, 3, 3, 8, 1, 1, 1, 0, 0, 3,8,2,4,0,2,3,2,4,
        0, 1, 1, 2, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 2,8,7,4,1,2,3,7,4,
        2, 1, 1, 0, 3, 3, 6, 6, 4, 0, 1, 1, 1, 6, 2, 1,2,3,4,5,2,5,6,4,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 5, 5, 6, 0,8,7,4,1,2,3,7,4,
        0, 0, 1, 0, 3, 6, 5, 2, 0, 0, 0, 0, 1, 1, 1, 6,3,2,4,1,1,3,7,4,
    };
    
    //const int level_u[] =
    //{
       // 0, 1, 2, 3, 4, 
	//};
    //State s;
    //s.initGrid(level,long_cases,larg_cases,tab_corres);
    // create the tilemap from the level definition
    render::Surface map;
    if (!map.loadGrid("/home/ensea/plt/ressources/spritee.PNG", level, sf::Vector2u(46, 48), 25, 8))
        return -1;
    // run the main loop
    //placer les unityarmy à choisir
    sf::Texture texture;
    sf::RectangleShape rectangle(sf::Vector2f(150, 60));
    
    if (!texture.loadFromFile("/home/ensea/plt/ressources/UnityArmy.png"))
     return -1;
     
    rectangle.setTexture(&texture);
    rectangle.setPosition(0.f, 430.f);
    
    //placer les castles à choisir
    sf::Texture texture1;
    sf::RectangleShape rectangle1(sf::Vector2f(150, 60));
    
    if (!texture1.loadFromFile("/home/ensea/plt/ressources/Castles.png"))
     return -1;
     
    rectangle1.setTexture(&texture1);
    rectangle1.setPosition(0.f, 550.f);
    
    //placer les flêches
    sf::Texture texture2;
    sf::RectangleShape rectangle2(sf::Vector2f(150, 60));
    
    if (!texture2.loadFromFile("/home/ensea/plt/ressources/arrows_tileset.png"))
     return -1;
     
    rectangle2.setTexture(&texture2);
    rectangle2.setPosition(548.f, 550.f);
    
    //render::Surface army;
    //if (!army.loadGrid("/home/ensea/plt/ressources/UnityArmy.png", level_u, sf::Vector2u(46, 48), 5, 1))
        return -1;
        
    sf::Font police;
    police.loadFromFile("/home/ensea/plt/ressources/Pixellari.ttf");
    std::string chaine = "Army Choice";
    sf::Text text;
	text.setFont(police);
	text.setString(chaine);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(sf::Vector2f(5.f, 390.f));
	
	sf::Font police1;
    police1.loadFromFile("/home/ensea/plt/ressources/Pixellari.ttf");
    std::string chaine1 = "Castle Choice";
    sf::Text text1;
	text1.setFont(police1);
	text1.setString(chaine1);
	text1.setCharacterSize(25);
	text1.setFillColor(sf::Color::Red);
	text1.setPosition(sf::Vector2f(5.f, 520.f));
	
	sf::Font police2;
    police2.loadFromFile("/home/ensea/plt/ressources/Pixellari.ttf");
    std::string chaine2 = "Move";
    sf::Text text2;
	text2.setFont(police2);
	text2.setString(chaine2);
	text2.setCharacterSize(25);
	text2.setFillColor(sf::Color::Red);
	text2.setPosition(sf::Vector2f(600.f, 520.f));
	
	
	//sf::FloatRect textRect = text.getLocalBounds();
	//text.setOrigin((int)(textRect.left + textRect.width/2.0f),
		           //(int)(textRect.top  + textRect.height/2.0f));
	//text.setPosition(sf::Vector2f(10.f, 390.f));
	
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
        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(text);
        window.draw(text1);
        window.draw(text2);
        //window.draw(rectangle_1);
        //window.draw(army);
        window.display();
    }
    return 0;*/
}
}
