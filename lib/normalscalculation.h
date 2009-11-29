//Author: Riley Hardin
//Revision: Paul Scarrone
//Depends on <math.h> "coordstruct.h"
//Program takes 3 points on a 2d plane & finds the line between points 1 & 3, the normal line of 1 & 3 running through point 2,
//the point of intersection between the 2 lines (point 4), and 2 points each with a distance of 10 float away from point 2 on the normal line.

//TODO: - Change how points are inputted (3 points are currently coded in)  (Riley)
//      - Take cout statements out of the CalculateNormalPoints function (just used to test accuracy)  (Riley)

//pointsInput[0], pointsInput[1], and pointsInput[2] are the 3 initial points in order
//pointsOutput[0] is the point of intersection between the lines
//pointsOutput[1] and pointsOutput[2] are the points on the normal line with a distance of 10 float away from pointsInput[1]
using namespace std;
class CalculateNormals
{
private:
	Vertex3d pointsOutput[3];
	Vertex3d pointsInput[3];
	float d;  //distance
public:
	CalculateNormals()//default constructor
	{
		this->d = 10.0f;
	}
	
	void SetNormalDistance(float d){this->d = d;}
	float GetNormalDistance(){return this->d;}
	
	//retrives the positive quadratic right normal of 3 vertex3d objects
	Vertex3d GetRightNormal(Vertex3d pointOne, Vertex3d pointTwo, Vertex3d pointThree)  
	{
		//PointData pointsInput[3];
		this->pointsInput[0].x = pointOne.x;
		this->pointsInput[0].y = pointOne.y;
		this->pointsInput[0].z = pointOne.z;
		this->pointsInput[1].x = pointTwo.x;
		this->pointsInput[1].y = pointTwo.y;
		this->pointsInput[1].z = pointOne.z;
		this->pointsInput[2].x = pointThree.x;
		this->pointsInput[2].y = pointThree.y;
		this->pointsInput[2].z = pointOne.z;
		//PointData pointsOutput[3];
		CalculateNormalPoints(this->pointsInput, this->pointsOutput);
		Vertex3d rightNormal;
		rightNormal.x = this->pointsOutput[1].x;
		rightNormal.y = this->pointsOutput[1].y;
		rightNormal.z = this->pointsOutput[1].z;
		return rightNormal;

	}
	Vertex3d GetLeftNormal(Vertex3d pointOne, Vertex3d pointTwo, Vertex3d pointThree)
	{
		this->pointsInput[0].x = pointOne.x;
		this->pointsInput[0].y = pointOne.y;
		this->pointsInput[0].z = pointOne.z;
		this->pointsInput[1].x = pointTwo.x;
		this->pointsInput[1].y = pointTwo.y;
		this->pointsInput[1].z = pointOne.z;
		this->pointsInput[2].x = pointThree.x;
		this->pointsInput[2].y = pointThree.y;
		this->pointsInput[2].z = pointOne.z;
		CalculateNormalPoints(this->pointsInput, this->pointsOutput);
		Vertex3d leftNormal;
		leftNormal.x = this->pointsOutput[2].x;
		leftNormal.y = this->pointsOutput[2].y;
		leftNormal.z = this->pointsOutput[2].z;
		return leftNormal;
	}
//remarked out all console statements
void CalculateNormalPoints(Vertex3d pointsInput[], Vertex3d pointsOutput[])
{
	float m = 0, intercept = 0, mNormal = 0, bNormal = 0;
	bool vertLine = false;
	if (pointsInput[2].x == pointsInput[0].x)
		vertLine = true;
	m = (pointsInput[2].y - pointsInput[0].y) / (pointsInput[2].x - pointsInput[0].x); //calculates slope between point 1 & 3
	
	intercept = -(m*pointsInput[0].x) + pointsInput[0].y; //calculates y-intercept of slope line

	if (!vertLine)
	{
		mNormal = -(1/m); //figures out slope of normal between points 1 & 3
		/*
		cout << "mNormal: " << mNormal << endl;
		*/

		bNormal = -(mNormal*pointsInput[1].x) + pointsInput[1].y; //calculates y-intercept of normal line

		pointsOutput[0].x = (intercept - bNormal)/(mNormal - m); //calculates x-coordinate at point of intersection between regular line & normal line
		pointsOutput[0].y = m*pointsOutput[0].x + intercept; //calculated y-coordinate at point of intersection between regular line & normal line

		float a = (1+pow(mNormal,2));  //a
		float b = (2*mNormal*(bNormal-pointsInput[1].y)-2*pointsInput[1].x);  //b
		float c = (pow(pointsInput[1].x,2)+pow((bNormal-pointsInput[1].y),2)-pow(d,2));  //c

		//Quadratic Formula
		pointsOutput[1].x = (-(b) + sqrt(pow(b,2)-4*(a)*(c)))/(2*a);  //calculates x-coordinate for one point with a distance of 10 away from the interect point on the normal line
		pointsOutput[1].z = pointsInput[1].z;
		pointsOutput[2].x = (-(b) - sqrt(pow(b,2)-4*(a)*(c)))/(2*a);  //calculates x-coordinate for one point with a distance of 10 away the other direction from the interect point on the normal line
		pointsOutput[2].z = pointsInput[2].z;

		pointsOutput[1].y = mNormal * pointsOutput[1].x + bNormal;  //calculated y-coordinate for x5 coordinate
		pointsOutput[2].y = mNormal * pointsOutput[2].x + bNormal;  //calculated y-coordinate for x6 coordinate
	}
	else
	{
		//vert slope handler
		pointsOutput[1].x = pointsInput[1].x + this->d;
		pointsOutput[1].y = pointsInput[1].y;
		pointsOutput[1].z = pointsInput[1].z;
		
		pointsOutput[2].x = pointsInput[1].x - this->d;
		pointsOutput[2].y = pointsInput[1].y;
		pointsOutput[2].z = pointsInput[1].z;
	}
	}
Vertex3d ExtendPoints(Vertex3d p1, Vertex3d p2)
{
	Vertex3d p3;
	p3.x=p2.x-(p1.x-p2.x);
	p3.y=p2.y-(p1.y-p2.y);
	p3.z=p2.z-(p1.z-p2.z);
	return p3;
}
};