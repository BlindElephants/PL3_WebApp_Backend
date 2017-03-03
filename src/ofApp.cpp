#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    pl_console::setFbo(0, 0, 400, 150);
    pl_console::addLine("server initialized");
    pl_console::addLine("sending to localhost:57121");
    pl_console::addLine("receiving from node server on port:57120");
    pl_console::addLine("number clients: 0");
    
    ofSetBackgroundColor(ofColor::black);
    
    send.setup("localhost", 8887);
    recv.setup(8888);
    
    ofxOscMessage m;
    m.setAddress("/user/get_all/");
    send.sendMessage(m);
    
//    toSound.setup("Mts-iMac.local", 57120);
    toSound.setup("localhost", 57120);
}

//--------------------------------------------------------------
void ofApp::update(){


    while(recv.hasWaitingMessages()) {
        ofxOscMessage m;
        recv.getNextMessage(m);
        
        if(m.getAddress() == "/user/add/") {
            auto a = connectedUsers.insert(m.getArgAsString(0));
            
            //a.second is true if the element is added successfully
            //false if the element already exists by the same key
            if(!a.second) {
                pl_console::addLine("user already added, ERROR");
            }
            pl_console::addLine("user added: ");
            pl_console::addLine("    " + m.getArgAsString(0));
            pl_console::addLine("number clients: " + ofToString(connectedUsers.size()));
        }
        
        if(m.getAddress() == "/user/remove/") {
            connectedUsers.erase(m.getArgAsString(0));
            pl_console::addLine("user removed: ");
            pl_console::addLine("    " + m.getArgAsString(0));
            pl_console::addLine("number clients: " + ofToString(connectedUsers.size()));
            
        }
        
        if(m.getAddress() == "/user/existing/") {
            if(m.getNumArgs()>0) {
                for(int i = 0 ; i < m.getNumArgs() ; i++ ) {
                    auto a = connectedUsers.insert(m.getArgAsString(i));
                    if(!a.second) {
                        pl_console::addLine("user already added, ERROR");
                    }
                    pl_console::addLine("user added: ");
                    pl_console::addLine("    " + m.getArgAsString(i));
                    pl_console::addLine("number clients: " + ofToString(connectedUsers.size()));
                }
            }
        }
//        
//        cout << m.getAddress() ;
//        
//        for(int i = 0 ; i < m.getNumArgs() ; i++ ) {
//            cout << ", " << m.getArgAsString(i);
//        }
//        
//        cout << endl;

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
                
                //anything addressed with this will be forwarded to a single client
                m.setAddress("/client_message/");
                
                //this is the client to whom the message should go
                m.addStringArg(*connectedUsers.begin());
                
                //tell the client this is a command to add a element
                m.addStringArg("add");
                
                //these are the X and Y coords for that element (normalized)
                m.addFloatArg(ofRandom(1));
                m.addFloatArg(ofRandom(1));
                
                //duration of the element
                m.addFloatArg(ofRandom(0.5f, 10.0f));
                
                //delay until that element is spawned
                m.addFloatArg(ofRandom(1.0, 5.0));
                
                //send
                send.sendMessage(m);
            }
        }
            break;

            
        case 'S' : {
            ofxOscMessage m;
            m.setAddress("/test");
            m.addFloatArg(ofRandom(10000));
            m.addFloatArg(ofRandom(-1, 1));
            m.addFloatArg(ofRandom(1));
            m.addFloatArg(ofRandom(2));
            toSound.sendMessage(m);
        }
    }
}
