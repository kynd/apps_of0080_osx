#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255);
    fbo.allocate(1280, 720);
    
    fbo.begin();
    ofClear(128, 128, 128, 256);
    fbo.end();
}

//--------------------------------------------------------------
void testApp::update(){
    brush.moveAndDraw(mouseX, mouseY, fbo);
}

//--------------------------------------------------------------
void testApp::draw(){
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    brush.begin(x, y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    brush.end();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
