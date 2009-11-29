// Author: Paul Scarrone
// Relies on coordstructs.h, DarkGDK.h
using namespace std;
class VehicleTools
{
private:
	Vertex3d carPos; //offset statistic for control
	Vertex3d camera;
	Vertex2d wheelPos; //2 axis position information from steering wheel
	Vertex3d absCarPos;
	int vehicleId;
	float speedControlRate; //rate of decceleration after button is no longer being pressed
	float accelerationRate; //rate of growth for movement
	float pedalMultiplier; //generally fractional value this value is the demon to reduce raw output
	float steeringMultiplier; //generally a frational value this value is the demon to reduce raw output
	float turningRate; //multiplier for turning control
	bool vehicleCameraOn;
public:
	// single call setting accessor for control properties
	void SetControlMultipliers(float wheel, float pedal, float turning, float controlRate, float accel)
	{
		this->SetAccelerationRate(accel);
		this->SetControlRate(controlRate);
		this->SetPedalMultiplier(pedal);
		this->SetSteeringMultiplier(wheel);
		this->SetTurningRate(turning);
	}
	//accessors
	//set
	void SetSteeringMultiplier(float wheel){this->steeringMultiplier = wheel;}
	void SetPedalMultiplier(float pedal){this->pedalMultiplier = pedal;}
	void SetAccelerationRate(float rate){this->accelerationRate = rate;}
	void SetControlRate(float rate){this->speedControlRate = rate;}
	void SetTurningRate(float rate){this->turningRate = rate;}
	void SetVehicleCameraOn(bool condition){this->vehicleCameraOn = condition;}
	void SetVehicleId(int vehicleId){this->vehicleId = vehicleId;}
	//get
	float GetSteeringMultiplier(){return this->steeringMultiplier;}
	float GetPedalMultiplier(){return this->pedalMultiplier;}
	float GetAccelerationRate(){return this->accelerationRate;}
	float GetControlRate(){return this->speedControlRate;}
	float GetTurningRate(){return this->turningRate;}
	int GetVehicleId(){return this->vehicleId;}
	Vertex3d GetCarPos(){return this->carPos;}
	Vertex3d GetAbsCarPos()
	{
		this->absCarPos.x = dbObjectPositionX(this->vehicleId);
		this->absCarPos.y = dbObjectPositionY(this->vehicleId);
		this->absCarPos.z = dbObjectPositionZ(this->vehicleId);
		return this->absCarPos;
	}
	VehicleTools()  // default constructor sets default movement values
	{
		this->carPos.x = 0;
		this->carPos.y = 0;
		this->carPos.z = 0;
		this->wheelPos.x = 0;
		this->wheelPos.y = 0;
		this->SetControlMultipliers(5,500,2,.0007f,.01f);
		this->vehicleCameraOn = true;
	}
	// overloaded constructor to permit instansiation with custom properties and vehicle starting position
	VehicleTools(Vertex3d vehPos, float wheel, float pedal, float turning, float controlRate, float accel)
	{
		this->carPos = vehPos;
		this->wheelPos.x = 0;
		this->wheelPos.y = 0;
		this->SetControlMultipliers(wheel, pedal, turning, controlRate, accel);
	}
	// takes a DarkGDK object id and allows for control of forward motion through acceleration and turning
	void VehicleControlKeyboard(int vehicleId)
	{
		if (dbDownKey())
		{
			this->carPos.y = this->carPos.y - this->accelerationRate;
		}
		if (dbUpKey())
		{
			this->carPos.y = this->carPos.y + this->accelerationRate;
		}
		if (dbLeftKey())
		{
			this->carPos.x = this->carPos.x + this->turningRate ; // rotates left by inversion
			dbZRotateObject(vehicleId,this->carPos.x); //rotates from aggregated button presses
		}
		if (dbRightKey())
		{
			this->carPos.x = this->carPos.x - this->turningRate; // rotates right by inversion
			dbZRotateObject(vehicleId,this->carPos.x); //rotates from aggregated button presses
		}
		if (dbReturnKey()) //acts as reset key. Places vehicle at origin and stops motion
		{
			this->carPos.x = 0;
			this->carPos.y = 0;
			this->carPos.z = 0;
			this->VehicleReset(vehicleId, this->carPos);
		}
		// moves object in direction it is facing
		// gradually slows the vehicle and retards its sudden acceleration 
		if (carPos.y > 0) //tests to see if the positional values are still in positive range
		{
			//tests to see if values are under the value before next calculation
			if(this->carPos.y > this->speedControlRate) //this is in place to protect against rebounding and an inability for the object to stop under its own settings
				this->carPos.y = this->carPos.y - this->speedControlRate;
			else
				this->carPos.y = 0;
		}
		if (carPos.y < 0)
		{
			//tests to see if values are under the value before next calculation
			if (this->carPos.y < this->speedControlRate)//this is in place to protect against rebounding and an inability for the object to stop under its own settings
				this->carPos.y = this->carPos.y + this->speedControlRate;
			else
				this->carPos.y = 0;
		}
		dbMoveObjectUp(vehicleId,this->carPos.y); //moves object forward relative to x and y
		this->VehicleCameraControl(vehicleId, this->carPos.y);
	}
	//takes a 3d object id as a parameter and allows for control with the controller set
	void VehicleControlGameController(int vehicleId)
	{
		//while(this->wheelPos.x != 0 || this->wheelPos.y == 0)
		{
		this->wheelPos.x = -(dbControlDeviceX ()/this->steeringMultiplier);
		dbZRotateObject(vehicleId,this->wheelPos.x);
		this->wheelPos.y = -(dbControlDeviceY ()/this->pedalMultiplier);
		dbMoveObjectUp(vehicleId,this->wheelPos.y);
		this->VehicleCameraControl(vehicleId, this->wheelPos.y);
		}
	}
	void VehicleCameraControl(int vehicleId, float pos)
	{
#ifdef CAMERAONCAR
		dbSetCameraToObjectOrientation(vehicleId);
		dbPitchCameraUp(90);
		dbMoveCamera(pos);
#endif
	}
	void SetupVehicleCamera(int vehicleId)
	{
#ifdef CAMERAONCAR
		this->camera.x = dbObjectPositionX(vehicleId);
		this->camera.y = dbObjectPositionY(vehicleId);
		this->camera.z = -8;
		dbPositionCamera(this->camera.x,this->camera.y,this->camera.z);
#endif
	}
	void VehicleReset(int vehicleId, Vertex3d pos)
	{
		this->carPos = pos;
		dbPositionObject(vehicleId, this->carPos.x, this->carPos.y, this->carPos.z);
		SetupVehicleCamera(vehicleId);
	}
};