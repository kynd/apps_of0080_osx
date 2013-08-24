#pragma once

#include "ofMain.h"
#include "WaterColorCanvas.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    void strokeDraw();
    void clearLayers();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofImage bg;
    ofImage brush;
    WaterColorCanvas canvas;
    
    ofPoint pos, prev, vec;
    float width, currentWidth;
    int currentPigment;
    bool pressed;
    
    int state;
    static const int STATE_WATER = 0;
    static const int STATE_PIGMENT = 1;
    static const int STATE_MIX = 2;
};