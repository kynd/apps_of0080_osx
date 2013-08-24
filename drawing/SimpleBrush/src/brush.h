

#ifndef __Brush__
#define __Brush__

#include "ofMain.h"
class Brush {
    
public:
    Brush();
    void begin(float x, float y);
    void end();
    void moveAndDraw(float x, float y, ofFbo& fbo);
private:
    bool isWorking;
    float width;
    ofVec2f pos, lastPos;
    vector<ofVec2f> brushTips;
    vector<ofVec2f> brushTipLogs;
    vector<float> brushTipDevs;
    vector<float> brushTipAlphas;
};


#endif /* defined(__Brush__) */
