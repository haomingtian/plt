#include <iostream>
#include <string.h>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <unistd.h>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
using namespace std;

#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"
using namespace state;
using namespace render;
using namespace engine;

namespace render{
  class Surface;
};

int main(int argc,char* argv[])
{

    cout << "bonjour " << endl;

    if (strcmp(argv[1], "render") == 0)
    {
        // create the window

        sf::RenderWindow window(sf::VideoMode(1550 * 0.5f, 1550 * 0.5f), "Tilemap");
        


        int mapWidth = 25;
        int mapHeight = 25;
        std::string mapTxt = "./ressources/map1.txt";

        Correspondence correspondences;

        State state;
        state.initGrid(mapTxt,mapWidth,mapHeight,correspondences);

        state.initUnityArmy(correspondences);

        StateLayer layer(state);

        layer.initSurfaces(state);

        // create the tilemap from the level definition
//    render::Surface map;
//    if (!map.loadGrid("/home/ensea/plt/ressources/spritee.PNG", level, sf::Vector2u(46, 48), 25, 8))
//        return -1;
        // run the main loop
        sf::Texture texture;
        sf::RectangleShape rectangle(sf::Vector2f(150, 60));

        if (!texture.loadFromFile("./ressources/UnityArmy.png"))
            return -1;

        rectangle.setTexture(&texture);
        rectangle.setPosition(0.f, 430.f);
        render::Surface army;
        /*if (!army.loadGrid("/home/ensea/plt/ressources/UnityArmy.png", level_u, sf::Vector2u(46, 48), 5, 1))
            return -1;*/

        sf::Font police;
        police.loadFromFile("./ressources/Pixellari.ttf");
        std::string chaine = "Army Choice";
        sf::Text text;
        text.setFont(police);
        text.setString(chaine);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::Blue);
        text.setPosition(sf::Vector2f(5.f, 390.f));

        /*sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin((int)(textRect.left + textRect.width/2.0f),
                       (int)(textRect.top  + textRect.height/2.0f));
        text.setPosition(sf::Vector2f(10.f, 390.f));*/

        while (window.isOpen())
        {
            // handle events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            // draw the map
            window.clear();
//        window.draw(map);
            window.draw(*layer.getSurfaces()[0]);
            window.draw(*layer.getSurfaces()[1]);
//        window.draw(rectangle);
//        window.draw(text);
            //window.draw(rectangle_1);
            //window.draw(army);
            window.display();
        }
    }
    else if (strcmp(argv[1], "engine") == 0)
    {
        cout<<"--- engine du jeu ---"<<endl;
        //----------------------------
        unsigned int longueur_map_cases = 25, largeur_map_cases = 25;
        std::string chemin_fichier_map_txt = "./ressources/map1.txt";

        Correspondence tab_corres = Correspondence();

        //-----------------------------
        Engine engine;

        if(	engine.getState().initGrid(chemin_fichier_map_txt, longueur_map_cases, largeur_map_cases, tab_corres)){
            engine.getState().initUnityArmy(tab_corres);
            engine.getState().initCursor();
            StateLayer stateLayer(engine.getState());
            stateLayer.initSurfaces(engine.getState());

            //----------------------------
            StateLayer* ptr_stateLayer=&stateLayer;
            engine.getState().registerObserver(ptr_stateLayer);

            //------------------------

            sf::RenderWindow window(sf::VideoMode(longueur_map_cases*stateLayer.getTileSets()[0]->getCellHeight() * 0.5f,
                                                  largeur_map_cases*stateLayer.getTileSets()[0]->getCellWidth() * 0.5f),
                                    "Map");

            bool demarrage = true;

            while (window.isOpen()){
                sf::Event event;

                if (demarrage){
                    stateLayer.draw(window);
                    cout << "\t\t--- Tour " << engine.getState().getRound() << " ---" << endl;
                    cout << "(Appuyez sur une touche pour simuler un tour de jeu)" << endl;
                    cout << "(Cette simulation compte 3 tours)\n" << endl;
                    demarrage = false;
                }

                while (window.pollEvent(event)){
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                    // Commands du premier tour pour la simulation (effectuees a l'appuis d'une touche)
                    else if(event.type==sf::Event::KeyPressed && !engine.getState().isEndAction() && engine.getState().getRound() == 1){

                        // Movement chevalier bleu
                        Position destination1(3,22);
                        Movement Movement1(*engine.getState().getUnityArmys()[2], destination1,true);
                        unique_ptr<Command> ptr_Movement1 (new Movement(Movement1));
                        engine.addCommand(0, move(ptr_Movement1));

                        // Attaque chevalier bleu contre archer rouge
                        Attack attaque1(*engine.getState().getUnityArmys()[2], *engine.getState().getUnityArmys()[4],true);
                        unique_ptr<Command> ptr_attaque1 (new Attack(attaque1));
                        engine.addCommand(1, move(ptr_attaque1));

                        // Movement chevalier bleu
                        Position destination2(1,20);
                        Movement movement2(*engine.getState().getUnityArmys()[0], destination2,true);
                        unique_ptr<Command> ptr_Movement2 (new Movement(movement2));
                        engine.addCommand(2, move(ptr_Movement2));

                        // Fin tour archer bleu
                        EndAction finactions1(*engine.getState().getUnityArmys()[0], true);
                        unique_ptr<Command> ptr_finactions1 (new EndAction(finactions1));
                        engine.addCommand(3, move(ptr_finactions1));

                        // Premier Movement du brigand bleu
                        Position destination3(3,20);
                        Movement Movement3(*engine.getState().getUnityArmys()[1], destination3,true);
                        unique_ptr<Command> ptr_Movement3 (new Movement(Movement3));
                        engine.addCommand(4, move(ptr_Movement3));

                        // Deuxieme Movement du brigand bleu
                        Position destination4(4,20);
                        Movement Movement4(*engine.getState().getUnityArmys()[1], destination4,true);
                        unique_ptr<Command> ptr_Movement4 (new Movement(Movement4));
                        engine.addCommand(5, move(ptr_Movement4));

                        // Troisieme Movement du brigand bleu
                        Position destination5(4,19);
                        Movement Movement5(*engine.getState().getUnityArmys()[1], destination5,true);
                        unique_ptr<Command> ptr_Movement5 (new Movement(Movement5));
                        engine.addCommand(6, move(ptr_Movement5));

                        // Tentative de quatrieme Movement du brigand bleu
                        Position destination6(4,18);
                        Movement Movement6(*engine.getState().getUnityArmys()[1], destination6,true);
                        unique_ptr<Command> ptr_Movement6 (new Movement(Movement6));
                        engine.addCommand(7, move(ptr_Movement6));

                        // Fin tour brigand bleu
                        EndAction finactions2(*engine.getState().getUnityArmys()[1], true);
                        unique_ptr<Command> ptr_finactions2 (new EndAction(finactions2));
                        engine.addCommand(8, move(ptr_finactions2));

                        // Fin tour guerrier bleu
                        EndAction finactions3(*engine.getState().getUnityArmys()[3], true);
                        unique_ptr<Command> ptr_finactions3 (new EndAction(finactions3));
                        engine.addCommand(9, move(ptr_finactions3));

                        engine.update(window);

                        if(engine.endOfTourVerification()){
                            engine.verificationDebutDeTour();
                            StateEvent majDisponibilite(ALLCHANGED);
                            engine.getState().notifyObservers(majDisponibilite, engine.getState(), window);
                        }
                    }

                        // Commands du deuxieme tour pour la simulation
                    else if(event.type==sf::Event::KeyPressed && !engine.getState().isEndAction() && engine.getState().getRound() == 2){

                        // Fin tour archer rouge
                        EndAction finactions4(*engine.getState().getUnityArmys()[4], false);
                        unique_ptr<Command> ptr_finactions4 (new EndAction(finactions4));
                        engine.addCommand(0, move(ptr_finactions4));

                        // Tentative d'attaque archer rouge contre chevalier bleu
                        Attack attaque2(*engine.getState().getUnityArmys()[4], *engine.getState().getUnityArmys()[2],false);
                        unique_ptr<Command> ptr_attaque2 (new Attack(attaque2));
                        engine.addCommand(1, move(ptr_attaque2));

                        engine.update(window);

                        if(engine.endOfTourVerification()){
                            engine.verificationDebutDeTour();
                            StateEvent majDisponibilite(ALLCHANGED);
                            engine.getState().notifyObservers(majDisponibilite, engine.getState(), window);
                        }
                    }

                        // Commands du troisieme tour pour la simulation
                    else if(event.type==sf::Event::KeyPressed && !engine.getState().isEndAction() && engine.getState().getRound() == 3){

                        // Quatrieme Movement du brigand bleu
                        Position destination7(4,18);
                        Movement Movement7(*engine.getState().getUnityArmys()[1], destination7,true);
                        unique_ptr<Command> ptr_Movement7 (new Movement(Movement7));
                        engine.addCommand(0, move(ptr_Movement7));

                        // Cinquieme Movement du brigand bleu
                        Position destination8(3,18);
                        Movement Movement8(*engine.getState().getUnityArmys()[1], destination8,true);
                        unique_ptr<Command> ptr_Movement8 (new Movement(Movement8));
                        engine.addCommand(1, move(ptr_Movement8));

                        // Tentative fin de tour archer rouge
                        EndAction finactions5(*engine.getState().getUnityArmys()[4], false);
                        unique_ptr<Command> ptr_finactions5 (new EndAction(finactions5));
                        engine.addCommand(2, move(ptr_finactions5));

                        // Fin tour brigand bleu
                        EndAction finactions6(*engine.getState().getUnityArmys()[1], true);
                        unique_ptr<Command> ptr_finactions6 (new EndAction(finactions6));
                        engine.addCommand(3, move(ptr_finactions6));

                        // Deuxieme Movement de l'archer bleu
                        Position destination9(1,21);
                        Movement Movement9(*engine.getState().getUnityArmys()[0], destination9,true);
                        unique_ptr<Command> ptr_Movement9 (new Movement(Movement9));
                        engine.addCommand(4, move(ptr_Movement9));

                        // Attaque archer bleu contre guerrier rouge
                        Attack attaque3(*engine.getState().getUnityArmys()[0], *engine.getState().getUnityArmys()[4],true);
                        unique_ptr<Command> ptr_attaque3 (new Attack(attaque3));
                        engine.addCommand(5, move(ptr_attaque3));

                        // Attaque chevalier bleu contre guerrier rouge
                        Attack attaque4(*engine.getState().getUnityArmys()[2], *engine.getState().getUnityArmys()[4],true);
                        unique_ptr<Command> ptr_attaque4 (new Attack(attaque4));
                        engine.addCommand(6, move(ptr_attaque4));

                        // Fin tour guerrier bleu
                        EndAction finactions7(*engine.getState().getUnityArmys()[3], true);
                        unique_ptr<Command> ptr_finactions7 (new EndAction(finactions7));
                        engine.addCommand(7, move(ptr_finactions7));

                        engine.update(window);

                        if(engine.endOfTourVerification()){
                            engine.verificationDebutDeTour();
                            StateEvent majDisponibilite(ALLCHANGED);
                            engine.getState().notifyObservers(majDisponibilite, engine.getState(), window);
                        }
                    }
                }
            }
        }
    }
    else if(strcmp(argv[1],"random_ai")==0 ||
            strcmp(argv[1],"heuristic_ai")==0||
            strcmp(argv[1], "rollback") == 0 ||
            strcmp(argv[1],"deep_ai")==0){
        //----------------------------
        unsigned int longueur_map_cases = 25, largeur_map_cases = 25;
        std::string chemin_fichier_map_txt = "./ressources/map1.txt";

        Correspondence tab_corres = Correspondence();
        //-----------------------------
        Engine engine;

        if(	engine.getState().initGrid(chemin_fichier_map_txt, longueur_map_cases, largeur_map_cases, tab_corres)){
            engine.getState().initUnityArmy(tab_corres);
            engine.getState().initCursor();
            StateLayer stateLayer(engine.getState());
            stateLayer.initSurfaces(engine.getState());

            StateLayer* ptr_stateLayer=&stateLayer;
            engine.getState().registerObserver(ptr_stateLayer);

            sf::RenderWindow window(sf::VideoMode(longueur_map_cases*stateLayer.getTileSets()[0]->getCellWidth() * 0.5f,
                                                  largeur_map_cases*stateLayer.getTileSets()[0]->getCellHeight() * 0.5f + 200.0f),"Map");

            bool startUp = true;
            bool rollback = false;
            ai::RandomAI randomAI;
            ai::HeuristicAI heuristicAI;
            ai::DeepAI deepAI;

            if(strcmp(argv[1],"heuristic_ai")==0){
                cout<<"\t\t--- HeuristicAI ---"<<endl;
            }
            else if(strcmp(argv[1],"random_ai")==0){
                cout<<"\t\t--- RandomAI ---"<<endl;
            }
            else if(strcmp(argv[1],"deep_ai")==0){
                cout<<"\t\t--- DeepAI ---"<<endl;
            }
            else if(strcmp(argv[1],"rollback")==0){
                cout<<"\t\t--- Rollback ---"<<endl;
                rollback = true;
            }

            int changementX = 0, changementY = 0;

            while (window.isOpen()){
                sf::Event event;

                // End-of-turn Verification and Start-of-turn Reinitializations
                if(!engine.getState().isEndAction() && engine.endOfTourVerification()){
                    engine.verificationDebutDeTour();
                    StateEvent majDisponibilite(ALLCHANGED);
                    engine.getState().notifyObservers(majDisponibilite, engine.getState(), window);
                }

                // Action at the start of the game
                if (startUp){
                    stateLayer.draw(window);
                    cout << "\n\t\t--- Round " << engine.getState().getRound() << " ---\n" << endl;
                    cout << "***********************************************************" << endl;
                    cout << "*                       CONTROLS                          *" << endl;
                    cout << "*  Move the Cursor             : Directional arrows       *" << endl;
                    cout << "*  Select Character            : Enter key                *" << endl;
                    cout << "*                                                         *" << endl;
                    cout << "*  Trigger a Attack            : A key                    *" << endl;
                    cout << "*  Choose Attack Target        : Directional arrows       *" << endl;
                    cout << "*  Validate Attack             : Enter key                *" << endl;
                    cout << "*  Cancel Attack               : N key                    *" << endl;
                    cout << "*                                                         *" << endl;
                    cout << "*  Terminer le tour d'actions  : touche Z                 *" << endl;
                    cout << "***********************************************************" << endl;

                    if (rollback)
                    {
                        cout << "\nPress R during your turn to trigger backtracking\n" << endl;
                    }

                    startUp = false;
                }

                // Call to the chosen AI for the opponent's turn
                if(strcmp(argv[1],"heuristic_ai")==0 || strcmp(argv[1],"rollback")==0) {
                    if (rollback) {
                        heuristicAI.runRollback(engine, window);
                    } else {
                        heuristicAI.run(engine, window);
                    }
                }
                else if (strcmp(argv[1], "deep_ai") == 0) {
                    deepAI.run(engine, window);
                } else {
                    randomAI.run(engine, window);
                }

                while (window.pollEvent(event)){
                    // Closing the window
                    if (event.type == sf::Event::Closed){
                        window.close();
                    }
                    else if (event.type==sf::Event::KeyPressed && engine.getState().isEndAction() == false && rollback){
                        engine.managerCursor(event, window, largeur_map_cases, longueur_map_cases);
                    }

                    else if (event.type==sf::Event::KeyPressed && engine.getState().isEndAction() == false){
                        engine.managerCursor(event, window, largeur_map_cases, longueur_map_cases);
                    }


                        /* CURSOR (WIP: code to move later) */

                        // Press a directional arrow or Enter without selection
                        // (engine.getState().verifyStatus()!=-1)
//                    else if(event.type==sf::Event::KeyPressed && (engine.getState().verifyStatus()==-1)){
//
//                        StateEvent stateEvent(ALLCHANGED);
//                        size_t xCurs=engine.getState().getCursor()->getPosition().getX();
//                        size_t yCurs=engine.getState().getCursor()->getPosition().getY();
//                        int numeroPerso = engine.getState().getGrid()[xCurs][yCurs]->isOccupated(engine.getState());
//
//                        // Directional arrows (moving the cursor)
//                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//                            if(xCurs!=largeur_map_cases-1)
//                            {
//                                changementX = 1;
//                            }
//                            else
//                            {
//                                changementX = -xCurs;
//                            }
//                        }
//                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//                            if(xCurs!=0){changementX = -1;}
//                            else{changementX = largeur_map_cases-1 -xCurs;}
//                        }
//                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//                            if(yCurs!=0){changementY = -1;}
//                            else{changementY = longueur_map_cases-1 -yCurs;}
//                        }
//                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//                            if(yCurs!=longueur_map_cases-1){changementY = 1;}
//                            else{changementY = -yCurs;}
//                        }
//                        // Enter (selection)
//                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
//                            if(numeroPerso != -1){
//                                // Character Selection
//                                if(engine.getState().getUnityArmys()[numeroPerso]->getCamp()){
//                                    engine.getState().getCursor()->setCodeTuile(3);
//                                    cout<< "\t\t-> \nBeginning of the round " << engine.getState().getUnityArmys()[numeroPerso]->getName() << " <-" << endl;
//                                    engine.getState().getUnityArmys()[numeroPerso]->setStatus(SELECTED);
//                                    StateEvent stateEvent(ALLCHANGED);
//                                    engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                                }
//                                else{	cout<< "This character belongs to the opponent!" <<endl;}
//                            }
//                                // Affichage du type de terrain
//                            else{	cout<< "This is a : ";
//                                cout << engine.getState().getGrid()[yCurs][xCurs]->getName() << endl;
//                            }
//                        }
//
//                        // Move the cursor
//                        if (changementX != 0 || changementY !=0){
//                            Position nextPosCurs(xCurs+changementX, yCurs+changementY);
//                            engine.getState().getCursor()->move(nextPosCurs);
//                            engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//
//                            changementX = 0;
//                            changementY = 0;
//                        }
//                    }
                    // Actions with selected character (engine.getState().verifyStatus()!=-1)
//                    else if(event.type==sf::Event::KeyPressed && (engine.getState().verifyStatus()!=-1)){
//                        int numeroPerso=engine.getState().verifyStatus();
//                        size_t xPerso=engine.getState().getUnityArmys()[numeroPerso]->getPosition().getX();
//                        size_t yPerso=engine.getState().getUnityArmys()[numeroPerso]->getPosition().getY();
//
//                        // Fleches directionnelles (deplacement du curseur et du personnage)
//                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//                            if(xPerso!=largeur_map_cases-1){changementX = 1;}
//                        }
//                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//                            if(xPerso!=0){changementX = -1;}
//                        }
//                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//                            if(yPerso!=0){changementY = -1;}
//                        }
//                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//                            if(yPerso!=longueur_map_cases-1){changementY = 1;}
//                        }
//
//                            // Z key: End of the action round
//                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
//                            EndAction endAction(*engine.getState().getUnityArmys()[numeroPerso],engine.getState().getUnityArmys()[numeroPerso]->getCamp());
//                            unique_ptr<Command> ptr_finaction (new EndAction(endAction));
//                            engine.addCommand(0, move(ptr_finaction));
//                            engine.getState().getCursor()->setCodeTuile(0);
//                            engine.update(window);
//                        }
//
//                        // Move cursor and selected character
//                        if (changementX != 0 || changementY != 0){
//                            Position nextPos(xPerso+changementX, yPerso+changementY);
//                            Movement movement(*engine.getState().getUnityArmys()[numeroPerso], nextPos, engine.getActivePlayer());
//                            unique_ptr<Command> ptr_movement (new Movement(movement));
//                            engine.addCommand(0, move(ptr_movement));
//
//                            engine.getState().getCursor()->move(nextPos);
//                            engine.update(window);
//
//                            changementX = 0;
//                            changementY = 0;
//                        }
//                    }

                        // Triggering an attack
//                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (engine.getState().verifyStatus()!=-1)){
//                        cout<< "\tAttack in preparation" << endl;
//
//                        StateEvent stateEvent(ALLCHANGED);
//                        int attaquant=engine.getState().verifyStatus();
//                        int champDroit=engine.getState().getUnityArmys()[attaquant]->getAttack();
//                        int champGauche=champDroit;
//                        int champHaut=champDroit;
//                        int champBas=champDroit;
//                        int cible=-1;
//
//                        engine.getState().getCursor()->setCodeTuile(1);
//                        engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//
//                        while((cible==-1) || (cible==attaquant)){
//                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//                                size_t xCurs=engine.getState().getCursor()->getPosition().getX();
//                                size_t yCurs=engine.getState().getCursor()->getPosition().getY();
//                                if(xCurs!=largeur_map_cases-1 && champDroit!=0){
//                                    Position nextPosCurs(xCurs+1, yCurs);
//
//                                    engine.getState().getCursor()->move(nextPosCurs);
//                                    champDroit=champDroit-1;
//                                    champGauche++;
//                                    engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                                    usleep(200000);
//                                }
//                            }
//                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//                                size_t xCurs=engine.getState().getCursor()->getPosition().getX();
//                                size_t yCurs=engine.getState().getCursor()->getPosition().getY();
//                                if(xCurs!=0 && champGauche!=0){
//                                    Position nextPosCurs(xCurs-1, yCurs);
//                                    engine.getState().getCursor()->move(nextPosCurs);
//                                    champGauche=champGauche-1;
//                                    champDroit++;
//                                    engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                                    usleep(200000);
//                                }
//                            }
//                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//                                size_t xCurs=engine.getState().getCursor()->getPosition().getX();
//                                size_t yCurs=engine.getState().getCursor()->getPosition().getY();
//                                if(yCurs!=longueur_map_cases-1 && champBas!=0){
//                                    Position nextPosCurs(xCurs, yCurs+1);
//                                    engine.getState().getCursor()->move(nextPosCurs);
//                                    champBas=champBas-1;
//                                    champHaut++;
//                                    engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                                    usleep(200000);
//                                }
//                            }
//                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//                                size_t xCurs=engine.getState().getCursor()->getPosition().getX();
//                                size_t yCurs=engine.getState().getCursor()->getPosition().getY();
//                                if(yCurs!=0 && champHaut!=0){
//                                    Position nextPosCurs(xCurs, yCurs-1);
//                                    engine.getState().getCursor()->move(nextPosCurs);
//                                    champHaut=champHaut-1;
//                                    champBas++;
//                                    engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                                    usleep(200000);
//                                }
//                            }
//
//                                // Cancel attack with N
//                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
//                                cible=-2;
//                                cout<< "\tCanceled attack" << endl;
//                                engine.getState().getCursor()->setCodeTuile(3);
//                                engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                                if(!engine.getState().getCursor()->getPosition().equals(engine.getState().getUnityArmys()[attaquant]->getPosition())){
//                                    Position nextPosCurs(engine.getState().getUnityArmys()[attaquant]->getPosition().getX(), engine.getState().getUnityArmys()[attaquant]->getPosition().getY());
//                                    engine.getState().getCursor()->move(nextPosCurs);
//
//                                    engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                                }
//                            }
//
//                                // Validate attack with Enter
//                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
//                                cible=engine.getState().getGrid()[engine.getState().getCursor()->getPosition().getX()][engine.getState().getCursor()->getPosition().getY()]->isOccupated(engine.getState());
//                            }
//                        }
//
//                        // Validation of the attack
//                        if(cible>=0){
//                            Attack attack(*engine.getState().getUnityArmys()[attaquant], *engine.getState().getUnityArmys()[cible],engine.getState().getUnityArmys()[attaquant]->getCamp());
//                            unique_ptr<Command> ptr_attaque (new Attack(attack));
//                            engine.addCommand(0, move(ptr_attaque));
//
//                            engine.getState().getCursor()->setCodeTuile(2);
//                            engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                            engine.update(window);
//                            engine.getState().getCursor()->setCodeTuile(0);
//                            engine.getState().notifyObservers(stateEvent, engine.getState(), window);
//                        }
//                    }
                }
            }
        }
    }


    return 0;
}
