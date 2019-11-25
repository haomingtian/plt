#include <string>
#include <iostream> 
#include "Surface.h"

namespace render{
bool Surface::loadGrid (state::State& s_layer, sf::Texture& texture_t, sf::Vector2u tile_size, unsigned int width, unsigned int height){
	texture=texture_t;
	/*if (!texture.loadFromFile(tileset))
            return false;*/
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	quads.setPrimitiveType(sf::Quads);
    quads.resize(width * height * 4);
    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i){
            for (unsigned int j = 0; j < height; ++j)
            {
				// get the current tile number
				
                int tileNumber = s_layer.getGrid()[i][j]->getCodeTuile();
                
                // find its position in the tileset texture
                int tu = tileNumber % (texture.getSize().x / tile_size.x);
                int tv = tileNumber / (texture.getSize().x / tile_size.x);
                
                // get a pointer to the current tile's quad
                sf::Vertex* quad = &quads[(i + j * width) * 4];
                
                // define its 4 corners
                quad[0].position = sf::Vector2f(s_layer.getGrid()[j][i]->getPosition().getX() * tile_size.x, s_layer.getGrid()[j][i]->getPosition().getY() * tile_size.y);
                quad[1].position = sf::Vector2f((s_layer.getGrid()[j][i]->getPosition().getX()+ 1) * tile_size.x, s_layer.getGrid()[j][i]->getPosition().getY() * tile_size.y);
                quad[2].position = sf::Vector2f((s_layer.getGrid()[j][i]->getPosition().getX() + 1) * tile_size.x, (s_layer.getGrid()[j][i]->getPosition().getY() + 1) * tile_size.y);
                quad[3].position = sf::Vector2f(s_layer.getGrid()[j][i]->getPosition().getX() * tile_size.x, (s_layer.getGrid()[j][i]->getPosition().getY() + 1) * tile_size.y);
                
                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
                quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			}
			return true;
		}
	}

bool Surface::loadUnityArmy (state::State& s_layer, sf::Texture& texture_t, sf::Vector2u tile_size, unsigned int width, unsigned int height){
		/*if (!texture.loadFromFile(tileset))
            return false;*/
        texture= texture_t;
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	   	quads.setPrimitiveType(sf::Quads);
       	quads.resize(width * height * 4);
        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i){
        		//On met a jour les tuiles des personnages en fonction de leur statut
        		updateTilesUnity(s_layer);
              	// on récupère le numéro de tuile courant
				int tileNumber=s_layer.getUnityArmy()[i]->getCodeTuile();;
				
                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (texture.getSize().x / tile_size.x);
                int tv = tileNumber / (texture.getSize().x / tile_size.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &quads[i * 4];
                
                // define its 4 corners
                quad[0].position = sf::Vector2f(s_layer.getUnityArmy()[i]->getPosition().getX() * tile_size.x, s_layer.getUnityArmy()[i]->getPosition().getY() * tile_size.y);
                quad[1].position = sf::Vector2f((s_layer.getUnityArmy()[i]->getPosition().getX()+ 1) * tile_size.x, s_layer.getUnityArmy()[i]->getPosition().getY() * tile_size.y);
                quad[2].position = sf::Vector2f((s_layer.getUnityArmy()[i]->getPosition().getX() + 1) * tile_size.x, (s_layer.getUnityArmy()[i]->getPosition().getY() + 1) * tile_size.y);
                quad[3].position = sf::Vector2f(s_layer.getUnityArmy()[i]->getPosition().getX() * tile_size.x, (s_layer.getUnityArmy()[i]->getPosition().getY() + 1) * tile_size.y);
                
                 // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
                quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			}
			return true;				
}	
bool Surface::loadCastles (state::State& s_layer, sf::Texture& texture_t, sf::Vector2u tile_size, unsigned int width, unsigned int height){
	texture= texture_t;
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	   	quads.setPrimitiveType(sf::Quads);
       	quads.resize(width * height * 4);
        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i){
        		//On met a jour les tuiles des personnages en fonction de leur statut
        		//updateTilesUnity(s_layer);
              	// on récupère le numéro de tuile courant
				int tileNumber=s_layer.getCastle()[i]->getCodeTuile();;
				
                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (texture.getSize().x / tile_size.x);
                int tv = tileNumber / (texture.getSize().x / tile_size.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &quads[i * 4];
                
                // define its 4 corners
                quad[0].position = sf::Vector2f(s_layer.getCastle()[i]->getPosition().getX() * tile_size.x, s_layer.getCastle()[i]->getPosition().getY() * tile_size.y);
                quad[1].position = sf::Vector2f((s_layer.getCastle()[i]->getPosition().getX()+ 1) * tile_size.x, s_layer.getCastle()[i]->getPosition().getY() * tile_size.y);
                quad[2].position = sf::Vector2f((s_layer.getCastle()[i]->getPosition().getX() + 1) * tile_size.x, (s_layer.getCastle()[i]->getPosition().getY() + 1) * tile_size.y);
                quad[3].position = sf::Vector2f(s_layer.getCastle()[i]->getPosition().getX() * tile_size.x, (s_layer.getCastle()[i]->getPosition().getY() + 1) * tile_size.y);
                
                 // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
                quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			}
			return true;	
}
bool Surface::loadCursor (state::State& s_layer, sf::Texture& texture_t, sf::Vector2u tile_size, unsigned int width, unsigned int height){
		texture= texture_t;
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	   	quads.setPrimitiveType(sf::Quads);
       	quads.resize(width * height * 4);
        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i){
        		//On met a jour les tuiles des personnages en fonction de leur statut
        		//updateTilesUnity(s_ayer);
              	// on récupère le numéro de tuile courant
				int tileNumber=s_layer.getCursor()->getCodeTuile();;
				
                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (texture.getSize().x / tile_size.x);
                int tv = tileNumber / (texture.getSize().x / tile_size.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &quads[i * 4];
                
                // define its 4 corners
                quad[0].position = sf::Vector2f(s_layer.getCursor()->getPosition().getX() * tile_size.x, s_layer.getCursor()->getPosition().getY() * tile_size.y);
                quad[1].position = sf::Vector2f((s_layer.getCursor()->getPosition().getX()+ 1) * tile_size.x, s_layer.getCursor()->getPosition().getY() * tile_size.y);
                quad[2].position = sf::Vector2f((s_layer.getCursor()->getPosition().getX() + 1) * tile_size.x, (s_layer.getCursor()->getPosition().getY() + 1) * tile_size.y);
                quad[3].position = sf::Vector2f(s_layer.getCursor()->getPosition().getX() * tile_size.x, (s_layer.getCursor()->getPosition().getY() + 1) * tile_size.y);
                
                 // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
                quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			}
			return true;
}

