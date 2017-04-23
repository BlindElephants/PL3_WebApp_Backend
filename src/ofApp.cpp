#include "ofApp.h"
#include "PL_BehaviorTypeGen.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofEnableAntiAliasing();
    ofSetWindowShape(400, 700);
    
    FollowGen::setup();

    pl_console::setSender("10.0.1.7", 7891);
//    pl_console::setSender("10.0.1.17", 7891);
    pl_console::setFbo(0, 0, 400, ofGetHeight());
    pl_console::addLine("server initialized");
    pl_console::addLine("number clients: 0");
    ofSetBackgroundColor(ofColor::black);

    string soundAddr="localhost";
    int soundPort = 57120;
    
    PL_SoundSender::setup(soundAddr, soundPort);
    pl_console::addLine("connection to sound server at " + soundAddr + ": " + ofToString(soundPort));
    
    ofxLibwebsockets::ServerOptions s = ofxLibwebsockets::defaultServerOptions();
    s.port = 8080;
    s.bUseSSL=false;
    s.protocol = "echo-protocol";
    server.setup(s);
    server.addListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){
    while(messages.size()>0) {
        pl_console::addLine(messages.front());
        messages.pop_front();
    }
    for(auto it=connections.begin(); it!=connections.end(); ++it) {it->second->tick();}
}

//--------------------------------------------------------------
void ofApp::draw(){pl_console::draw();}


void ofApp::exit() {
    ofxOscMessage m;
    m.setAddress("/server/closed");
    PL_SoundSender::sendMessage(m);
}


void ofApp::onConnect(ofxLibwebsockets::Event &args) {cout << "client connected" << endl;}

void ofApp::onOpen(ofxLibwebsockets::Event &args) {
    shared_ptr<ClientConnection> cc = make_shared<ClientConnection>(args.conn);
    std::pair<string, shared_ptr<ClientConnection>> thisConnection(args.conn.getClientIP(), cc);
    connections.insert(thisConnection);
    Json::Value md;
    md["address"] = "/get/user";
    args.conn.send(md.toStyledString());
    Json::Value mo;
    mo["address"] = "/get/objects";
    args.conn.send(mo.toStyledString());
    ofxOscMessage m;
    m.setAddress("/client/connected");
    m.addIntArg(cc->getId());
    PL_SoundSender::sendMessage(m);
    messages.push_back("number clients: " + ofToString(connections.size()));    
}

void ofApp::onClose(ofxLibwebsockets::Event &args) {
    ofxOscMessage m;
    m.setAddress("/client/disconnected");
    auto c = connections.find(args.conn.getClientIP());
    if(c == connections.end()) {
        messages.push_back("ERROR: trying to remove connection that doesn't exist");
    } else {
        m.addIntArg(c->second->getId());
        PL_SoundSender::sendMessage(m);
        connections.erase(args.conn.getClientIP());
        messages.push_back("number clients: " + ofToString(connections.size()));
    }
    
}

void ofApp::onIdle(ofxLibwebsockets::Event &args) {}

void ofApp::onMessage(ofxLibwebsockets::Event &args) {
    auto it = connections.find(args.conn.getClientIP());
    if(it != connections.end()) {
        Json::Value a = args.json["args"];
        if(args.json["address"] == "/client/object/added") {
            messages.push_back("[" + it->second->getUserName() + "] geom added: (" + ofToString(a[0].asFloat()) + ", " + ofToString(a[1].asFloat()) + ")");
            it->second->addObject(ofVec2f(a[0].asFloat(), a[1].asFloat()));
        } else if(args.json["address"] == "/client/object/moved") {
            messages.push_back("[" + it->second->getUserName() + "] geom moved: (" + ofToString(a[0].asFloat()) + ", " + ofToString(a[1].asFloat()) + ") -> (" + ofToString(a[2].asFloat()) + ", " + ofToString(a[3].asFloat()) + ")");
            it->second->moveObject(ofVec2f(a[0].asFloat(), a[1].asFloat()), ofVec2f(a[2].asFloat(), a[3].asFloat()));
        } else if(args.json["address"] == "/client/object/removed") {
            messages.push_back("[" + it->second->getUserName() + "] geom removed: (" + ofToString(a[0].asFloat()) + ", " + ofToString(a[1].asFloat()) + ")");
            it->second->removeObject(ofVec2f(a[0].asFloat(), a[1].asFloat()));
        } else if(args.json["address"] == "/client/objects") {
            it->second->clearObjects();
            vector<ofVec2f>allObjects;
            for(int i = 0 ; i < a.size() ; i ++ ) {
                allObjects.push_back(ofVec2f(a[i]["x"].asFloat(), a[i]["y"].asFloat()));
            }
            it->second->setObjects(allObjects);
        } else if(args.json["address"] == "/client/user") {
            messages.push_back("User Name: " + a[0].asString() + " device dimensions: " + ofToString(a[1].asFloat()) + ", " + ofToString(a[2].asFloat()));

            cout << a[0].asString() << ", " << a[1].asFloat() << ", " << a[2].asFloat() << ", " << a[3].asFloat() << endl;
            it->second->setClientUser(a[0].asString(), a[1].asFloat(), a[2].asFloat(), a[3].asFloat());
        }
    }
}

void ofApp::onBroadcast(ofxLibwebsockets::Event &args) {}
