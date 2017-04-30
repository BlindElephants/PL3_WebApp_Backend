#include "ofApp.h"
#include "PL_BehaviorTypeGen.hpp"

bool ofApp::runPiece=false;

//--------------------------------------------------------------
void ofApp::setup(){
//    ofEnableAntiAliasing();
    ofSetWindowShape(400, 700);
    
    FollowGen::setup();

    pl_console::setSender("10.0.1.4", "10.0.1.5", "10.0.1.6", 7891);
    pl_console::setFbo(0, 0, 400, ofGetHeight());
    pl_console::addLine("server initialized");
    pl_console::addLine("number clients: 0");
    
    PL_VisServer::setup("10.0.1.3", 7891);
    
    PL_PerformerServer::setup("localhost", 7895);
    PL_PerformerServer::setMsgTimerLock(5.0f);
    
    PL_AuditoryMessageBuilder::init();
    
    ofSetBackgroundColor(ofColor::black);

    string soundAddr="localhost";
    int soundPort = 57120;
    
    PL_SoundSender::setup(soundAddr, soundPort);
    pl_console::addLine("connection to sound server at " + soundAddr + ": " + ofToString(soundPort));
    pl_console::addLine("connection to performer server at localhost: " + ofToString(7895));
    
    ofxLibwebsockets::ServerOptions s = ofxLibwebsockets::defaultServerOptions();
    s.port = 8080;
    s.bUseSSL=false;
    s.protocol = "echo-protocol";
    server.setup(s);
    server.addListener(this);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    PL_SoundSender::tick();
    
    if(ofApp::runPiece) {
        PL_PerformerServer::tick();
        PL_AuditoryMessageBuilder::tick();
    }
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


void ofApp::keyPressed(int key) {
    if(key == ' ') {
        ofApp::runPiece = !ofApp::runPiece;
        cout << ofApp::runPiece << endl;
        ofxOscMessage m;
        m.setAddress("/run/performance");
        m.addBoolArg(ofApp::runPiece);
        PL_VisServer::sendMessage(m);
    } else if(key == 'B') {
        ofxOscMessage m;
        m.setAddress("/grid/all/color");
        m.addFloatArg(0.0f);
        m.addFloatArg(5.5f);
        PL_VisServer::sendMessage(m);
    } else if(key == 'U') {
        ofxOscMessage m;
        m.setAddress("/grid/all/color");
        m.addFloatArg(255.0f);
        m.addFloatArg(2.0);
        PL_VisServer::sendMessage(m);
    }
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
    PL_VisServer::sendMessage(m);
    messages.push_back("number clients: " + ofToString(connections.size()));
}

void ofApp::onClose(ofxLibwebsockets::Event &args) {
    ofxOscMessage m;
    m.setAddress("/client/disconnected");
    auto c = connections.find(args.conn.getClientIP());
    if(c == connections.end()) {
        messages.push_back("ERROR: trying to remove connection that doesn't exist");
    } else {
        pl_console::addDisconnectedUser(c->second->getUserName());
        
        m.addIntArg(c->second->getId());
        PL_SoundSender::sendMessage(m);
        PL_VisServer::sendMessage(m);
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
            pl_console::addConnectedUser(a[0].asString());
            cout << a[0].asString() << ", " << a[1].asFloat() << ", " << a[2].asFloat() << ", " << a[3].asFloat() << endl;
            it->second->setClientUser(a[0].asString(), a[1].asFloat(), a[2].asFloat(), a[3].asFloat());
        }
    }
}

void ofApp::onBroadcast(ofxLibwebsockets::Event &args) {}