bool Surface::loadInfos (state::State& s_layer, sf::Texture& texture_t, sf::Vector2u tile_size, unsigned int width, unsigned int height){
		texture= texture_t;
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	   	quads.setPrimitiveType(sf::Quads);
       	quads.resize(width * height * 4);
       	for (unsigned int i = 0; i < width; ++i){
			if(s_layer.getUnityArmy()[i]->getStatus()==state::SELECTED || s_layer.getUnityArmy()[i]->getStatus()==state::TARGET){
				int tileNumber=s_layer.getUnityArmy()[i]->getCodeTuile();;
				
                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (texture.getSize().x / tile_size.x);
                int tv = tileNumber / (texture.getSize().x / tile_size.x);
                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &quads[i * 4];
                
                if (s_layer.getUnityArmy()[i]->getCamp()==true){
				quad[0].position = sf::Vector2f(5+64,440);
				quad[1].position = sf::Vector2f(0+5,440);
				quad[3].position = sf::Vector2f(5+64,440+64);
				quad[2].position = sf::Vector2f(0+5,440+64);
			}
				
			// Personnage Adverse
			else{
				quad[0].position = sf::Vector2f(400-5-64,440);
				quad[1].position = sf::Vector2f(400-5,440);
				quad[2].position = sf::Vector2f(400-5,440+64);
				quad[3].position = sf::Vector2f(400-5-64,440+64);		
			}
			                 // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
                quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			}
		
		}
		return true;
}
void Surface::updateTilesUnity (state::State& s_layer){
	for (unsigned int i = 0; i < s_layer.getUnityArmy().size(); i++){
		if (s_layer.getUnityArmy()[i]->getStatus() == state::AVAILABLE){
			if (s_layer.getUnityArmy()[i]->getCamp() == true){
				if (s_layer.getUnityArmy()[i]->getType() == state::INGENEER){
					s_layer.getUnityArmy()[i]->setCodeTuile(0);
				}
				else if (s_layer.getUnityArmy()[i]->getType() == state::CAVLRY){
					s_layer.getUnityArmy()[i]->setCodeTuile(1);
				}
				else if (s_layer.getUnityArmy()[i]->getType() == state::ARCHER){
					s_layer.getUnityArmy()[i]->setCodeTuile(2);
				}
				if (s_layer.getUnityArmy()[i]->getType() == state::INFANTRY){
					s_layer.getUnityArmy()[i]->setCodeTuile(3);
				}
				else if (s_layer.getUnityArmy()[i]->getType() == state::LANCER){
					s_layer.getUnityArmy()[i]->setCodeTuile(4);
				}
			}
			else if (s_layer.getUnityArmy()[i]->getCamp() == false){
				if (s_layer.getUnityArmy()[i]->getType() == state::INGENEER){
					s_layer.getUnityArmy()[i]->setCodeTuile(5);
				}
				else if (s_layer.getUnityArmy()[i]->getType() == state::CAVLRY){
					s_layer.getUnityArmy()[i]->setCodeTuile(6);
				}
				else if (s_layer.getUnityArmy()[i]->getType() == state::ARCHER){
					s_layer.getUnityArmy()[i]->setCodeTuile(7);
				}
				if (s_layer.getUnityArmy()[i]->getType() == state::INFANTRY){
					s_layer.getUnityArmy()[i]->setCodeTuile(8);
				}
				else if (s_layer.getUnityArmy()[i]->getType() == state::LANCER){
					s_layer.getUnityArmy()[i]->setCodeTuile(9);
				}
			}
		
			else if (s_layer.getUnityArmy()[i]->getStatus() == state::WAITING){
				if (s_layer.getUnityArmy()[i]->getType() == state::INGENEER){
						s_layer.getUnityArmy()[i]->setCodeTuile(10);
					}
					else if (s_layer.getUnityArmy()[i]->getType() == state::CAVLRY){
						s_layer.getUnityArmy()[i]->setCodeTuile(11);
					}
					else if (s_layer.getUnityArmy()[i]->getType() == state::ARCHER){
						s_layer.getUnityArmy()[i]->setCodeTuile(12);
					}
					if (s_layer.getUnityArmy()[i]->getType() == state::INFANTRY){
						s_layer.getUnityArmy()[i]->setCodeTuile(13);
					}
					else if (s_layer.getUnityArmy()[i]->getType() == state::LANCER){
						s_layer.getUnityArmy()[i]->setCodeTuile(14);
					}
			}
		
			else if (s_layer.getUnityArmy()[i]->getStatus() == state::DEAD){
				s_layer.getUnityArmy()[i]->setCodeTuile(15);
			}		
		}
	}
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

