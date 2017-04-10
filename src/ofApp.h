#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxLibwebsockets.h"
#include "pl_console.hpp"

#include <unordered_set>
#include <unordered_map>

#include "ClientConnection.hpp"
#include "PL_SoundSender.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void exit();
    
//    ofxOscSender toSound;
    
    unordered_set<string> connectedUsers;
    
    ofxLibwebsockets::Server server;
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
    
    unordered_map<string,shared_ptr<ClientConnection>> connections;
    
    deque<string> messages;
};
