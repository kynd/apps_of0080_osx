#include "Boid3D.h"

Boid3D::Boid3D(): fleeDist(200) {
	
}

void Boid3D::update() {
    if (ofRandom(1) < 0.1) {
        target.set(ofRandom(-600,600), ofRandom(-600,600), ofRandom(-200,200));
    }
     
	addVehicle();
	for (int i = 0; i < preys.size(); i ++) {
        for (int j = 0; j < predators.size(); j ++) {
            if (preys[i].position.distance(predators[j].position) < fleeDist) {
                preys[i].flee(predators[j].position);
            }
        }
		preys[i].arrive(target);
		preys[i].flock(preys);
		preys[i].update();
	}
    
	for (int i = 0; i < predators.size(); i ++) {
        predators[i].seek(preys[0].position);
		predators[i].arrive(target);
		predators[i].flock(preys);
		predators[i].update();
	}
    
    
}
void Boid3D::draw() {
    for (int i = 0; i < preys.size(); i ++) {
		preys[i].draw();
	}
}

void Boid3D::addVehicle() {
	if (preys.size() < NUM_PREYS) {
        SteeredVehicle v;
		v.position.set(ofRandom(-100, 100), ofRandom(-100, 100), ofRandom(-100, 100));
		v.velocity.set(ofRandom(-3,3), ofRandom(-3,3), ofRandom(-3,3));
		preys.push_back(v);
	}
    
    if (predators.size() < NUM_PREDATORS) {
        SteeredVehicle v;
		v.position.set(ofRandom(-100, 100), ofRandom(-100, 100), ofRandom(-100, 100));
		v.velocity.set(ofRandom(-3,3), ofRandom(-3,3), ofRandom(-3,3));
        v.mass = 10.0;
        v.maxSpeed = 8.0;
		predators.push_back(v);
	}
}