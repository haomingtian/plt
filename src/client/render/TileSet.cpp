#include <iostream> 
#include "TileSet.h"
using namespace std;
namespace render {
TileSet::TileSet (TilesetId newID){
	id=newID;
	if (id == GRIDTILESET){
		cellWidth=16;
		cellHeight=16;
		imageFile="/home/ensea/plt/ressources/spritee.PNG";
	}
	else if (id==UNITYARMYTILESET){
		cellWidth=16;
		cellHeight=16;
		imageFile="/home/ensea/plt/ressources/UnityArmy.png";
	}
	else if (id==CASTLETILESET){
		cellWidth=64;
		cellHeight=64;
		imageFile="/home/ensea/plt/ressources/Castles.png";		
	}
	/*else if (id==INFOSTILESET){
		cellWidth=16;
		cellHeight=16;
		imageFile="/home/ensea/plt/ressources/Castles.png";		
	}*/
	else if (id==CURSORTILESET){
		cellWidth=16;
		cellHeight=16;
		imageFile="/home/ensea/plt/ressources/curseur_tileset.png";		
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
