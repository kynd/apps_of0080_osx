#pragma once

#include "ofMain.h"
#include "PigmentLayer.h"

class WaterColorCanvas {
    
public:
    WaterColorCanvas();
    void update();
    void draw();
    void addPigment(ofColor color);
    void beginPigmentDraw(int i);
    void endPigmentDraw();
    void beginWaterDraw();
    void endWaterDraw();
    void clearLayers();
    
    
private:
    ofFbo* applyShader(ofShader& shader, ofFbo* fbo, int type, int pigmentNum = 0);
    void clearFbo(ofFbo *fbo, int r, int g, int b);
    
    ofColor color;
    ofShader noiseShader, waterBleedingShader, waterRenderShader, pigmentFixShader, pigmentRenderShader, blurShader, pigmentShader;;
    ofFbo *tempFbo, *noiseFbo, *waterFbo, *paperFbo;
    vector<PigmentLayer> pigments;
    int currentPigment;
    
    ofPoint pos, prev, vec, adj;
    float width, cwidth;
    bool pressed;
    int state;
    
    static const int SHADING_TYPE_NOISE = 0;
    static const int SHADING_TYPE_WATER_BLEEDING = 1;
    static const int SHADING_TYPE_WATER_RENDER = 2;
    static const int SHADING_TYPE_PIGMENT_FIX = 3;
    static const int SHADING_TYPE_PIGMENT_RENDER = 4;
    static const int SHADING_TYPE_BLUR = 5;
};
