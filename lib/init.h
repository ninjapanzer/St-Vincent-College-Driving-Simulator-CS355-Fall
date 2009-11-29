using namespace std;

class SimInit
{
private:
	CoordBlock CoordArrayReal[56];
	EventLog evts;
	VehicleTools Car;
	Vertex3d camera;
	CarStatus status;
	Vertex3d startPos;
	ControlDeviceManager controlManager; //used to query the available devices. does not set anything yet.
	CheckList* controllerList;
	char* memblockFileName;
	DoubleLinked<CoordBlock> list;
	bool displayText;
public:
	SimInit()
	{
		dbSyncOn   ( );
		dbSyncRate (240);
		dbSetWindowLayout(0,0,1);
		displayText = true;
		this->startPos.x = 0;
		this->startPos.y = 0;
		this->startPos.z = 0;
		this->memblockFileName = "..\\data\\roadblock.mbk";
		try
		{
			ifstream drawFile;
			drawFile.open(this->memblockFileName, ifstream::in);
			drawFile.close();
			ParseVector parser("..\\data\\VectorPoints.txt"); //parse file
			parser.GetVectorCoordBlock(CoordArrayReal); //recieve the Coord Array from file
			if(drawFile.fail())
			{
				drawFile.clear(ios::failbit);
				throw 1;
			}
		}
		catch(...)
		{
#ifdef DRAWEVERYTIME
			DrawIrregularPoly roadSurfaceTest(CoordArrayReal); //send the coord array from the file to
#endif
		}
		evts = EventLog();
	}
	void Init()
	{
		//dbSetDisplayMode(1280,1024,32);
		//dbSetWindowOff();
		//dbPitchCameraUp(90);


		// object display order affects camera focus
		dbMakeObjectCube(2,8.0f);
		dbPositionObject(2, this->startPos.x, this->startPos.y, this->startPos.z);
		dbColorObject(2,dbRgb(255,0,0));

		SetCurrentDirectory ( "media" );


		dbMakeObjectPlane(20,6000,6000);
		dbPositionObject(20,0,0,1);
		dbColorObject(20, dbRgb(15,130,45));


		//Create object from created memblock in file
		dbOpenToRead(1,"..\\data\\roadblock.mbk");
		dbMakeMemblockFromFile(1, 1); //recreate a memblock from a file
		dbMakeMeshFromMemblock(1,1);  //convert memblock to mesh
		dbMakeObject(1,1,1);  //display loaded mesh
		dbCloseFile(1);

		//DrawRoadLines roadLines(CoordArrayReal);
		//roadLines.DrawRightLine();
		//roadLines.DrawLeftLine();
		//roadLines.DrawCenterLine();	

		DoubleLinked<CoordBlock> list;
		DoubleLinked<CoordBlock> list2;
		DoubleLinked<CoordBlock> list3;
		dbOpenToRead(2,"..\\data\\roadblock.mbk");
		dbMakeMemblockFromFile(2, 2);
		MemblockParser mParser(2);
		mParser.GetCoordBlockList(list);

		BuildRoadLinesList roadLinesList(list);
		roadLinesList.GetRightLine(list2);
		DrawIrregularPoly rightRoadLine(list2);
		dbCloseFile(2);

		//Create object from created memblock in file
		dbOpenToRead(3,"..\\data\\linetests.mbk");
		dbMakeMemblockFromFile(3, 3); //recreate a memblock from a file
		dbMakeMeshFromMemblock(3,3);  //convert memblock to mesh
		dbMakeObject(3,3,1);  //display loaded mesh


#ifdef CAMERAONCAR
		this->Car.SetupVehicleCamera(2);
#endif
		//this->Car.SetVehicleCameraOn(false);
		this->controllerList = this->controlManager.GetCheckList();
		if (this->controlManager.GetCheckListSize() > 0)
		{
			dbSetControlDevice(controllerList[0].name); //sets project default control device
		}
		float pitch = 0;
		/*dbOpenToRead(2, "..\\data\\testblock.txt");
		dbMakeMemblockFromFile(2, 1);
		MemblockParser mParser(1);
		dbCloseFile(2);*/
	}
	void SimLoop()
	{
		if (dbSpaceKey())
		{
			if(this->displayText)
			{
				this->displayText = false;
			}
			else if(this->displayText == false)
			{
				this->displayText = true;
			}
			dbSleep(150);
		}
		this->DebugPopup();
		if(this->displayText){this->NotesPopup();}
		this->status.LocateCar(2,this->CoordArrayReal,55);
		this->Car.VehicleControlKeyboard(2);
		this->Car.SetVehicleId(2);
		//Car.VehicleControlGameController(2);
		this->status.displayStatus();

	}
	void NotesPopup()
	{
		TextOverlay txtDisplay;
		txtDisplay.SetVertPos(50);
		txtDisplay.CenterText("Notes");
		txtDisplay.CenterText("To Clear this Message Press Space");
		txtDisplay.CenterText("");
		txtDisplay.CenterText("Use Arrow Keys to Control Vehicle");
		txtDisplay.CenterText("To Reset the Car Press (Return)");
		txtDisplay.CenterText("For Debug Information Press (Tab)");
	}
	void DebugPopup()
	{
		TextOverlay txtDebug;
		txtDebug.SetVertPos(40);
		txtDebug.SetOffsetPercent(5);
		txtDebug.LeftOffsetText("Vehicle Id: ");
		txtDebug.RightofCurrentText(dbStr(this->Car.GetVehicleId()));
		txtDebug.LeftOffsetText("X: ");
		txtDebug.RightofCurrentText(dbLeft(dbStr(this->Car.GetAbsCarPos().x),7));
		txtDebug.LeftOffsetText("Y: ");
		txtDebug.RightofCurrentText(dbLeft(dbStr(this->Car.GetAbsCarPos().y),7));
		txtDebug.LeftOffsetText("Z: ");
		txtDebug.RightofCurrentText(dbLeft(dbStr(this->Car.GetAbsCarPos().z),7));
		txtDebug.LeftOffsetText("Angle: ");
		txtDebug.RightofCurrentText(dbStr(dbWrapValue(dbObjectAngleZ(this->Car.GetVehicleId()))));
		txtDebug.LeftOffsetText("Velocity: ");
		txtDebug.RightofCurrentText(dbLeft(dbStr(this->Car.GetCarPos().y),7));
		txtDebug.LeftOffsetText("");
		txtDebug.LeftOffsetText("Run Time: ");
		txtDebug.RightofCurrentText(evts.GetClockTime());
	}
	void EventHandler()
	{
<<<<<<< .mine
		if (evts.checkUpdate())
			evts.addEvent(0,0,0,0,0,0,0,"",0,0);
=======
		if (evts.checkUpdate())
			evts.addEvent(0,0,0,0,0,0,"",0,0);
>>>>>>> .r173
	}
};