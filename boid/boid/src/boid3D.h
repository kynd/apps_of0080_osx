#pragma once

#include "ofMain.h"
#include "vehicle.h"
#include "steeredVehicle.h"

class Boid3D {
public:
	Boid3D();
	void update();
	void draw();
	
	vector<SteeredVehicle> preys;
	vector<SteeredVehicle> predators;
private:
	void addVehicle();
	float fleeDist;
    ofVec3f target;
	const int NUM_PREYS = 100;
	const int NUM_PREDATORS = 10;
};

