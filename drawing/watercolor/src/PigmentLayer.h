#pragma once

#include "ofMain.h"
class PigmentLayer {
public:
	PigmentLayer();
	~PigmentLayer();
	ofFbo* update(ofFbo* water, ofFbo* noise, ofFbo* temp);

    ofColor color;
    ofFbo *fbo;
    ofShader shader;
};
