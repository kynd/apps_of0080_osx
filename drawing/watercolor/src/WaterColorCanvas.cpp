#include "WaterColorCanvas.h"

WaterColorCanvas::WaterColorCanvas() {
    noiseShader.load("shader.vert", "simplexNoise.frag");
    waterBleedingShader.load("shader.vert", "waterBleeding.frag");
    waterRenderShader.load("shader.vert", "waterRender.frag");
    pigmentFixShader.load("shader.vert", "pigmentFix.frag");
    pigmentRenderShader.load("shader.vert", "pigmentRender.frag");
    blurShader.load("shader.vert", "blur.frag");
    pigmentShader.load("shader.vert", "pigmentBleeding.frag");
    
    tempFbo = new ofFbo();
    tempFbo->allocate(1280, 720, GL_RGBA32F); //temporary buffer
    noiseFbo = new ofFbo();
    noiseFbo->allocate(1280, 720, GL_RGBA32F); //noise
    waterFbo = new ofFbo();
    waterFbo->allocate(1280, 720, GL_RGBA32F); //water
    paperFbo = new ofFbo();
    paperFbo->allocate(1280, 720, GL_RGBA32F); //fixed color
    clearLayers();
}

//--------------------------------------------------------------
void WaterColorCanvas::update() {
    noiseFbo = applyShader(noiseShader, noiseFbo, SHADING_TYPE_NOISE);
    for (int i = 0; i < pigments.size(); i ++) {
        tempFbo = pigments[i].update(waterFbo, noiseFbo, tempFbo, pigmentShader);
    }
    waterFbo = applyShader(waterBleedingShader, waterFbo, SHADING_TYPE_WATER_BLEEDING);
    for (int i = 0; i < pigments.size(); i ++)  {
        paperFbo = applyShader(pigmentFixShader, paperFbo, SHADING_TYPE_PIGMENT_FIX, i);
    }
    paperFbo = applyShader(blurShader, paperFbo, SHADING_TYPE_BLUR);
}

//--------------------------------------------------------------
void WaterColorCanvas::draw() {
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    waterRenderShader.begin();
    waterFbo->draw(0, 0);
    waterRenderShader.end();
    
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    paperFbo->draw(0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    for (int i = 0; i < pigments.size(); i ++)  {
        tempFbo = applyShader(pigmentRenderShader, pigments[i].fbo, SHADING_TYPE_PIGMENT_RENDER, i);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        tempFbo->draw(0,0);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

//--------------------------------------------------------------
ofFbo* WaterColorCanvas::applyShader(ofShader& shader, ofFbo* fbo, int type, int pigmentNum) {
    tempFbo->begin();
    ofClear(0.f, 0.f, 0.f, 0.f);
    shader.begin();
    switch (type) {
        case SHADING_TYPE_NOISE:
            shader.setUniform1f("time", (float) ofGetFrameNum());
            break;
        case SHADING_TYPE_WATER_BLEEDING:
            shader.setUniformTexture("noise", *noiseFbo, 1);
            shader.setUniformTexture("water", *waterFbo, 2);
            break;
        case SHADING_TYPE_WATER_RENDER:
            break;
        case SHADING_TYPE_PIGMENT_FIX:
            shader.setUniformTexture("pigment", *pigments[pigmentNum].fbo, 1);
            shader.setUniform1f("r", pigments[pigmentNum].color.r);
            shader.setUniform1f("g", pigments[pigmentNum].color.g);
            shader.setUniform1f("b", pigments[pigmentNum].color.b);
            break;
        case SHADING_TYPE_PIGMENT_RENDER:
            shader.setUniform1f("r", pigments[pigmentNum].color.r);
            shader.setUniform1f("g", pigments[pigmentNum].color.g);
            shader.setUniform1f("b", pigments[pigmentNum].color.b);
            break;
        case SHADING_TYPE_BLUR:
            shader.setUniformTexture("noise", *noiseFbo, 1);
            shader.setUniformTexture("water", *waterFbo, 2);
            break;
    }
    
    fbo->draw(0, 0);
    shader.end();
    tempFbo->end();
    
    ofFbo *swap = tempFbo;
    tempFbo = fbo;
    return swap;
}

//--------------------------------------------------------------
void WaterColorCanvas::beginPigmentDraw(int i) {
    if (i < pigments.size()) {
        currentPigment = i;
        pigments[i].fbo->begin();
    }
}

//--------------------------------------------------------------
void WaterColorCanvas::endPigmentDraw() {
    pigments[currentPigment].fbo->end();
}

//--------------------------------------------------------------
void WaterColorCanvas::beginWaterDraw() {
    waterFbo->begin();
}

//--------------------------------------------------------------
void WaterColorCanvas::endWaterDraw() {
    waterFbo->end();
}


//--------------------------------------------------------------
void WaterColorCanvas::clearLayers() {
    clearFbo(waterFbo, 0, 0, 0);
    clearFbo(paperFbo, 255, 255, 255);
    
    for (int i = 0; i < pigments.size(); i ++) {
        clearFbo(pigments[i].fbo, 0, 0, 0);
    }
}

//--------------------------------------------------------------
void WaterColorCanvas::clearFbo(ofFbo *fbo, int r, int g, int b) {
    fbo->begin();
    ofClear(r, g, b, 255);
    fbo->end();
}

//--------------------------------------------------------------
void WaterColorCanvas::addPigment(ofColor color) {
    PigmentLayer p;
    p.color = color;
    pigments.push_back(p);
}