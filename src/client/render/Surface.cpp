#include <string>
#include <iostream> 
#include "Surface.h"

namespace render{
bool Surface::loadGrid (const std::string&  tileset,const int* tiles , sf::Vector2u tile_size, unsigned int width, unsigned int heigth){
	if (!texture.loadFromFile(tileset))
            return false;
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	quads.setPrimitiveType(sf::Quads);
    quads.resize(width * heigth * 4);
    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < heigth; ++j)
            {
				// get the current tile number
                int tileNumber = tiles[i + j * width];
                // find its position in the tileset texture
                int tu = tileNumber % (texture.getSize().x / tile_size.x);
                int tv = tileNumber / (texture.getSize().x / tile_size.x);
                
                // get a pointer to the current tile's quad
                sf::Vertex* quad = &quads[(i + j * width) * 4];
                
                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
                quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j *tile_size.y);
                quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
                quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);
                
                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
                quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			}
			return true;
		}

bool Surface::loadUnityArmy (const std::string& tileset, const int* tiles, sf::Vector2u tile_size, unsigned int width, unsigned int heigth){
		if (!texture.loadFromFile(tileset))
            return false;
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	   	quads.setPrimitiveType(sf::Quads);
       	quads.resize(width * heigth * 4);
        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i){
        		/*//On met a jour les tuiles des personnages en fonction de leur statut
        		updateTilesPersonnages(etatLayer);*/
              	// on récupère le numéro de tuile courant
				int tileNumber=tiles[i];;
				
                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (texture.getSize().x / tile_size.x);
                int tv = tileNumber / (texture.getSize().x / tile_size.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &quads[i * 4];
                
                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tile_size.x, i * tile_size.y);
                quad[1].position = sf::Vector2f((i + 1) * tile_size.x, i *tile_size.y);
                quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (i + 1) * tile_size.y);
                quad[3].position = sf::Vector2f(i * tile_size.x, (i + 1) * tile_size.y);
                
                 // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
                quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			}
			return true;				
}	
void Surface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	    // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &texture;

        // et on dessine enfin le tableau de vertex
        target.draw(quads, states);
	
}
}

