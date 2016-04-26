#ifndef VELOCITYPID_H_INCLUDED
#define VELOCITYPID_H_INCLUDED

#include "filter.c"
#include "util.c"

//A velocity PID controller
typedef struct vel_PID_t
{
	//PID constants
	float kP;
	float kD;

	//PID calculations
	float currentVelocity;
	int prevPosition;
	int error;
	int prevError;
	int derivative;

	//Timestep
	float dt;
	int currentTime;
	int prevTime;

	//Input
	tSensors sensor;
	tMotor imeMotor;
	float *var;
	bool usingIME;
	bool usingVar;
	float ticksPerRev;
	int currentPosition;
	float targetVelocity;

	//Filtering
	DEMAFilter filter;
	float alpha;
	float beta;

	//Output
	float outVal;
} vel_PID;

//Initializes a velocity PID controller
void vel_PID_InitController(vel_PID *pid, const tSensors sensor, const float kP, const float kD, const float ticksPerRev = UTIL_QUAD_TPR);
void vel_PID_InitController(vel_PID *pid, const tMotor imeMotor, const float kP, const float kD, const float ticksPerRev = UTIL_IME_HT_TPR);
void vel_PID_InitController(vel_PID *pid, const float *var, const float kP, const float kD, const float ticksPerRev = UTIL_QUAD_TPR);

//Sets new filter constants
void vel_PID_SetFilterConstants(vel_PID *pid, const float alpha, const float beta);

//Sets the controller's target velocity
void vel_PID_SetTargetVelocity(vel_PID *pid, const int targetVelocity);

//Gets the current error
int vel_PID_GetError(vel_PID *pid);

//Gets the current output
int vel_PID_GetOutput(vel_PID *pid);

//Steps the controller's velocity calculations with out stepping math
int vel_PID_StepVelocity(vel_PID *pid);

//Steps the controller's calculations
int vel_PID_StepController(vel_PID *pid);

//Steps the controller's calculations with a given current velocity
int vel_PID_StepController(vel_PID *pid, const int currentVelocity);

#endif //VELOCITYPID_H_INCLUDED
