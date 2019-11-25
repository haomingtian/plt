#include <iostream> 
#include "State.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
 
using namespace std;
namespace state {
int State::initCursor (){
	ptr_cursor=nullptr;
	ptr_cursor= new Cursor();
	return 1;
}

int State::verifStatus (){
	int selec=-1;
	for(size_t i=0; i<unityArmy.size(); i++){
		if(unityArmy[i]->getStatus()==SELECTED){
			selec=i;
			break;
		}
	}
	return selec;
}
int State::getRound (){
	return num_round;
}
int State::getMround (){
	return max_round;
}
void State::setRound (int round){
	num_round=round;
}
bool State::isEnd (){
	return end;
}
Cursor* State::getCursor (){
	return ptr_cursor;
}
std::vector<std::vector<std::unique_ptr<Field>>>& State::getGrid (){
	std::vector<std::vector<std::unique_ptr<Field>>> & ref_grid = grid;
	return ref_grid;
}
std::vector<std::unique_ptr<UnityArmy>>& State::getUnityArmy (){
	std::vector<std::unique_ptr<UnityArmy>>& ref_unity = unityArmy;
	return ref_unity;
}
std::vector<std::unique_ptr<Castle>>& State::getCastle (){
	std::vector<std::unique_ptr<Castle>>& ref_castle= castle;
	return ref_castle;
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
				/*if (correspondence.getCorrspondenceP().find(map_tuiles_code[k]) != correspondence.getCorrspondenceP().end()){
					Praticable newP(correspondence.getCorrspondenceP()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
					std::unique_ptr<Praticable> ptr((&newP)) ;
					newLigne.push_back(move(ptr));
					
				}*/
				// Cas du Terrain Non Praticable
				//else 
				if (correspondence.getCorrespondenceNP().find(map_tuiles_code[k]) != correspondence.getCorrespondenceNP().end()){
					NPraticable newNP(correspondence.getCorrespondenceNP()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
					std::unique_ptr<NPraticable> ptr((&newNP)) ;
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

int State::initUnityArmy (Correspondence& correspondence){
	UnityArmy ing_bleu(INGENEER, "Ing1", true, 1, 21);
	std::unique_ptr<UnityArmy> ptrIB(new UnityArmy(ing_bleu));
	unityArmy.push_back(move(ptrIB));
	
	UnityArmy ing_rouge(INGENEER, "Ing2", false, 17, 5);
	std::unique_ptr<UnityArmy> ptrIR(new UnityArmy(ing_rouge));
	unityArmy.push_back(move(ptrIR));
}
State::~State (){
	delete ptr_cursor;
	ptr_cursor=nullptr;
}
}
