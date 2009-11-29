//Author: Paul Scarr
//Depens on DarkGDK linkedlist.h
//TO DO: test for open memblocks and use the next unused one
//		 test for file ids open and use the next open one

using namespace std;

struct MemblockHeader //stuct to hold the header information
{
	int fvfStyle;
	int fvfVertexSize;
	long vertexNum;
};

class MemblockParser : public BuildRoadLinesList
{
private:
	int memblockId;  //id of the memblock to be created from a file
	DoubleLinked<CoordBlock> list; //list to store the coordblocks of the memblock
	CoordBlock tempCordBlock; //temp coordblock for pushing to list
	MemblockHeader header; //private of the memblock struct from above
public:
	MemblockParser(){}; //blank constructor
	//overloaded constructor takes in the memblock number and a filename
	//creates a memblock from the file and closes the file and processes the memblock information into a list type coordblock
	//once done the memblock is destroyed
	MemblockParser(int memblockId)
	{
		this->memblockId = memblockId;
		this->ReadFVFHeader();
		this->ReadMemblock();
		dbDeleteMemblock(this->memblockId);
	}
	//passes the first 96 bit to a struct for later use
	//to read the memblock you must read the header to get the number of vertices in the file
	void ReadFVFHeader()
	{
		int a = 0; //start at beginning of the file
		this->header.fvfStyle = dbMemblockDword(this->memblockId, a);
		this->header.fvfVertexSize = dbMemblockDword(this->memblockId, a=a+4);
		this->header.vertexNum = dbMemblockDword(this->memblockId, a=a+4);
	}
	void ReadMemblock()
	{
		int a = 8; //start past the header
		for (int i = 0; i < this->header.vertexNum; i++)
		{
			this->tempCordBlock.vertex.x = dbMemblockFloat(this->memblockId, a=a+4);
			this->tempCordBlock.vertex.y = dbMemblockFloat(this->memblockId, a=a+4);
			this->tempCordBlock.vertex.z = dbMemblockFloat(this->memblockId, a=a+4);
			this->tempCordBlock.normal.x = dbMemblockFloat(this->memblockId, a=a+4);
			this->tempCordBlock.normal.y = dbMemblockFloat(this->memblockId, a=a+4);
			this->tempCordBlock.normal.z = dbMemblockFloat(this->memblockId, a=a+4);
			this->tempCordBlock.diffuse = dbMemblockDword(this->memblockId, a=a+4);
			this->tempCordBlock.uv.x = dbMemblockFloat(this->memblockId, a=a+4);
			this->tempCordBlock.uv.y = dbMemblockFloat(this->memblockId, a=a+4);
			this->list.push_back(tempCordBlock);
		}
		
	}

	//copies and allows for access of the list by references requires a DoubleLinked<CoordBlock> for reference.
	//uses copy since the process of removing data from the list destroys the data
	void GetCoordBlockList(DoubleLinked<CoordBlock> (&list2))
	{
		this->list.CopyList(list2);
	}
	MemblockHeader GetFVFHeader()
	{
		return header;
	}
};