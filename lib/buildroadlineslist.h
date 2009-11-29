//Author: Sarah Anderson

using namespace std;

class BuildRoadLinesList
{
private:
	int drawingListSize;
	CoordBlock* drawingList;
	DoubleLinked<CoordBlock> rightLine;
	DoubleLinked<CoordBlock> leftLine;
	DoubleLinked<CoordBlock> centerLine;

public:
	
	//Default Constructor
	BuildRoadLinesList(){}

	BuildRoadLinesList(DoubleLinked<CoordBlock> list)
	{
		this->InitializeLines(list);
	}

	void InitializeLines(DoubleLinked<CoordBlock> list)
	{
		drawingListSize = list.GetSize();
		this->drawingList = new CoordBlock[drawingListSize];

		for(long i = 0; i < drawingListSize; i++)
		{
			drawingList[i] = list.pop_front();
		}

		this->CreateRightLine();
		this->CreateLeftLine();
		this->CreateCenterLine();
	}

	void CreateRightLine()
	{
		CoordBlock tempCoordBlock;
		for(long i = 0; i < drawingListSize - 12; i= i+6)
		{
			if(i == 0)
			{
				tempCoordBlock = drawingList[i+1];
				tempCoordBlock.vertex.z = -0.1;
				rightLine.push_back(tempCoordBlock);

				tempCoordBlock = drawingList[i];
				tempCoordBlock.vertex.z = -0.1;
				rightLine.push_back(tempCoordBlock);				
			}
			else
			{
				tempCoordBlock = drawingList[i];
				tempCoordBlock.vertex.z = -0.1;
				rightLine.push_back(tempCoordBlock);
			}
		}
	}

	void CreateLeftLine()
	{
		CoordBlock tempCoordBlock;
		for(long i = 11; i < drawingListSize-12; i = i + 6)
		{
			if(i == 11)
			{
				tempCoordBlock = drawingList[i-1];
				tempCoordBlock.vertex.z = -0.01;
				leftLine.push_back(tempCoordBlock);

				tempCoordBlock = drawingList[i];
				tempCoordBlock.vertex.z = -0.01;
				leftLine.push_back(tempCoordBlock);				
			}
			else
			{
				tempCoordBlock = drawingList[i];
				tempCoordBlock.vertex.z = -0.01;
				leftLine.push_back(tempCoordBlock);
			}
		}		
	}

	void CreateCenterLine()
	{
		CoordBlock tempCoordBlock;
		for(long i = 5; i < drawingListSize-12; i = i + 6)
		{
			if(i == 5)
			{
				tempCoordBlock = drawingList[i-1];
				tempCoordBlock.vertex.z = -0.01;
				centerLine.push_back(tempCoordBlock);

				tempCoordBlock = drawingList[i];
				tempCoordBlock.vertex.z = -0.01;
				centerLine.push_back(tempCoordBlock);				
			}
			else
			{
				tempCoordBlock = drawingList[i];
				tempCoordBlock.vertex.z = -0.01;
				centerLine.push_back(tempCoordBlock);
			}
		}		
	}

	void GetRightLine(DoubleLinked<CoordBlock>& list)
	{
		this->rightLine.CopyList(list);
	}

	void GetLeftLine(DoubleLinked<CoordBlock>& list)
	{
		this->leftLine.CopyList(list);
	}

	void GetCenterLine(DoubleLinked<CoordBlock>& list)
	{
		this->centerLine.CopyList(list);
	}

};