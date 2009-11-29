
// Dark GDK - The Game Creators - www.thegamecreators.com

// the wizard has created a very simple 3D project that uses Dark GDK
// it can be used as a starting point in making your own 3D games

// whenever using Dark GDK you must ensure you include the header file
#include "..\lib\defines.h"
#include "DarkGDK.h"
#include "..\lib\headers.h"
#include "..\lib\init.h"

using namespace std;

// the main entry point for the application is this function
void DarkGDK ( void )
{
#ifdef TESTROADVALUES
	dbOpenToRead(7, "..\\data\\roadblock.mbk");
	dbMakeMemblockFromFile(7,7);
	dbCloseFile(7);
	MemblockParser test(7);
	dbDeleteMemblock(7);
	DoubleLinked<CoordBlock> testblock;
	test.ReadMemblock();
	test.GetCoordBlockList(testblock);
	long testblocksize = testblock.GetSize();
	ofstream outfile("..\\data\\parsedblock");
	CoordBlock tempblock;
	for(int i = 0; i < testblocksize; i++)
	{
		tempblock = testblock.pop_front();
		outfile<<i<<" "<<tempblock.vertex.x<<"\t"<<tempblock.vertex.y<<"\t"<<tempblock.vertex.z<<"\n";
	}
	outfile.close();
#endif
	SimInit init;
	init.Init();
	while ( LoopGDK ( ) )
	{
		init.SimLoop();
		dbSync ( );
	}
	return;
}