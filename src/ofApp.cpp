#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(false);
    
    font.load("courier", 12);
    numClientsConnected=0;
    
    
    pl_console::setFbo(0, 0, 400, 150);

    pl_console::addLine("server initialized");
    pl_console::addLine("sending to localhost:57121");
    pl_console::addLine("receiving from node server on port:57120");
    
    pl_console::addLine("number clients: " + ofToString(numClientsConnected));
    
    ofSetBackgroundColor(ofColor::black);
    
    send.setup("localhost", 57121);
    recv.setup(57120);
}

//--------------------------------------------------------------
void ofApp::update(){
    while(recv.hasWaitingMessages()) {
        ofxOscMessage m;
        recv.getNextMessage(m);
        
        
        pl_console::addLine("--msg recv'd");
        pl_console::addLine("    " + m.getAddress());
        
        string s = "    ";
        
        if(m.getNumArgs()>0) {
            for(int i = 0 ; i < m.getNumArgs() ; i ++ ) {
                s += "[" + ofToString(i) + "] ";
                switch (m.getArgType(i)) {
                    OFXOSC_TYPE_TRUE:
                        s += "true";
                        break;
                        
                    OFXOSC_TYPE_FALSE:
                        s += "false";
                        break;
                        
                    OFXOSC_TYPE_FLOAT:
                        s += ofToString(m.getArgAsFloat(i));
                        break;
                        
                    OFXOSC_TYPE_INT32:
                        s+= ofToString(m.getArgAsInt32(i));
                        break;
                        
                    OFXOSC_TYPE_INT64:
                        s+= ofToString(m.getArgAsInt64(i));
                        break;
                        
                    OFXOSC_TYPE_STRING:
                        s+= m.getArgAsString(i);
                        break;
                        
                    default:
                        s += m.getArgAsString(i);
                        break;
                }
            }
        }
//        pl_console::addLine(s);
        
        if(m.getAddress() == "/user/add/") {
            auto a = connectedUsers.insert(m.getArgAsString(0));
            if(!a.second) {
                pl_console::addLine("user already added, ERROR");
            }
            pl_console::addLine("user added: ");
            pl_console::addLine("    " + m.getArgAsString(0));
            pl_console::addLine("num users: " + ofToString(connectedUsers.size()));
        }
        
        if(m.getAddress() == "/user/remove/") {
            connectedUsers.erase(m.getArgAsString(0));
            pl_console::addLine("user removed: ");
            pl_console::addLine("    " + m.getArgAsString(0));
            pl_console::addLine("num users: " + ofToString(connectedUsers.size()));
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    pl_console::draw();
}

void ofApp::keyPressed(int key) {
    switch (key) {
           
        case ' ': {
            if(connectedUsers.size()) {
                ofxOscMessage m;
                m.setAddress("/client_message/");
                m.addStringArg(*connectedUsers.begin());
                m.addIntArg(ofRandom(10000));
                m.addIntArg(ofRandom(10000));
                send.sendMessage(m);
            }
        }
            
    }
}
