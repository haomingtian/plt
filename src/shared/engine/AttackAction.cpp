#include "engine.h"
#include "state.h"
#include <iostream> 
#include <unistd.h>
#include <stdlib.h>

using namespace engine;
using namespace state;
using namespace std;

AttackAction::AttackAction (state::UnityArmy& attacker, state::UnityArmy& target, bool player) : attacker(attacker), target(target){
    actionId = ATTACK_ACTION;
	againstAttack = false;
	this->player = player;
	oldAttackerStatistics = attacker.getStatistics();
	oldTargetStatistics = target.getStatistics();
	oldAttackerPosition = attacker.getPosition();
	oldTargetPosition = target.getPosition();
	oldAttackerStatus = attacker.getStatus();
	oldTargetStatistics = target.getStatistics();
}

state::UnityArmy& AttackAction::getTarget(){
    UnityArmy& refPersoC = target;
	return refPersoC;
}

state::UnityArmy& AttackAction::getAttacker(){
    UnityArmy& refPersoA= attacker;
	return refPersoA;
}

void AttackAction::apply (state::State& state){
	//cout<<"attaque"<<endl;
	bool attaque_possible=false;
	vector<Position> listePosAtq=attacker.getLegalAttack(state);

	if (attacker.getStatus()!=WAITING && attacker.getStatus()!=DEAD){

		for(size_t j=0; j<listePosAtq.size(); j++){
			if(listePosAtq[j].equals(target.getPosition())){
				attaque_possible=true;
				break;
			}
			
		}
		if(attaque_possible){
			
				int attaque_attacker=attacker.getStatistics().getAttack();
				int critique_attacker=attacker.getStatistics().getCritical();
				string nomArme_attacker=attacker.getArmorName();

				int defense_target=target.getStatistics().getDefense();
				int pv_target=target.getStatistics().getPV();
				int esquive_target=target.getStatistics().getDodge();
				string nomArme_target=target.getArmorName();
				
								
				if (againstAttack == true){
					cout << "\tCONTRE-ATTAQUE" << endl;
				}
				
				//-----------------triangle des armes--------------------------------
				int bonus_attaque=-1;
				string afficheBonus;

				if(nomArme_target==nomArme_attacker){
					bonus_attaque=0;
				}
				else if(nomArme_attacker=="Arc" || nomArme_target=="Arc"){
					bonus_attaque=0;
				}
				else if((nomArme_attacker=="Hache" && nomArme_target=="Lance")|| (nomArme_attacker=="Lance" && nomArme_target=="Epee") || (nomArme_attacker=="Epee" && nomArme_target=="Hache")){
					bonus_attaque=5;
					afficheBonus = "\t|\tBonus d'arme pour " + attacker.getName() + ": +5 en ATTAQUE";
				}
				else if ((nomArme_target=="Hache" && nomArme_attacker=="Lance")|| (nomArme_target=="Lance" && nomArme_attacker=="Epee") || (nomArme_target=="Epee" && nomArme_attacker=="Hache")){
					bonus_attaque=-5;
					afficheBonus = "\t|\tMalus d'arme pour " + attacker.getName() + ": -5 en ATTAQUE";
				}

				//------------------------succes ou echec----------------------------------
				cout << "\t- " << attacker.getName() << " attaque " << target.getName() << " ! -" << endl;
				cout << afficheBonus << endl;
				srand(time(NULL));
				int chanceEsquive=rand()%100 + 1;
				
				//------------------------echec de l'attaque-------------------------------
				if(chanceEsquive<=esquive_target){
					cout << "\t|\t " << target.getName() << " évite l'attaque." << endl;
					cout << "\t|\t L'attaque échoue ! " << endl;
				}
				//------------------------succes de l'attaque-------------------------------
				else{
				//------------------------Calcul bonus critique-------------------------------------
					srand(time(NULL));
					int chanceCritique= rand()%100 + 1 ;
					int bonus_critique=0;
					if(chanceCritique<=critique_attacker){
						bonus_critique=5;
						cout << "\t|\t COUP CRITIQUE ! (+" << bonus_critique << " dégâts)" << endl;
					}

				//-------------------------Calcul degats------------------------------------
					int degats=attaque_attacker-defense_target + bonus_attaque + bonus_critique;
					if (degats < 0){
						degats = 0;
					}
				//---------------------------Attaque--------------------------------------
					target.getStatistics().setPV(pv_target-degats);
					cout << "\t|\t " << target.getName() << " perd " << degats << " PV. " << endl;
					cout << "\t|\t Il ne lui reste plus que " << target.getStatistics().getPV() << " PV."<< endl;
				}

				if(target.getStatistics().getPV()==0){
					target.setStatus(DEAD);
					target.getPosition().setX(-1);
					target.getPosition().setY(-1);
					cout << "\t\t++ " << target.getName() << " est mort. ++" << endl;
					
					// Si un personnage meurt lors d'une contre-attaque, le tour du personnage qui a 
					// contre-attaqué ne se termine pas
					if (againstAttack == false){
						FinAction finattaque(attacker, player);
						//FinActions finattaque(attacker, joueur);
						//sleep(2);
						finattaque.apply(state);
					}
				}
				
				else{
					if(againstAttack==false){
						AttackAction contre_attaque(target, attacker, !player);
						//Attaque contre_attaque(target, attacker, !joueur);
						contre_attaque.againstAttack=true;
						//sleep(2);
						contre_attaque.apply(state);
					}
					if(againstAttack==true){
						/*// Le tour du contre-attacker ne se termine pas apres sa contre-attaque
						if(attacker.getType()==ARCHER && target.getType()!=ARCHER){
							FinActions finattaque(attacker, joueur);
							sleep(2);
							finattaque.execute(etat);		
						}*/
						//else{
							FinAction finattaque(target, player);
							//FinActions finattaque(target, joueur);
							//sleep(2);
							finattaque.apply(state);
						//}		
					}
					
				}
			
		}
		
		// Cas attaque impossible
		else{
			if (againstAttack == true){
				cout << "\t CONTRE-ATTAQUE IMPOSSIBLE : ennemi hors de portée !" << endl;
				FinAction finattaque(target, player);
				//FinActions finattaque(target, joueur);
				//sleep(2);
				finattaque.apply(state);
			}
			else{
				cout << "\tAttaque non autorisée !" << endl;
			}		
		}
	}
	else if(attacker.getStatus()==WAITING){
		cout << attacker.getName() << " a terminé son tour d'actions, il ne peut plus attaquer." <<endl;  
	}
	
	cout << "\n" ;

}

void AttackAction::undo (state::State& state){

	attacker.getStatistics().setPV(oldAttackerStatistics.getPV());
	attacker.getStatistics().setAttack(oldAttackerStatistics.getAttack());
	attacker.getStatistics().setDefense(oldAttackerStatistics.getDefense());
	attacker.getStatistics().setCritical(oldAttackerStatistics.getCritical());
	attacker.getStatistics().setDodge(oldAttackerStatistics.getDodge());

	target.getStatistics().setPV(oldTargetStatistics.getPV());
	target.getStatistics().setAttack(oldTargetStatistics.getAttack());
	target.getStatistics().setDefense(oldTargetStatistics.getDefense());
	target.getStatistics().setCritical(oldTargetStatistics.getCritical());
	target.getStatistics().setDodge(oldTargetStatistics.getDodge());

	attacker.getPosition().setX(oldAttackerPosition.getX());
	attacker.getPosition().setY(oldAttackerPosition.getY());
	target.getPosition().setX(oldTargetPosition.getX());
	target.getPosition().setY(oldTargetPosition.getY());
	//attacker.setStatut(oldStatutattacker);
	attacker.setStatus(state::AVAILABLE);
	target.setStatus(oldTargetStatus);
}
