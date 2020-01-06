#include <string>
#include <iostream> 
#include "Surface.h"
#include "state/State.h"
#include "state/Correspondence.h"

namespace render{

bool Surface::loadInfos(state::State& stateLayer, sf::Texture& textureTileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    texture = textureTileset;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    quads.setPrimitiveType(sf::Quads);
    quads.resize(width * height * 4);

    // on récupère le numéro de tuile courant
    int tileNumber=8;
    int indicePerso=-1;

    for (size_t i = 0; i< stateLayer.getUnityArmys().size(); i++){
        if (stateLayer.getUnityArmys()[i]->getStatus()==state::SELECTED){
            tileNumber = stateLayer.getUnityArmys()[i]->getCodeTuile();
            indicePerso = i;
            break;
        }
    }

    // on en déduit sa position dans la texture du tileset
    int tu = tileNumber % (texture.getSize().x / tileSize.x);
    int tv = tileNumber / (texture.getSize().x / tileSize.x);

    // on récupère un pointeur vers le quad à définir dans le tableau de vertex
    sf::Vertex* quad = &quads[0];
    if(indicePerso!=-1){
        // Personnage de l'armee bleue affiché à gauche
        if (stateLayer.getUnityArmys()[indicePerso]->getCamp()==true){
            quad[0].position = sf::Vector2f(5+64,815);
            quad[1].position = sf::Vector2f(0+5,815);
            quad[3].position = sf::Vector2f(5+64,815+64);
            quad[2].position = sf::Vector2f(0+5,815+64);
        }

            // Personnage de l'armee rouge affiché à droite
        else{
            quad[0].position = sf::Vector2f(775-5-64,815);
            quad[1].position = sf::Vector2f(775-5,815);
            quad[2].position = sf::Vector2f(775-5,815+64);
            quad[3].position = sf::Vector2f(775-5-64,815+64);
        }
    }

    // on définit ses quatre coordonnées de texture
    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

    return true;
}

bool Surface::loadGrid (state::State& stateLayer, const std::string& tileSet, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    // on charge la texture du tileset
    if (!texture.loadFromFile(tileSet)){
        return false;
    }
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    quads.setPrimitiveType(sf::Quads);
    quads.resize(width * height * 4);

    state::Correspondence correspondence;

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; i++){
        for (unsigned int j = 0; j < height; j++){

            // on récupère le numéro de tuile courant
            int tileNumber=stateLayer.getGrid()[i][j]->getCodeTuile();

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (texture.getSize().x / tileSize.x);
            int tv = tileNumber / (texture.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &quads[(i + j * width) * 4];

            if (correspondence.getCorrespondenceNonPraticable().find(tileNumber) != correspondence.getCorrespondenceNonPraticable().end())
            {
                quad[0].color.a = 122;
                quad[1].color.a = 122;
                quad[2].color.a = 122;
                quad[3].color.a = 122;
            }

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(stateLayer.getGrid()[j][i]->getPosition().getX() * tileSize.x, stateLayer.getGrid()[j][i]->getPosition().getY() * tileSize.y) * 0.5f;
            quad[1].position = sf::Vector2f((stateLayer.getGrid()[j][i]->getPosition().getX()+ 1) * tileSize.x, stateLayer.getGrid()[j][i]->getPosition().getY() * tileSize.y) * 0.5f;
            quad[2].position = sf::Vector2f((stateLayer.getGrid()[j][i]->getPosition().getX() + 1) * tileSize.x, (stateLayer.getGrid()[j][i]->getPosition().getY() + 1) * tileSize.y) * 0.5f;
            quad[3].position = sf::Vector2f(stateLayer.getGrid()[j][i]->getPosition().getX() * tileSize.x, (stateLayer.getGrid()[j][i]->getPosition().getY() + 1) * tileSize.y) * 0.5f;

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        }
    }


    return true;
}

bool Surface::loadUnityArmy (state::State& stateLayer, const std::string& tileSet, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    // on charge la texture du tileset
    if (!texture.loadFromFile(tileSet)){
        return false;
    }
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    quads.setPrimitiveType(sf::Quads);
    quads.resize(width * height * 4);

    float multiplier = 3.87f * 0.5f;

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i){
        //On met a jour les tuiles des personnages en fonction de leur statut
        updateUnityArmys(stateLayer);
        // on récupère le numéro de tuile courant
        int tileNumber=stateLayer.getUnityArmys()[i]->getCodeTuile();

        // on en déduit sa position dans la texture du tileset
        int tu = tileNumber % (texture.getSize().x / tileSize.x);
        int tv = tileNumber / (texture.getSize().x / tileSize.x);

        // on récupère un pointeur vers le quad à définir dans le tableau de vertex
        sf::Vertex* quad = &quads[i * 4];

        // on définit ses quatre coins
        quad[0].position = sf::Vector2f(stateLayer.getUnityArmys()[i]->getPosition().getX() * tileSize.x, stateLayer.getUnityArmys()[i]->getPosition().getY() * tileSize.y) * multiplier;
        quad[1].position = sf::Vector2f((stateLayer.getUnityArmys()[i]->getPosition().getX()+ 1) * tileSize.x, stateLayer.getUnityArmys()[i]->getPosition().getY() * tileSize.y) * multiplier;
        quad[2].position = sf::Vector2f((stateLayer.getUnityArmys()[i]->getPosition().getX() + 1) * tileSize.x, (stateLayer.getUnityArmys()[i]->getPosition().getY() + 1) * tileSize.y) * multiplier;
        quad[3].position = sf::Vector2f(stateLayer.getUnityArmys()[i]->getPosition().getX() * tileSize.x, (stateLayer.getUnityArmys()[i]->getPosition().getY() + 1) * tileSize.y) * multiplier;

        // on définit ses quatre coordonnées de texture
        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }

