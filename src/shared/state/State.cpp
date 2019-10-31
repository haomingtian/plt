#include <iostream> 
#include "State.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
 
using namespace std;
namespace state {
int State::getRound (){
	return num_round;
}
int State::getMround (){
	return max_round;
}
void State::setRound (int round){
	num_round=round;
}
bool State::isFin (){
	return fin;
}
int State::initGrid (std::string chemin_maptext, unsigned int width, unsigned int heigth, Correspondence& correspondence){
	std::ifstream fichier(chemin_maptext, ios::in);
	std::string contenu, ligne, code_tuile;
	int map_tuiles_code[heigth*width];
	// Lecture Fichier
    if (fichier){
    	while (getline(fichier,ligne)){
			ligne = ligne + ",";
			contenu = contenu + ligne;
		}
		fichier.close();
    }
    else {return -1;}
    // Conversion des codes des tuiles en int
    std::stringstream contenuStream(contenu);
    unsigned int i = 0, j = 0, k = 0;
    
    while(std::getline(contenuStream, code_tuile, ',')){
    	map_tuiles_code[i] = std::stoi(code_tuile);
    	i++;
    }
    // Remplissage de la grille de jeu avec les terrains
    for (i = 0; i < width; i++){
    	std::vector<std::unique_ptr<Field>> newLigne;
    	for (j = 0; j < heigth; j++){
    		if (map_tuiles_code[k] >= 0 && map_tuiles_code[k] <= 23){
				 // On regarde si le code de la tuile est celui d'un Terrain Praticable
				if (correspondence.getCorrspondenceP().find(map_tuiles_code[k]) != correspondence.getCorrspondenceP().end()){
					Praticable newTP(correspondence.getCorrspondenceP()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
					std::unique_ptr<Praticable> ptr(new Praticable(newTP)) ;
					newLigne.push_back(move(ptr));
				}
				// Cas du Terrain Non Praticable
				else if (correspondence.getCorrespondenceNP().find(map_tuiles_code[k]) != correspondence.getCorrespondenceNP().end()){
					NPraticable newNP(correspondence.getCorrespondenceNP()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
					std::unique_ptr<NPraticable> ptr(new NPraticable(newNP)) ;
					newLigne.push_back(move(ptr));
				}
			}
			else{
    			cerr << "Code Tuile " << map_tuiles_code[k]<< " invalide dans le fichier " << chemin_maptext << endl;
    			return 0;
    		
    		}
    		k++;
		}
		grid.push_back(move(newLigne));
	}
	return 1;
}
std::vector<std::vector<std::unique_ptr<Field>>>& State::getGrid (){
	std::vector<std::vector<std::unique_ptr<Field>>> & refGrid = grid;
	return refGrid;
}
}
