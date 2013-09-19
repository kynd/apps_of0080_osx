#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    mesh.setMode(OF_PRIMITIVE_LINES);
    ofBackground(0);
}

//--------------------------------------------------------------
void testApp::update(){
    boid.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofSetColor(255,255,255);
    mesh.clear();
    for (int i = 0; i < boid.preys.size(); i ++) {
        mesh.addVertex(boid.preys[i].position);
        mesh.addVertex(boid.preys[i].position + boid.preys[i].velocity * 3);
    }
    mesh.draw();
    
    ofSetColor(255,0,0);
    mesh.clear();
    for (int i = 0; i < boid.predators.size(); i ++) {
        mesh.addVertex(boid.predators[i].position);
        mesh.addVertex(boid.predators[i].position + boid.predators[i].velocity * 6);
    }
    mesh.draw();
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
