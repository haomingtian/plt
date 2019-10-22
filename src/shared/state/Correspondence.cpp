#include <iostream> 
#include "Correspondence.h"
 
using namespace std;
namespace state {

Correspondence ::Correspondence(){
	//correspondence_praticable[0] 	= HILL ;
	correspondence_praticable[1] 	= HILL ;
	correspondence_praticable[3] 	= HILL ;
	correspondence_praticable[4] 	= HILL ;
	correspondence_praticable[5] 	= HILL ;
	correspondence_praticable[6] 	= HILL ;
	correspondence_praticable[7] 	= HILL ;
	correspondence_praticable[8] 	= LAND ;
	correspondence_praticable[9] 	= LAND ;
	correspondence_praticable[10] 	= LAND ;
	correspondence_praticable[12] 	= LAND ;
	correspondence_praticable[13] 	= LAND ;
	correspondence_praticable[14] 	= LAND ;
	correspondence_praticable[15] 	= LAND ;
	correspondence_praticable[20] 	= LAND ;
	correspondence_praticable[21] 	= LAND ;
	correspondence_praticable[22] 	= LAND ;
	correspondence_praticable[23] 	= LAND ;
	
	correspondence_npraticable[0]   = TREE;
	correspondence_npraticable[16]   = TREE;
	correspondence_npraticable[17]  = TREE;
	correspondence_npraticable[2]  = WALL;
	correspondence_npraticable[19]  = WALL;
	correspondence_npraticable[6]  = WATER;
	correspondence_npraticable[11]  = WATER;
	
	correspondence_castle[0]= FIRSTLEVEL;
	correspondence_castle[1]= SECONDLEVEL;
	correspondence_castle[2]= THIRDLEVEL;
	correspondence_castle[2]= FINALLEVEL;
	
	correspondence_unityArmy[0]= INGENEER;
	correspondence_unityArmy[1]= INFANTRY;
	correspondence_unityArmy[2]= CAVLRY;
	correspondence_unityArmy[3]= ARCHER;
	correspondence_unityArmy[4]= LANCER;
	//correspondence_unityArmy[5]= INGENEER;		
}
}
