
#include "Brush.h"


Brush::Brush():
isWorking(false),
pos(0,0)
{
}
void Brush::begin(float x, float y){
    isWorking = true;
    pos.set(x, y);
    lastPos.set(x, y);
    width = ofRandom(50, 400);
    
    for (int i = 0; i < width * 4; i ++) {
        brushTipDevs.push_back(ofRandom(-width / 2, width / 2));
        brushTipAlphas.push_back(ofRandom(10, 40));
        float radius = ofRandom(width / 2);
        float theta = ofRandom(TWO_PI);
        brushTips.push_back(ofVec2f(x + cos(theta) * radius, y + sin(theta) * radius));
        brushTipLogs.push_back(ofVec2f(x + cos(theta) * radius, y + sin(theta) * radius));
    }
}

void Brush::end(){
    isWorking = false;
    brushTips.clear();
    brushTipLogs.clear();
    brushTipDevs.clear();
    brushTipAlphas.clear();
}

void Brush::moveAndDraw(float x, float y, ofFbo& fbo){
    ofPushStyle();
    pos.set(x, y);
    if (pos == lastPos || !isWorking) return;
    ofVec2f direc = pos - lastPos;
    ofVec2f perp = direc.perpendicular().normalize();
    ofVec2f target, diff, sum(0,0);
    lastPos.set(pos);
    
    fbo.begin();
    for (int i = 0; i < brushTips.size(); i ++) {
        target.set(perp.x * brushTipDevs[i] + x, perp.y * brushTipDevs[i] + y);
        brushTips[i] += (target - brushTips[i]) * 0.1;
        diff.set((target - brushTips[i]).normalize());
        ofSetColor(128 + diff.x * 128, 128 + diff.y * 128, 0, brushTipAlphas[i]);
        ofLine(brushTips[i], brushTipLogs[i]);
        brushTipLogs[i].set(brushTips[i]);
        sum += brushTips[i];
    }
    fbo.end();
    ofPopStyle();
    
    sum /= brushTips.size();
    lastPos.set(sum);
    
}