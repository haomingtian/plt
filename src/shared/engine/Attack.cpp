#include "engine.h"
#include "state.h"
#include <iostream> 
#include <unistd.h>
#include <stdlib.h>

using namespace engine;
using namespace state;
using namespace std;

Attack::Attack (state::UnityArmy& inAttacker, state::UnityArmy& inTarget, bool inPlayer): attacker(inAttacker), target(inTarget){
	id = ATTACK;
    againstAttack=false;
	player=inPlayer;
}
    

void Attack::execute (state::State& state){
	bool attackPossible=false;
	vector<Position> listePosAtq=attacker.getLegalAttack(state);

	if (attacker.getStatus()!=WAITING && attacker.getStatus()!=DEAD){

		for(size_t j=0; j<listePosAtq.size(); j++){
			if(listePosAtq[j].equals(target.getPosition())){
				attackPossible=true;
				break;
			}
			
		}
		if(attackPossible){
			
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
				int bonus_esquive=-1;
				string afficheBonus;

				if(nomArme_target==nomArme_attacker){
					bonus_attaque=0;
					bonus_esquive=0;
				}
				else if(nomArme_attacker=="Arc" || nomArme_target=="Arc"){
					bonus_attaque=0;
					bonus_esquive=0;
				}
				else if((nomArme_attacker=="Hache" && nomArme_target=="Lance")|| (nomArme_attacker=="Lance" && nomArme_target=="Epee") || (nomArme_attacker=="Epee" && nomArme_target=="Hache")){
					bonus_attaque=5;
					bonus_esquive=5;
					afficheBonus = "\t|\tBonus d'arme pour " + attacker.getName() + ": +5 en ATTAQUE et +5 en ESQUIVE";
				}
				else if ((nomArme_target=="Hache" && nomArme_attacker=="Lance")|| (nomArme_target=="Lance" && nomArme_attacker=="Epee") || (nomArme_target=="Epee" && nomArme_attacker=="Hache")){
					bonus_attaque=-5;
					bonus_esquive=-5;
					afficheBonus = "\t|\tMalus d'arme pour " + attacker.getName() + ": -5 en ATTAQUE et -5 en ESQUIVE";
				}

				//------------------------succes ou echec----------------------------------
				cout << "\t- " << attacker.getName() << " attaque " << target.getName() << " ! -" << endl;
				cout << afficheBonus << endl;
				srand(time(NULL));
				int chanceEsquive=rand()%100 + 1;
				
				//------------------------echec de l'attaque-------------------------------
				if(chanceEsquive<=esquive_target + bonus_esquive){
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
					EndAction endAction(attacker, player);
					sleep(2);
                    endAction.execute(state);
				}
				
				else{
					if(againstAttack==false){
						Attack contre_attaque(target, attacker, !player);
						contre_attaque.againstAttack=true;
						sleep(2);
						contre_attaque.execute(state);
					}
					if(againstAttack==true){
						/*// Le tour du contre-attacker ne se termine pas apres sa contre-attaque
						if(attacker.getType()==ARCHER && target.getType()!=ARCHER){
							FinActions finattaque(attacker, joueur);
							sleep(2);
							finattaque.execute(etat);		
						}*/
						//else{
							EndAction endAction(target, player);
							sleep(2);
							endAction.execute(state);
						//}		
					}
					
				}
			
		}
		
		// Cas attaque impossible
		else{
			if (againstAttack == true){
				cout << "\t CONTRE-ATTAQUE IMPOSSIBLE : ennemi hors de portée !" << endl;
				EndAction endAction(target, player);
				sleep(2);
				endAction.execute(state);
			}
			else{
				cout << "Attaque non autorisée !" << endl;
			}		
		}
	}
	else if(attacker.getStatus()==WAITING){
		cout << attacker.getName() << " a terminé son tour d'actions, il ne peut plus attaquer." <<endl;  
	}
	
	cout << "\n" ;
}
