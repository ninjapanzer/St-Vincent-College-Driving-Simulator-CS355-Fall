//Author: Nathan Hoffer and Josh Woods
//
//Requires: time.h, sstream, cstring
using namespace std;

//Node used to hold data in EventLog
struct EventNode
{
	int status;
	float carX;
	float carY;
	float carZ;
	float carAngle;
	float collisionAngle;
	float distanceFromCenter;
	string collisionObject;
	float speed;
	float time;
	EventNode *next;
};

class EventLog
{
private:
	clock_t lastUpdate; //Used to see if automatic update should occur
	clock_t currentRunTime; //Used to hold current program run time
	int hr, min, sec; //Used to hold time information
	EventNode *startEvent; //Starting dummy node
	EventNode *lastEvent; //Used to hold last event so far.
public:
	//Default constructor
	//Sets up clock information and initial event listings
	EventLog() 
	{
		EventNode *temp=new EventNode;
		startEvent = temp;
		startEvent->next=NULL;
		lastUpdate = clock();
		lastEvent = startEvent;
		this->hr = 0;
		this->min = 0;
		this->sec = 0;
	}

	//Used for debug messages.  Returns a human readable time stamp.  Time is the amount of time passed since the program started.
	char* GetClockTime()
	{
		char* returnHolder;
		this->currentRunTime = clock();
		this->sec = this->currentRunTime/1000 - min * 60;
		if (this->sec > 59)
		{
			this-> min++;
		}
		int time = lastUpdate;
		returnHolder = dbStr(this->min);
		strcat(returnHolder,":");
		strcat(returnHolder,dbStr(this->sec));
		return returnHolder;
	}

<<<<<<< .mine
	void addEvent(float carPosX, float carPosY, float carPosZ, int status, float distance, float carAngle, float collisionAngle, string collisionObject, float speed, float time)
=======
	//Function used to add current event information to the event log
	void addEvent(float carPosX, float carPosY, float carPosZ, int status, float carAngle, float collisionAngle, string collisionObject, float speed, float time)
>>>>>>> .r173
	{
		lastUpdate = clock();		
		EventNode *tempEvent = new EventNode;
		tempEvent->carX = carPosX;
		tempEvent->carY = carPosY;
		tempEvent->carZ = carPosZ;
		tempEvent->carAngle = carAngle;
		tempEvent->collisionObject = collisionObject;
		tempEvent->collisionAngle = collisionAngle;
		tempEvent->speed = speed;
		tempEvent->status = status;
		tempEvent->time = time;
		tempEvent->distanceFromCenter = distance;
		tempEvent->next = NULL;
		lastEvent->next = tempEvent;
		lastEvent = tempEvent;
	}

	//Checks if the event log should auto update.  Users can use an if statement to check and then addEvent function to do an update.
	bool checkUpdate()
	{
		if ((clock()-lastUpdate)>500)
			return true;
		return false;
	}

	//XML information will have to be written to a file.  This function generates a string of the XML contents.  A user can then write this string to a file.
	string generateXMLString()
	{
		ostringstream s; //used for converting to string.
		s << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
		s << "<events>\n";
		EventNode *temp;
		temp = startEvent->next;
		while (temp!=NULL)
		{

			s << "\t<event>\n";
			s << "\t\t<status code=\"";
			s << temp->status;
			s << "\">";
			if (temp->status==0)
				s << "Normal";
			else if (temp->status==1)
				s << "Off Road";
			else if (temp->status==2)
				s << "Crossed Center Line";
			else
				s << "Collision";
			s << "</status>\n";
			s << "\t\t<xPos>";
			s << temp->carX;
			s << "</xPos>\n";
			s << "\t\t<yPos>";
			s << temp->carY;
			s << "</yPos>\n";
			s << "\t\t<zPos>";
			s << temp->carZ;
			s << "</zPos>\n";
			s << "\t\t<distanceFromCenter>";
			s << temp->distanceFromCenter;
			s << "</distanceFromCenter>\n";

			s << "\t\t<carAngle>";
			s << temp->carAngle;
			s << "</carAngle>\n";

			s << "\t\t<collision detected=\"";
			if (temp->collisionObject=="")
				s << "0";
			else
				s << "1";
			s << "\" angle=\"";
			s << temp->collisionAngle;
			s << "\">";
			s << temp->collisionObject;
			s << "</collision>\n";

			s << "\t\t<speed>";
			s << temp->speed;
			s << "</speed>\n";
			s << "\t\t<time>";
			s << temp->time;
			s << "</time>\n";
			s << "\t</event>\n";


			temp = temp->next;
		}
		s << "</events>\n";
		return s.str();
	}

	//Deconstructor that frees the current linked list
	~EventLog()
	{
		EventNode *temp;
		temp = startEvent;
		while (temp!=NULL)
		{
			lastEvent = temp;
			temp = temp->next;
			delete lastEvent;
		}
	}
};