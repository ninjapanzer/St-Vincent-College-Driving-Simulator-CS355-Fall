//Author: Sarah Anderson & Anthony Williams  (Original Code)
//Revised: Paul Scarrone (Class Rewrite / Partial Comments)
//Depends on <string> <cassert> <cstdlib> "coordstructs.h" <assert.h>
using namespace std;
class ParseVector  //Class to parse a data file of with data delimited by , and \n into an array of vertex objects
{
private:
	Vertex3d* vectorPoints; //pointer to a 3 dimensional vertex block
protected:
	CoordBlock* coordArrayTemp; //pointer to a full coordblock
	int arraySize;
	DWORD diffuseColor;
public:
	ParseVector(){}
	ParseVector(char* filename) //Overload constructor takes filename as argument
	{
		this->arraySize = GetVectorFileLength(filename);  //parses the file for number of lines then multiplies by rows of data(3)
		ifstream vectorFile; //prepares the in filestream object
		vectorFile.open (filename, ifstream::in); //opens file
		assert(vectorFile.is_open()); //assures the file is open (bool)
		this->vectorPoints = new Vertex3d[this->arraySize]; //creates an array at the vectorPoints pointer of the size of the data
		this->diffuseColor = 1065353216;

		int placeInArray = 0;
		int indicator = 0;
		char tempNums[100];
		string floatNumber;
		for(int i = 0; !(vectorFile.eof());i++)
		{
			vectorFile.getline(tempNums, 100);
			string lineOfNumbers = tempNums;		

			int start = 0;
			for(int j = 0; j < 100 && tempNums[j] != NULL; j++)
			{
				if(tempNums[j] == ',')
				{
					floatNumber = lineOfNumbers.substr(start, j-start-1);
					start = j + 1;

					float number = atof(floatNumber.c_str());

					if(indicator == 0)
					{
						this->vectorPoints[placeInArray].x = number;
						indicator++;
					}
					else if(indicator == 1)
					{
						this->vectorPoints[placeInArray].y = number;
						indicator++;
					}
					else
					{
						this->vectorPoints[placeInArray].z = number;
						indicator = 0;
						placeInArray++;
					}
				}
			}
		}
		vectorFile.close();
	}

	void ProcessVectorFile(char* filename)
	{
		this->arraySize = GetVectorFileLength(filename);  //parses the file for number of lines then multiplies by rows of data(3)
		ifstream vectorFile; //prepares the in filestream object
		vectorFile.open (filename, ifstream::in); //opens file
		assert(vectorFile.is_open()); //assures the file is open (bool)
		this->vectorPoints = new Vertex3d[this->arraySize]; //creates an array at the vectorPoints pointer of the size of the data
		this->diffuseColor = 1065353216;

		int placeInArray = 0;
		int indicator = 0;
		char tempNums[100];
		string floatNumber;
		for(int i = 0; !(vectorFile.eof());i++)
		{
			vectorFile.getline(tempNums, 100);
			string lineOfNumbers = tempNums;		

			int start = 0;
			for(int j = 0; j < 100 && tempNums[j] != NULL; j++)
			{
				if(tempNums[j] == ',')
				{
					floatNumber = lineOfNumbers.substr(start, j-start-1);
					start = j + 1;

					float number = atof(floatNumber.c_str());

					if(indicator == 0)
					{
						this->vectorPoints[placeInArray].x = number;
						indicator++;
					}
					else if(indicator == 1)
					{
						this->vectorPoints[placeInArray].y = number;
						indicator++;
					}
					else
					{
						this->vectorPoints[placeInArray].z = number;
						indicator = 0;
						placeInArray++;
					}
				}
			}
		}
		vectorFile.close();
	}
	void SetDiffuseColor(DWORD color)
	{
		this->diffuseColor = color;
	}
	//outputs the size of the data within the data file num rows x data in rows(3) takes filename argument
	int GetVectorFileLength(char* filename)
	{
		int i;  //declare outside of loop so the data is not temporary to the loop
		ifstream vectorFile;  //prepares the in filestream object
		vectorFile.open (filename, ifstream::in);  //opens file
		assert(vectorFile.is_open());   //assures the file is open (bool)
		char tempNums[100];
		for(i = 0; !(vectorFile.eof());i++)
		{
			vectorFile.getline(tempNums, 100);
		}
		vectorFile.close();
			return i;
	}
	int GetArraySize()
	{
		return arraySize;
	}
template<int N> //stl to grab the index of a passed array
	//builds a coordblock from an array of vertices and passes the completed object back by reference
	void GetVectorCoordBlock(CoordBlock (&coordArray2)[N])
	{
		for (int i = 0; i<N; i++)
		{
			coordArray2[i].vertex = this->vectorPoints[i];
			coordArray2[i].normal = this->vectorPoints[i];
			coordArray2[i].uv.x = this->vectorPoints[i].x;
			coordArray2[i].uv.y = this->vectorPoints[i].y;
			coordArray2[i].diffuse = this->diffuseColor;
		}
	}
	void CopyVectorCoordBlock()
	{
		this->coordArrayTemp = new CoordBlock[this->arraySize];
		for (int i = 0; i<this->arraySize; i++)
		{
			this->coordArrayTemp[i].vertex = this->vectorPoints[i];
			this->coordArrayTemp[i].normal = this->vectorPoints[i];
			this->coordArrayTemp[i].uv.x = this->vectorPoints[i].x;
			this->coordArrayTemp[i].uv.y = this->vectorPoints[i].y;
			this->coordArrayTemp[i].diffuse = this->diffuseColor;
		}
	}
};