#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxLibwebsockets.h"
#include "pl_console.hpp"
#include <unordered_map>
#include "ClientConnection.hpp"
#include "PL_SoundSender.hpp"
#include "PL_PerformerServer.hpp"
#include "PL_AuditoryMessageBuilder.hpp"

#include "PL_VisServer.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    
    
    ofxLibwebsockets::Server server;
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
    
    unordered_map<string,shared_ptr<ClientConnection>> connections;
    
    deque<string> messages;
    static bool runPiece;
};