    return true;
}

void Surface::updateUnityArmys (state::State& stateLayer)
{
    for (unsigned int i = 0; i < stateLayer.getUnityArmys().size(); i++){
        if (stateLayer.getUnityArmys()[i]->getStatus() == state::AVAILABLE){
            if (stateLayer.getUnityArmys()[i]->getCamp() == true){
                if (stateLayer.getUnityArmys()[i]->getType() == state::ARCHER){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(0);
                }
                else if (stateLayer.getUnityArmys()[i]->getType() == state::INGENEER){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(1);
                }
                else if (stateLayer.getUnityArmys()[i]->getType() == state::INFANTRY){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(2);
                }
                if (stateLayer.getUnityArmys()[i]->getType() == state::LANCER){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(3);
                }
            }
            else if (stateLayer.getUnityArmys()[i]->getCamp() == false){
                if (stateLayer.getUnityArmys()[i]->getType() == state::ARCHER){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(4);
                }
                else if (stateLayer.getUnityArmys()[i]->getType() == state::INGENEER){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(5);
                }
                else if (stateLayer.getUnityArmys()[i]->getType() == state::INFANTRY){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(6);
                }
                if (stateLayer.getUnityArmys()[i]->getType() == state::LANCER){
                    stateLayer.getUnityArmys()[i]->setCodeTuile(7);
                }
            }
        }

        else if (stateLayer.getUnityArmys()[i]->getStatus() == state::WAITING){
            if (stateLayer.getUnityArmys()[i]->getType() == state::ARCHER){
                stateLayer.getUnityArmys()[i]->setCodeTuile(8);
            }
            else if (stateLayer.getUnityArmys()[i]->getType() == state::INGENEER){
                stateLayer.getUnityArmys()[i]->setCodeTuile(9);
            }
            else if (stateLayer.getUnityArmys()[i]->getType() == state::INFANTRY){
                stateLayer.getUnityArmys()[i]->setCodeTuile(10);
            }
            if (stateLayer.getUnityArmys()[i]->getType() == state::LANCER){
                stateLayer.getUnityArmys()[i]->setCodeTuile(11);
            }
        }

        else if (stateLayer.getUnityArmys()[i]->getStatus() == state::DEAD){
            stateLayer.getUnityArmys()[i]->setCodeTuile(12);
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

bool Surface::loadCursor(state::State &stateLayer, const std::string &tileSet, sf::Vector2u tileSize, unsigned int width,
                        unsigned int height){
        // we load the tileset texture
        if (!texture.loadFromFile(tileSet)){
            return false;
        }

        float multiplier = 3.87f * 0.5f;

        // we resize the vertex array so that it can contain the whole level
        quads.setPrimitiveType(sf::Quads);
        quads.resize(width * height * 4);
        // we fill the vertex board, with one quad per tile
        // We update the tiles of the characters according to their status

        // we get the current tile number
        int tileNumber = stateLayer.getCursor()->getCodeTuile();

        // on en déduit sa position dans la texture du tileset
        int tu = tileNumber % (texture.getSize().x / tileSize.x);
        int tv = tileNumber / (texture.getSize().x / tileSize.x);

        // on récupère un pointeur vers le quad à définir dans le tableau de vertex
        sf::Vertex* quad = &quads[0];

        // we define its four corners
        quad[0].position = sf::Vector2f(stateLayer.getCursor()->getPosition().getX() * tileSize.x, stateLayer.getCursor()->getPosition().getY() * tileSize.y) * multiplier;
        quad[1].position = sf::Vector2f((stateLayer.getCursor()->getPosition().getX()+ 1) * tileSize.x, stateLayer.getCursor()->getPosition().getY() * tileSize.y) * multiplier;
        quad[2].position = sf::Vector2f((stateLayer.getCursor()->getPosition().getX() + 1) * tileSize.x, (stateLayer.getCursor()->getPosition().getY() + 1) * tileSize.y) * multiplier;
        quad[3].position = sf::Vector2f(stateLayer.getCursor()->getPosition().getX() * tileSize.x, (stateLayer.getCursor()->getPosition().getY() + 1) * tileSize.y) * multiplier;

    // on définit ses quatre coordonnées de texture
        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        return true;
    }
}

