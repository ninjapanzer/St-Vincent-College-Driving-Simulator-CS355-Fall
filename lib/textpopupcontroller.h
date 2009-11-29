//Author: Paul Scarrone
//Depends: DarkGDK.h
// This class allows for the positioning of text on the screen.
// There are 3 major methods with 2 overloads for absolute positioning
// The goal of this class is to make easy use of displaying text on its own line with each execution 
// general use is to place text at some present offset from the left of the screen or to display additional text relative the the last line of text placed.

using namespace std;

class TextOverlay
{
private:
	int vertPos;          //current vertical position
	int hzonPos;          //current horizontal position
	char* textString;     //current text being written
	bool autoPos;         //turn off auto positioning of text
	int fontSize;         //locally set font size
	int newLineSpace;     //the default space between lines of text
	int leftOffsetSpace;  //the default distance added to the end of the last line of text when drawing to the right of the last line
	double offsetPercent; //the distance from the left of the scrren in screen percentage
public:
	TextOverlay() //default constructor
	{
		this->vertPos = 1;
		this->hzonPos = 0;
		this->textString = "";
		this->autoPos = true;
		this->fontSize = 12;
		this->newLineSpace = 2;
		this->offsetPercent = .05;
		this->leftOffsetSpace = 2;
	}
	//accessor
	//get
	char* GetLastText(){return this->textString;}
	int GetLastPosition(){return this->vertPos;}
	//set
	void SetVertPos(int pos){this->vertPos = pos;}
	void SetNewLineSpace(int space){this->newLineSpace = space;}
	void SetOffsetPercent(double percent){this->offsetPercent = percent/100;}
	void SetAutoPos(bool autoPos){this->autoPos = autoPos;}
	void SetFontSize(int size){this->fontSize = size;}
	void SetLeftOffsetSpace(int size){this->leftOffsetSpace = size;}
	//Displays text automatically in the center starting at the top of the screen
	void CenterText(char* text)
	{
		dbSetTextSize(this->fontSize);
		this->textString = text;
		if(this->autoPos) this->vertPos = this->vertPos + dbTextSize() + this->newLineSpace;
		this->hzonPos = dbScreenWidth()/2;
		dbCenterText(this->hzonPos, this->vertPos, this->textString);
	}
	//displays text at a particular default or set offset from the left of the screen
	void LeftOffsetText(char* text)
	{
		dbSetTextSize(this->fontSize);
		this->textString = text;
		if(this->autoPos) this->vertPos = this->vertPos + dbTextSize() + this->newLineSpace;
		this->hzonPos = dbScreenWidth() * this->offsetPercent;
		dbText(this->hzonPos, this->vertPos, this->textString);
	}
	//displays text along the center of the screen and takes an additional arugment for absolute position from the top of the screen
	void CenterText(char* text, int pos)
	{
		dbSetTextSize(this->fontSize);
		this->textString = text;
		this->vertPos = pos;
		this->hzonPos = dbScreenWidth()/2;
		dbCenterText(this->hzonPos, this->vertPos, this->textString);
	}
	//displays text along the left side at a set distance from the left of the screen takes an additional argument for the absolute position from the top of the screen
	void LeftOffsetText(char* text, int pos)
	{
		dbSetTextSize(this->fontSize);
		this->textString = text;
		this->vertPos = pos;
		this->hzonPos = dbScreenWidth() * this->offsetPercent;
		dbText(this->hzonPos, this->vertPos, this->textString);
	}
	//displays text directly to the right of the last line of text spaced by a default additional distance from the length of the last string and the offset from the left of the screen
	void RightofCurrentText(char* text)
	{
		int leftOffset = dbTextWidth(this->textString) + this->leftOffsetSpace;
		this->textString = text;
		this->hzonPos = this->hzonPos + leftOffset;
		dbText(this->hzonPos,this->vertPos,this->textString);
	}
};
