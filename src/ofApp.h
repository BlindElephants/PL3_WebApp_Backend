#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "pl_console.hpp"

#include <unordered_set>

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofxOscSender   send;
    ofxOscReceiver recv;
    
    unordered_set<string> connectedUsers;
};
