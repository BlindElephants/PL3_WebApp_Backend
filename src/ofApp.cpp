#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    pl_console::setFbo(0, 0, 400, ofGetHeight());
    pl_console::addLine("server initialized");
    pl_console::addLine("sending to localhost:57121");
    pl_console::addLine("receiving from node server on port:57120");
    pl_console::addLine("number clients: 0");
    
    ofSetBackgroundColor(ofColor::black);

    toSound.setup("Mts-iMac.local", 57120);
//    toSound.setup("localhost", 57120);
    
    ofxLibwebsockets::ServerOptions s = ofxLibwebsockets::defaultServerOptions();
    s.port = 8080;
    s.bUseSSL=false;
    s.protocol = "echo-protocol";
    server.setup(s);
    server.addListener(this);
    
    cout << server.getProtocol() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    while(messages.size()>0) {
        pl_console::addLine(messages.front());
        messages.pop_front();
    }
    for(auto it = connections.begin() ; it != connections.end() ; ++it) {
        it->second->tick();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    pl_console::draw();
}

void ofApp::keyPressed(int key) {
    switch (key) {

            
        case 'S' : {
            ofxOscMessage m;
            m.setAddress("/pl3_sound_server");
            m.addFloatArg(ofRandom(10000));
            m.addFloatArg(ofRandom(-1, 1));
            m.addFloatArg(ofRandom(1));
            m.addFloatArg(ofRandom(2));
            toSound.sendMessage(m);
        }
    }
}


void ofApp::onConnect(ofxLibwebsockets::Event &args) {
    cout << "client connected" << endl;
}

void ofApp::onOpen(ofxLibwebsockets::Event &args) {
    cout << "client connected" << endl;
    cout << "    " << args.conn.getClientIP() << endl;
    shared_ptr<ClientConnection> cc = make_shared<ClientConnection>(args.conn);
    std::pair<string, shared_ptr<ClientConnection>> thisConnection(args.conn.getClientIP(), cc);
    connections.insert(thisConnection);
    
//    Json::Value m;
//    m["address"] = "/get/objects";
//    connection.send(m.toStyledString());
    
    Json::Value md;
    md["address"] = "/get/dimensions";
    args.conn.send(md.toStyledString());
    
    Json::Value mo;
    mo["address"] = "/get/objects";
    args.conn.send(mo.toStyledString());
}

void ofApp::onClose(ofxLibwebsockets::Event &args) {
    cout << "client closed" << endl;
    cout << "    " << args.conn.getClientIP() << endl;
    connections.erase(args.conn.getClientIP());
}

void ofApp::onIdle(ofxLibwebsockets::Event &args) {
    
}

void ofApp::onMessage(ofxLibwebsockets::Event &args) {
    messages.push_back("message recv'd from: " + args.conn.getClientIP());
    messages.push_back("    at addr: " + args.json["address"].asString());
    
    auto it = connections.find(args.conn.getClientIP());
    if(it != connections.end()) {
        Json::Value a = args.json["args"];
        if(args.json["address"] == "/client/object/added") {
            it->second->addObject(ofVec2f(a[0].asFloat(), a[1].asFloat()));
        } else if(args.json["address"] == "/client/object/moved") {
            it->second->moveObject(ofVec2f(a[0].asFloat(), a[1].asFloat()), ofVec2f(a[2].asFloat(), a[3].asFloat()));
        } else if(args.json["address"] == "/client/object/removed") {
            it->second->removeObject(ofVec2f(a[0].asFloat(), a[1].asFloat()));
        } else if(args.json["address"] == "/client/objects") {
            it->second->clearObjects();
            for(int i = 0 ; i < a.size() ; i ++ ) {
                it->second->addObject(ofVec2f(a[i]["x"].asFloat(), a[i]["y"].asFloat()));
            }
        } else if(args.json["address"] == "/client/dimensions") {
            it->second->setClientScreenDimensions(a[0].asFloat(), a[1].asFloat());
        }
    }
}

void ofApp::onBroadcast(ofxLibwebsockets::Event &args) {
    
}
