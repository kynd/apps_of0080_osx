#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	frameByframe = false;

	movie.loadMovie("movie/fingers.mov");
    movie.setPaused(true);
    shader.load("shader/shader.vert", "shader/shader.frag");
    fbo.allocate(movie.width, movie.height);
    frameUpdate();
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xFFFFFF);
    movie.draw(20,20);
    fbo.draw(380, 20);
    ofDrawBitmapString("hit space to show next frame", 20, 400);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch(key){
        case ' ':
            frameUpdate();
        break;
    }
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
    
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
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

//--------------------------------------------------------------
void testApp::frameUpdate() {
    movie.nextFrame();
    movie.update();
    fbo.begin();
    shader.begin();
    movie.draw(0,0);
    shader.end();
    fbo.end();
}

