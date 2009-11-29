//Author: Paul Scarrone
//Class to complete a draw list of objects from a single vector array
//Depends upon <iostream> "coordstructs.h" "linkedlist.h"

using namespace std;

//Creates a doubly linked list in the exact draw order of both sides of the road surface
class BuildDrawList: public CalculateNormals, public ParseVector
{
private:
	CoordBlock* localCoordBlock; //pointer of CoordBlock to create an alias for the passed in coordArray
	long size;
	float surfaceZ;
protected:
	DoubleLinked<CoordBlock> list; //linked list used to store draw order
	DoubleLinked<CoordBlock> rightList;
	DoubleLinked<CoordBlock> leftList;
public:
	BuildDrawList(){}
	template<int N> //stl to grab the index of a passed array
		BuildDrawList(CoordBlock (&coordArray)[N])
		{
			this->SetNormalDistance(25);
			this->surfaceZ = -.00000001f;
			this->SetDiffuseColor(dbRGB(0,0,0));
			this->localCoordBlock = new CoordBlock[N];
			for (int i = 1; i<N-1; i++)
			{
				this->localCoordBlock[i] = coordArray[i];
			}
			for (int i = 1; i<N-1; i++)
			{
				this->CompleteVertexBlockRight(i);
			}
			for (int i = 1; i<N-1; i++)
			{
				this->CompleteVertexBlockLeft(i);
			}
		}
		BuildDrawList(DoubleLinked<CoordBlock> &list)
		{
			this->SetNormalDistance(.5f);
			this->surfaceZ = -.00001f;
			this->SetDiffuseColor(dbRGB(255,255,0));
			this->size = list.GetSize();
			this->localCoordBlock = new CoordBlock[size];
			for (long i = 0; i<size/2; i++)
			{
				this->localCoordBlock[i] = list.pop_front();
			}
		}
		void SetSurfaceZ(float z){this->surfaceZ = z;}
		void ClearList()
		{
			for(long i = 0; !(this->list.empty()); i++)
			{
				this->list.pop_front();
			}
		}

		void CompletePolygonRight()
		{
			this->ClearList();
			for (long i = 0; i<this->size; i++)
			{
				this->CompleteVertexBlockRight(i);
			}
				this->list.CopyList(rightList);
		}

		void CompletePolygonLeft()
		{
			this->ClearList();
			for (long i = 0; i<size; i++)
			{
				this->CompleteVertexBlockLeft(i);
			}
			this->list.CopyList(leftList);
		}
		//push items in the drawing list for polygons on the right side of the vector
		void CompleteVertexBlockRight(int i)
		{	
			CoordBlock firstNormal; //storage for a normal in format coordblock
			CoordBlock secondNormal; //storage for a normal in format coordblock
			//single line to calculate a normal in vertex 3d format and convert to coodblock format calculation for first is x-1, x, x+1 positions
			firstNormal = this->CompleteCoordBlock(this->GetRightNormal(this->localCoordBlock[i-1].vertex, this->localCoordBlock[i].vertex,this->localCoordBlock[i+1].vertex));
			//single line to calculate a normal in vertex 3d format and convert to coodblock format calculation for first is x, x+1, x+2 positions
			secondNormal = this->CompleteCoordBlock(this->GetRightNormal(this->localCoordBlock[i].vertex, this->localCoordBlock[i+1].vertex,this->localCoordBlock[i+2].vertex));
			//(1)push Second Normal to the List
			this->list.push_back(secondNormal);
			//(2)push First Normal to the List
			this->list.push_back(firstNormal);
			//(3)push Second Center to the List
			this->list.push_back(this->CompleteCoordBlock(this->localCoordBlock[i+1].vertex));
			//(4)push First normal point to list
			this->list.push_back(firstNormal);
			//(5)push First Center to the List
			this->list.push_back(this->CompleteCoordBlock(this->localCoordBlock[i].vertex));
			//(6)push Second Center to the List
			this->list.push_back(this->CompleteCoordBlock(this->localCoordBlock[i+1].vertex));
		}
		//push items in the drawing list for polygons on the left side of the vector
		void CompleteVertexBlockLeft(int i)
		{
			CoordBlock firstNormal; //storage for a normal in format coordblock
			CoordBlock secondNormal; //storage for a normal in format coordblock
			Vertex3d test;
			//single line to calculate a normal in vertex 3d format and convert to coodblock format calculation for first is x-1, x, x+1 positions
			firstNormal = this->CompleteCoordBlock(this->GetLeftNormal(this->localCoordBlock[i-1].vertex, this->localCoordBlock[i].vertex,this->localCoordBlock[i+1].vertex));
			//single line to calculate a normal in vertex 3d format and convert to coodblock format calculation for first is x, x+1, x+2 positions
			secondNormal = this->CompleteCoordBlock(this->GetLeftNormal(this->localCoordBlock[i].vertex, this->localCoordBlock[i+1].vertex,this->localCoordBlock[i+2].vertex));
			//(1)push Second Center to the List
			this->list.push_back(this->CompleteCoordBlock(this->localCoordBlock[i+1].vertex));
			//(2)push First Center to the List
			this->list.push_back(this->CompleteCoordBlock(this->localCoordBlock[i].vertex));
			//(3)push Second Normal to the List
			this->list.push_back(secondNormal);
			//(4)push First Center to the list
			this->list.push_back(this->CompleteCoordBlock(this->localCoordBlock[i].vertex));
			//(5)push First Normal to the List
			this->list.push_back(firstNormal);
			//(6)push Second Normal to the List
			this->list.push_back(secondNormal);
		}
		//pass the list object to calling function by reference
		void GetCoordBlock(DoubleLinked<CoordBlock> (&list2))
		{
			this->list.CopyList(list2);
		}
		//takes in one point and creates a FVF coord block from it Vertex3d to CoordBlock
		CoordBlock CompleteCoordBlock(Vertex3d inputVertex)
		{
			CoordBlock tempCoordBlock;
			tempCoordBlock.SetDiffuseColor(this->diffuseColor);
			inputVertex.z = this->surfaceZ;
			tempCoordBlock.CompleteCoordBlock(inputVertex);
			return tempCoordBlock;
		}
};