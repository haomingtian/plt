#include <iostream> 
#include "Map2D.h"
 
using namespace std;
namespace state {
Map2D::Map2D(size_t n_width, size_t n_heigth){
	width=n_width;
	heigth=n_heigth;
}
size_t Map2D::getWidth (){
	return width;
}
size_t Map2D::getHeigth (){
	return heigth;
}
void Map2D::resize (size_t n_width, size_t n_heigth){
	width=n_width;
	heigth=n_heigth;
}
	
}
