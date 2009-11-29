//Author: Paul Scarrone
//Class that handles drawing complex objects derived from triangles and irregular polygons
//currently only supports generation from sequenced list
//Depends on <iostream> "coordstructs.h" "linkedlist.h" "builddrawlist.h" "DarkGDK.h"

using namespace std;
class DrawIrregularPoly
{
private:
CoordBlock localCoordBlock;
int fvfStyle;
int fvfVertexSize;

public:
DrawIrregularPoly()//default empty constructor
{
	this->fvfStyle = 338;//sets fvf style id
	this->fvfVertexSize = 36;//sets size of the vertex for the fvf style
}
template<int N> //stl to grab the index of a passed array
	DrawIrregularPoly(CoordBlock (&coordArray)[N])
	{
		this->fvfStyle = 338;//sets fvf style id
		this->fvfVertexSize = 36;//sets size of the vertex for the fvf style
		CoordBlock temp;
		BuildDrawList DrawList(coordArray);
		DoubleLinked<CoordBlock> list;
		DrawList.GetCoordBlock(list);
		ofstream file;
		file.open("..\\data\\roaddebug.txt");
		dbMakeMemblock(1, CalcMemBlockSize(N*12));
		this->WriteFVF338Header(1,list.GetSize());
		int i = 0;
		int j = 0;
		while (list)
		{
			temp = list.pop_front();
			this->WriteCoordBlock(j, temp, 1);
			//outputs the coord being written to the memblock in exact order to a human readable textfile
			file<<j<<" "<<temp.vertex.x<<"\t"<<temp.vertex.y<<"\t"<<temp.vertex.z<<"\n";
			j++;
		}
		this->MakeMemBlockIntoFile(1, "..\\data\\roadblock.mbk");
		dbDeleteMemblock(1);
		file.close();
	}

	DrawIrregularPoly(DoubleLinked<CoordBlock> &list)
	{
		this->fvfStyle = 338;//sets fvf style id
		this->fvfVertexSize = 36;//sets size of the vertex for the fvf style
		CoordBlock temp;
		BuildDrawList DrawList(list);
		DrawList.CompletePolygonRight();
		DoubleLinked<CoordBlock> processedList;
		DrawList.GetCoordBlock(processedList);
		ofstream file;
		file.open("..\\data\\linetests.txt");
		dbMakeMemblock(1, CalcMemBlockSize(processedList.GetSize()));
		this->WriteFVF338Header(1,processedList.GetSize());
		int i = 0;
		int j = 0;
		while (processedList)
		{
			temp = processedList.pop_front();
			this->WriteCoordBlock(j, temp, 1);
			//outputs the coord being written to the memblock in exact order to a human readable textfile
			file<<j<<" "<<temp.vertex.x<<"\t"<<temp.vertex.y<<"\t"<<temp.vertex.z<<"\n";
			j++;
		}
		this->MakeMemBlockIntoFile(1, "..\\data\\linetests.mbk");
		dbDeleteMemblock(1);
		file.close();
	}

	//wrapper to test for memblock file and handle deletion and recreation of memblock file
	//takes the memblock index to write and a filename as arguments
	void MakeMemBlockIntoFile(int memblockIndex, char* filename)
	{
		if (dbFileExist(filename))
			{
				dbDeleteFile(filename);
			}
		dbOpenToWrite (memblockIndex,filename);
		dbMakeFileFromMemblock(memblockIndex,memblockIndex);
		dbCloseFile(memblockIndex);
	}
	//creates the default header for a FVF 338 memblock
	//takes a memblox index and the number of vertices in the object as arguments
	void WriteFVF338Header(int memblockIndex, long vertexNum)
	{
		int a = 0;//tracks write position in the file
		dbWriteMemblockDword(memblockIndex,a=a,this->fvfStyle);
		dbWriteMemblockDword(memblockIndex,a=a+4,this->fvfVertexSize);
		dbWriteMemblockDword(memblockIndex,a=a+4,vertexNum);
	}
	//calculated the default size of a FVF 338 by 36 memblock
	int CalcMemBlockSize(int vertices)
	{
		return (96+(vertices*288))/8;
	}
		//Creates a custom 4 sided poly from cords given does not check for overlap of coords calls check function
	void WriteCoordBlock(int blockNum,CoordBlock cBlock, int memblockIndex)
	{
		int a = (36*blockNum)+12; //relative starting position for each block after the header information
		// Spacial Cords
		dbWriteMemblockFloat(memblockIndex,a=a,cBlock.vertex.x);
		dbWriteMemblockFloat(memblockIndex,a=a+4,cBlock.vertex.y);
		dbWriteMemblockFloat(memblockIndex,a=a+4,cBlock.vertex.z);
		// Normals
		dbWriteMemblockFloat(memblockIndex,a=a+4,cBlock.normal.x);
		dbWriteMemblockFloat(memblockIndex,a=a+4,cBlock.normal.y);
		dbWriteMemblockFloat(memblockIndex,a=a+4,cBlock.normal.z);
		//Difusion Color
		dbWriteMemblockDword(memblockIndex,a=a+4,cBlock.diffuse );//localCoordBlock.diffuse
		//UV Cords
		dbWriteMemblockFloat(memblockIndex,a=a+4,cBlock.uv.x);
		dbWriteMemblockFloat(memblockIndex,a=a+4,cBlock.uv.y);
	}
};