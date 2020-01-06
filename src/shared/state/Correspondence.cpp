#include <iostream> 
#include "Correspondence.h"
 
using namespace std;
namespace state {

Correspondence ::Correspondence(){
    correspondence_nonpraticable[0] 	= WATER ;
    correspondence_nonpraticable[1] 	= WALL ;
    correspondence_nonpraticable[2]     = WALL;
    correspondence_nonpraticable[3] 	= WALL ;
    correspondence_nonpraticable[4] 	= WATER ;
    correspondence_nonpraticable[5] 	= WALL ;
    correspondence_nonpraticable[6] 	= WALL ;
    correspondence_nonpraticable[7] 	= WATER ;
    correspondence_nonpraticable[8] 	= WATER ;
    correspondence_nonpraticable[9] 	= WATER ;

    correspondence_nonpraticable[10] 	= TREE ;
	correspondence_praticable[11] 	= LAND ;
	correspondence_praticable[12] 	= LAND ;
	correspondence_praticable[13] 	= LAND ;
	correspondence_praticable[14] 	= LAND ;
	correspondence_praticable[15] 	= LAND ;
	correspondence_praticable[16] 	= LAND ;
	correspondence_praticable[17] 	= LAND ;
    correspondence_nonpraticable[18] = TREE;
    correspondence_nonpraticable[19] = HOLE;

    correspondence_praticable[20] = GRASS;
    correspondence_praticable[21] = GRASS;
    correspondence_praticable[22] = GRASS;
    correspondence_praticable[23] = GRASS;
    correspondence_praticable[24] = GRASS;
    correspondence_praticable[25] = GRASS;
    correspondence_praticable[26] = GRASS;
    correspondence_praticable[27] = GRASS;
    correspondence_nonpraticable[28] = HOLE;
    correspondence_nonpraticable[29] = HOLE;

    correspondence_nonpraticable[30] = TREE;
    correspondence_nonpraticable[31] = TREE;
    correspondence_praticable[32] = HILL;
    correspondence_praticable[33] = HILL;
    correspondence_praticable[34] = HILL;
    correspondence_praticable[35] = HILL;
    correspondence_praticable[36] = HILL;
    correspondence_praticable[37] = HILL;
    correspondence_nonpraticable[38] = HOLE;
    correspondence_nonpraticable[39] = HOLE;

    correspondence_nonpraticable[40] = WALL;
    correspondence_nonpraticable[41] = WALL;
    correspondence_nonpraticable[42] = TREE;
    correspondence_nonpraticable[43] = WALL;
    correspondence_nonpraticable[44] = WALL;
    correspondence_nonpraticable[45] = WALL;
    correspondence_nonpraticable[46] = TREE;
    correspondence_nonpraticable[47] = WALL;
    correspondence_nonpraticable[48] = HOLE;
    correspondence_nonpraticable[49] = TREE;

	correspondence_castle[0]= FIRSTLEVEL;
	correspondence_castle[1]= SECONDLEVEL;
	correspondence_castle[2]= THIRDLEVEL;
	correspondence_castle[2]= FINALLEVEL;

    correspondence_unityArmy[3] 	= INFANTRY;
    correspondence_unityArmy[7] 	= INFANTRY;
    correspondence_unityArmy[11] 	= INFANTRY;
    correspondence_unityArmy[0] 	= ARCHER;
    correspondence_unityArmy[4] 	= ARCHER;
    correspondence_unityArmy[8] 	= ARCHER;
    correspondence_unityArmy[2] 	= LANCER;
    correspondence_unityArmy[6] 	= LANCER;
    correspondence_unityArmy[10] 	= LANCER;
    correspondence_unityArmy[1] 	= CAVLRY;
    correspondence_unityArmy[5] 	= CAVLRY;
    correspondence_unityArmy[9] 	= CAVLRY;
}
std::map<int,TypePraticableId>& Correspondence ::getCorrspondencePraticable(){
	return correspondence_praticable;
}
std::map<int,TypeNonPraticableId>& Correspondence::getCorrespondenceNonPraticable(){
	return correspondence_nonpraticable;
}
std::map<int,CastleTypeId> Correspondence::getCorrespondenceC (){
	return correspondence_castle;
}
std::map<int,TypeGoldId> Correspondence::getCorrespondenceG (){
	return correspondence_gold;
}
std::map<int,ArmyTypeId> Correspondence::getCorrespondenceU (){
	return correspondence_unityArmy;
}
}
