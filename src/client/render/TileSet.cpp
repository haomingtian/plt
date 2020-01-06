#include <iostream> 
#include "TileSet.h"
using namespace std;
namespace render {
TileSet::TileSet (TileSetId newID){
	id=newID;
	if (id == GRIDTILESET){
		cellWidth=62;
		cellHeight=62;
		imageFile="./ressources/sprite_grid.png";
	}
	else if (id==UNITYARMYTILESET){
		cellWidth=16;
		cellHeight=16;
		imageFile="./ressources/UnityArmy.png";
	}
	else if (id==INFOSTILESET){
		cellWidth=64;
		cellHeight=64;
		imageFile="./ressources/mugshots_tileset.png";
	}
	else if (id == CURSORTILESET)
	{
	    cellWidth=16;
	    cellHeight=16;
	    imageFile="./ressources/curseur_tileset.png";
	}

	textureTileset.loadFromFile(imageFile);
}
const std::string  TileSet::getImageFile (){
	return imageFile;
}
int const TileSet::getCellWidth (){
	return cellWidth;
}
int const TileSet::getCellHeight (){
	return cellHeight;
}
int const TileSet::getTileSetID (){
	return id;
}
sf::Texture& TileSet::getTexture (){
	sf::Texture & refTexture = textureTileset;
	return refTexture ;
}
}
