#include "render.h"
#include "Surface.h"

using namespace render;

bool Surface::loadGrid (state::State& statelayer, Texture& text_tileset, Vector2u tile_size, unsigned int width, unsigned int heigth){
	texture=text_tileset;
	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	quads.setPrimitiveType(sf::Quads);
    quads.resize(width * height * 4);
}
