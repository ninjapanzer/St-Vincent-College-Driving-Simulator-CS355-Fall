//Author: Paul Scarrone
//Depends: darkGDK.h
//This class is a wrapper for the checklist systems and the get device checklist features of DarkGDK
//providing a simple OOP interface to controler selection and identification.


using namespace std;
struct CheckList //Creates a struct to hold the items of a checklist type.
{
	char *name;
	int attributes[4];
};
class ControlDeviceManager
{
private:
	int size;  //hold the size of the checklist
	CheckList* checkList;  //undefined pointer to a checklist array
public:
	ControlDeviceManager() //default constructor
	{
		CreateCheckList();
	}
	CheckList* GetCheckList(){return this->checkList;} //extracts a checklist array pointer
	int GetCheckListSize(){return this->size;} //returns the size of the checklist array
	void CreateCheckList()
	{
		dbPerformChecklistControlDevices(); //builds an internal system checklist of control types
		ProcessCheckListItem();  //function to place the items of the checklist in the system to an accessible array
	}
	void OutputCheckList()
	{
	}
	void ProcessCheckListItem()
	{
		this->size = dbChecklistQuantity();
		this->checkList = new CheckList[this->size];
		for(int i =1; i <= size; i++) //indexes for checklist start at 1 so offsets to 0 in array index notion use a index - 1
		{	
			this->checkList[i-1].name = dbChecklistString(i);
			this->checkList[i-1].attributes[0] = dbChecklistValueA(i);
			this->checkList[i-1].attributes[1] = dbChecklistValueB(i);
			this->checkList[i-1].attributes[2] = dbChecklistValueC(i);
			this->checkList[i-1].attributes[3] = dbChecklistValueD(i);
		}
		
	}
};