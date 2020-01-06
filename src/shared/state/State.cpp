#include <iostream>
#include "State.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include "Praticable.h"
#include "NonPraticable.h"
 
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
bool State::isEndAction() {
	return endAction;
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
    	map_tuiles_code[i] = std::stoi(code_tuile) - 1;
    	i++;
    }
    // Remplissage de la grille de jeu avec les terrains
    for (i = 0; i < width; i++){
    	std::vector<std::unique_ptr<Field>> newLigne;
    	for (j = 0; j < heigth; j++){
    		if (map_tuiles_code[k] >= 0 && map_tuiles_code[k] <= 49){

    		    int id = map_tuiles_code[k];

				 // On regarde si le code de la tuile est celui d'un Terrain Praticable
				if (correspondence.getCorrspondencePraticable().find(id) != correspondence.getCorrspondencePraticable().end()){
					Praticable newTP(correspondence.getCorrspondencePraticable()[id],i,j,id);
					std::unique_ptr<Praticable> ptr(new Praticable(newTP)) ;
					newLigne.push_back(move(ptr));
				}
				// Cas du Terrain Non Praticable
				else if (correspondence.getCorrespondenceNonPraticable().find(id) != correspondence.getCorrespondenceNonPraticable().end()){
                    NonPraticable newNP(correspondence.getCorrespondenceNonPraticable()[id],i,j,id);
					std::unique_ptr<NonPraticable> ptr(new NonPraticable(newNP)) ;
					newLigne.push_back(move(ptr));
				}
			}
			else{
    			cerr << "Code Tuile " << map_tuiles_code[k]<< " invalide dans le fichier " << chemin_maptext << endl;
    			return 0;
    		
    		}
    		k++;
		}
		grids.push_back(move(newLigne));
	}
	return 1;
}

int State::initUnityArmy(state::Correspondence &correspondence)
{
    UnityArmy archerBlue(ARCHER, true, "Oliver", 1, 21);
    std::unique_ptr<UnityArmy> archerBluePtr(new UnityArmy(archerBlue));
    unityArmys.push_back(move(archerBluePtr));

    UnityArmy brigand_bleu(INFANTRY, true, "John", 2, 20);
    std::unique_ptr<UnityArmy> ptrBB(new UnityArmy(brigand_bleu));
    unityArmys.push_back(move(ptrBB));

    UnityArmy chevalier_bleu(CAVLRY, true, "Bruce", 3, 23);
    std::unique_ptr<UnityArmy> ptrCB(new UnityArmy(chevalier_bleu));
    unityArmys.push_back(move(ptrCB));

    UnityArmy guerrier_bleu(LANCER, true, "Arthur", 4, 22);
    std::unique_ptr<UnityArmy> ptrGB(new UnityArmy(guerrier_bleu));
    unityArmys.push_back(move(ptrGB));

    UnityArmy archer_rouge(ARCHER, false, "Damian", 17, 5);
    std::unique_ptr<UnityArmy> ptrAR(new UnityArmy(archer_rouge));
    unityArmys.push_back(move(ptrAR));

    UnityArmy brigand_rouge(INFANTRY, false, "Oswald", 20, 2);
    std::unique_ptr<UnityArmy> ptrBR(new UnityArmy(brigand_rouge));
    unityArmys.push_back(move(ptrBR));

    UnityArmy chevalier_rouge(CAVLRY, false, "Jason", 23, 3);
    std::unique_ptr<UnityArmy> ptrCR(new UnityArmy(chevalier_rouge));
    unityArmys.push_back(move(ptrCR));

    UnityArmy guerrier_rouge(LANCER, false, "Slade", 21, 3);
    std::unique_ptr<UnityArmy> ptrGR(new UnityArmy(guerrier_rouge));
    unityArmys.push_back(move(ptrGR));

    return 1;
}

std::vector<std::unique_ptr<UnityArmy>>& State::getUnityArmys()
{
    std::vector<std::unique_ptr<UnityArmy>> & refUnityArmys = unityArmys;
    return refUnityArmys;
}

std::vector<std::vector<std::unique_ptr<Field>>>& State::getGrid (){
	std::vector<std::vector<std::unique_ptr<Field>>> & refGrid = grids;
	return refGrid;
}

void State::setEndAction(bool newEndAction)
{
    endAction = newEndAction;
}

int State::initCastle(state::Correspondence &correspondence)
{
    return 1;
}

int State::initGold(state::Correspondence &correspondence)
{
    return 1;
}

int State::initCursor()
{
    cursor = nullptr;
    cursor = new Cursor();
    return 1;
}

Cursor* State::getCursor()
{
    return cursor;
}

int State::verifyStatus()
{
    int selected=-1;
    for(size_t i=0; i<unityArmys.size(); i++){
        if(unityArmys[i]->getStatus()==SELECTED){
            selected=i;
            break;
        }
    }
    return selected;
}

State::~State()
{
    delete cursor;
    cursor = nullptr;
}

}
