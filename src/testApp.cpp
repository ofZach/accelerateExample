#include "testApp.h"
#include <Accelerate/Accelerate.h>

#define  howMany  100000
float xvalsOrig[256*howMany] __attribute__ ((aligned));
float yvalsOrig[256*howMany] __attribute__ ((aligned));


float xvals[256*howMany] __attribute__ ((aligned));
float yvals[256*howMany] __attribute__ ((aligned));
float outVector[256*howMany] __attribute__ ((aligned));


float xvalsFrom[256*howMany] __attribute__ ((aligned));
float yvalsFrom[256*howMany] __attribute__ ((aligned));
float results[howMany] __attribute__ ((aligned));

int smallestIndex = -1;


void randomVals(){

    for (int i = 0; i < howMany; i++){
        
        float angleSpeedA = ofRandom(-8, 8);
        float angleSpeedB = ofRandom(-8, 8);
        float adderSpeed = ofRandom(0.001, 0.01);
        float angle = ofRandom(0,TWO_PI);
                               
        for (int j = 0; j < 256; j++){
       
            
            xvalsOrig[i * 256 + j] = 128 + 128 * cos(angle * angleSpeedA);
            yvalsOrig[i * 256 + j] = 128 + 128 * sin(angle * angleSpeedB);
            
            angle += adderSpeed;
            
        }
    }
}

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    
    elapsedTime = 0;
    
    
    randomVals();

    
    ofNoFill();
    
    for (int i = 0; i < howMany; i++){
        for (int j = 0; j < 256; j++){
            xvalsFrom[i*256+ j] = j;
            yvalsFrom[i*256+ j] = 100;
        }
    }
    
    //vDSP_vadd(xvals, 1, yvals, 1, outVector, 1, 256);
    
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofDrawBitmapStringHighlight("closest to stright line", ofPoint(30,300));
    
    if (smallestIndex != -1){
        ofBeginShape();
        for (int i = 0; i < 256; i++){
            ofVertex(xvalsOrig[smallestIndex * 256 + i],yvalsOrig[smallestIndex* 256 + i]);
        }
        ofEndShape();
    }
    
    
    
    int who = ofClamp( ((int)(ofGetElapsedTimef()*60))%howMany, 0,howMany-1);
    ofBeginShape();
    for (int i = 0; i < 256; i++){
        ofVertex(xvalsOrig[who * 256 + i] + 600,yvalsOrig[who* 256 + i]);
    }
    ofEndShape();
    
    ofDrawBitmapStringHighlight("all generated shapes", ofPoint(600,300));
    

    ofDrawBitmapStringHighlight("press '1'  to generate more shapes\npress ' ' to calculate closest, 'h' for by hand\nnote: I've noticed  this be slow the first couple of times on solving...", ofPoint(30,400));
    
    
    ofDrawBitmapStringHighlight("elapsedTime " + ofToString(elapsedTime), ofPoint(30,450));
    ofDrawBitmapStringHighlight("elapsedTime (by hand) " + ofToString(nonAccerateTime), ofPoint(30,500));
    
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == '1'){
        
        smallestIndex = -1;
        randomVals();
        
//        for (int i = 0; i < howMany; i++){
//            for (int j = 0; j < 256; j++){
//                xvalsOrig[i * 256 + j] = ofRandom(0,256);
//                yvalsOrig[i * 256 + j] = ofRandom(0,256);
//                
//            }
//        }
    } else if (key == ' ' ){

        float startTime = ofGetElapsedTimef();
        float smallest = 1000000000;
        
        vDSP_vsub(xvalsOrig, 1, xvalsFrom, 1, xvals, 1, 256*howMany);
        vDSP_vsub(yvalsOrig, 1, yvalsFrom, 1, yvals, 1, 256*howMany);
        
        
        vDSP_vdist(xvals, 1, yvals, 1, outVector, 1, 256*howMany);
        for (int i = 0; i< howMany; i++){
            
                        
            vDSP_meanv(outVector + i*256,1,results + i,256);
            //printf("%f %f \n", *(results + i), avg);
            if (*(results + i) < smallest){
                
                //printf("%f %f \n", *(results + i), smallest);
                smallest = *(results + i);
                smallestIndex = i;
                
            }
        }
        
        elapsedTime = ofGetElapsedTimef() - startTime;
    } else if (key == 'h'){
        
        float startTime = ofGetElapsedTimef();
        float smallest = FLT_MAX;
        float avg = 0;
        
        for (int i = 0; i < howMany*256; i++){
            avg +=  (xvalsOrig[i] - xvalsFrom[i]) * (xvalsOrig[i] - xvalsFrom[i])
                +   (yvalsOrig[i] - yvalsFrom[i]) * (yvalsOrig[i] - yvalsFrom[i]);
            
            if((i + 1) % 256 == 0 ){
                avg /= 256.0;
                
                if( avg < smallest ){
                    smallest = avg;
                    smallestIndex = i / 256;
                }
                avg = 0;
            }
        }
        
        nonAccerateTime = ofGetElapsedTimef() - startTime;
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