//Author: Paul Scarrone

// a 3 dimensional vertex in floats
struct Vertex3d
{
	float x;
	float y;
	float z;
};
// a 2 dimensional vertex in floats
struct Vertex2d
{
	float x;
	float y;
};

//adapted previous CoordBlock struct to a class implimentation to permit constructor usage.
class CoordBlock
{
public:
Vertex3d vertex; //spatial coords
Vertex3d normal; //normal coords - generally the same as the spatial
Vertex2d uv;     //uv vertex in 2 dimensions
DWORD diffuse;   //the diffuse color of the vertex as a dword defined in iostream
CoordBlock(){}
CoordBlock(float x, float y, float z, bool autoComplete)
{
	this->vertex.x = x;
	this->vertex.y = y;
	this->vertex.z = z;
	if (autoComplete)
	{
		this->CompleteCoordBlock(this->vertex);
	}
}
CoordBlock(Vertex3d vertex, DWORD dColor)
{
	this->vertex = vertex;
	this->normal = vertex;
	this->uv.x = vertex.x;
	this->uv.y = vertex.y;
	this->diffuse = dColor;
}
void CompleteCoordBlock(Vertex3d vertex)
{
	this->vertex = vertex;
	this->normal = vertex;
	this->uv.x = vertex.x;
	this->uv.y = vertex.y;
}
void CompleteCoordBlock(Vertex3d vertex, float z)
{
	this->vertex = vertex;
	this->vertex.z = z;
	this->normal = this->vertex;
	this->vertex.z = z;
	this->uv.x = vertex.x;
	this->uv.y = vertex.y;
}
void SetDiffuseColor(DWORD diffuse){this->diffuse = diffuse;}
};