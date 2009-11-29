//Author: Nathan Hoffer and Josh Woods
//Revision: Paul Scarrone (adaptation of class to include status output, rewrote overloaded contsructor and converted to class method, adjusted source of vehicle position)
//TODO: -Fix obscure error with sharp turns
//
//Requires: Vertex3d and CoordBlock Classes
using namespace std;

class CarStatus
{
private:
	float distance;
	int status;
	Vertex3d closestPoint;
	Vertex3d carPos;

	//Distance formula that is used to find the nearest point on the nearest line segment
	//Takes two 3d points and returns the float distance between the points.
	float distanceFormula(Vertex3d p,Vertex3d p1) 
	{
		return dbSQRT((p.x-p1.x)*(p.x-p1.x)+(p.y-p1.y)*(p.y-p1.y));
	}

	//Uses vector equations for calculating the nearest point on a line segment from (p1 to p2) to a point (p) 
	//Takes a point and the two points of the line segment and returns a Vertex3d that contains the nearest point
	Vertex3d ClosestPointOnSegment(Vertex3d p, Vertex3d p1, Vertex3d p2)
	{
		float t = ((p.x-p1.x)*(p2.x-p1.x)+(p.y-p1.y)*(p2.y-p1.y))/(((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y))*1.0);
		if (t<=0.0f)
			return p1;
		else if (t>=1.0f)
			return p2;
		else {
			Vertex3d temp;
			temp.x = p1.x+t*(p2.x-p1.x);
			temp.y = p1.y+t*(p2.y-p1.y);
			temp.z= 0; //Used for current "cheat" method can be changed later to include calculation
			return temp;
		}
	}
public:
	CarStatus(){} //Default Constructor

	//Takes the road points and the current point of the object and then calculates the status message of the car
	void LocateCar(int objectid, CoordBlock roadCoord[], int arrayLength)
	{
		this->carPos.x = dbObjectPositionX(objectid);
		this->carPos.y = dbObjectPositionY(objectid);
		this->carPos.z = dbObjectPositionZ(objectid);
		distance= distanceFormula(this->carPos, roadCoord[0].vertex);
		float tempDistance;
		Vertex3d tempClosestPoint;
		int nearestInitialSegmentIndex = 0; //Denotes segment from roadCoord[0] to roadCoord[1]
		
		//A loop that finds the nearest point on the nearest segment
		for (int i=0;i<arrayLength-1;i++)
		{
			tempClosestPoint = ClosestPointOnSegment(carPos,roadCoord[i].vertex,roadCoord[i+1].vertex);
			tempDistance = distanceFormula(this->carPos, tempClosestPoint);
			
			if (tempDistance<=distance)
			{
				distance = tempDistance;
				closestPoint = tempClosestPoint;
				nearestInitialSegmentIndex = i;
			}
		}

		//Tests direction of vector formed by two points and checks which side the car is on.  Updates status appropriately.
		if (roadCoord[nearestInitialSegmentIndex].vertex.y<roadCoord[nearestInitialSegmentIndex+1].vertex.y)
		{
			if (carPos.x>closestPoint.x)
			{
				if (distance<=20)
					status = 0;
				else
					status = 1;
			}
			else
			{
				if (distance<=20)
					status = 2;
				else
					status = 1;
			}	
		}
		else if (roadCoord[nearestInitialSegmentIndex].vertex.y==roadCoord[nearestInitialSegmentIndex+1].vertex.y)
		{
			if (roadCoord[nearestInitialSegmentIndex].vertex.x<roadCoord[nearestInitialSegmentIndex+1].vertex.x)
			{
				if (carPos.y<closestPoint.y)
				{
					if (distance<=20)
						status = 0;
					else
						status = 1;
				}
				else
				{
					if (distance<=20)
						status = 2;
					else
						status = 1;
				}
			}
			else
			{
				if (carPos.y>closestPoint.y)
				{
					if (distance<=20)
						status = 0;
					else
						status = 1;
				}
				else
				{
					if (distance<=20)
						status = 2;
					else
						status = 1;
				}
			}
		}
		else 
		{
			if (carPos.x<closestPoint.x)
			{
				if (distance<=20)
					status = 0;
				else
					status = 1;
			}
			else
			{
				if (distance<=20)
					status = 2;
				else
					status = 1;
			}
		}
	}

	//Public accessor for distance information
	float distanceFromRoad()
	{
		return distance;
	}

	//Public accessor for status information
	int roadStatus()
	{
		return status;
	}

	//Public accessor for closestPoint information
	Vertex3d getClosestPoint()
	{
		return closestPoint;
	}
	
	//Example print out for debugging purposes
	void displayStatus()
	{
		char statusTxt[100];
		char cVal[100];
		if (this->roadStatus()==0)
			sprintf(statusTxt,"%s", "On Road");
		else if (this->roadStatus()==1)
			sprintf(statusTxt,"%s", "Off Road");
		else
			sprintf(statusTxt,"%s", "Wrong Side");
		sprintf(cVal,"%f %s",this->distanceFromRoad(), statusTxt);		
		dbText(0,0,cVal);
	}
};