//Author: Sarah Anderson

using namespace std;

class DrawRoadLines
{
private:
	BuildRoadLinesList RoadLinesList;

public:
	template<int N> //stl to grab the index of a passed array
		DrawRoadLines(CoordBlock (&coordArray)[N])
		{
			BuildDrawList DrawList(coordArray);
			DoubleLinked<CoordBlock> list;
			DrawList.GetCoordBlock(list);
			RoadLinesList.InitializeLines(list);
		}

	void DrawRightLine()
	{
		dbInk(dbRGB(0,0,0), dbRGB(0,0,0));
		DoubleLinked<CoordBlock> rightLine;
		RoadLinesList.GetRightLine(rightLine);

		CoordBlock repeatCoord;
		CoordBlock temp;

		for(int i = 0; !rightLine.empty(); i++)
		{
			if(i == 0)
				temp = rightLine.pop_front();
			else
				temp = repeatCoord;

			int x1 = temp.vertex.x;
			int y1 = temp.vertex.y;
			
			temp = rightLine.pop_front();
			int x2 = temp.vertex.x;
			int y2 = temp.vertex.y;
			dbLine( x1, y1, x2, y2);
			repeatCoord = temp;
		}
	}

	void DrawLeftLine()
	{
		dbInk(dbRGB(0,0,0), dbRGB(0,0,0));
		DoubleLinked<CoordBlock> leftLine;
		RoadLinesList.GetLeftLine(leftLine);

		CoordBlock repeatCoord;
		CoordBlock temp;

		for(int i = 0; !leftLine.empty(); i++)
		{
			if(i == 0)
				temp = leftLine.pop_front();
			else
				temp = repeatCoord;

			int x1 = temp.vertex.x;
			int y1 = temp.vertex.y;
			
			temp = leftLine.pop_front();
			int x2 = temp.vertex.x;
			int y2 = temp.vertex.y;
			dbLine( x1, y1, x2, y2);
			repeatCoord = temp;
		}
	}

	void DrawCenterLine()
	{
		dbInk(dbRGB(255,255,0), dbRGB(255,255,0));
		DoubleLinked<CoordBlock> centerLine;
		RoadLinesList.GetCenterLine(centerLine);

		CoordBlock repeatCoord;
		CoordBlock temp;

		for(int i = 0; !centerLine.empty(); i++)
		{
			if(i == 0)
				temp = centerLine.pop_front();
			else
				temp = repeatCoord;

			int x1 = temp.vertex.x;
			int y1 = temp.vertex.y;
			
			temp = centerLine.pop_front();
			int x2 = temp.vertex.x;
			int y2 = temp.vertex.y;
			dbLine( x1, y1, x2, y2);
			repeatCoord = temp;
		}
	}
};