//
//  pl_console.cpp
//  PL2_FLOOR
//
//  Created by EMPAC Video on 2/7/17.
//
//

#include "pl_console.hpp"

pl_console::pl_console() {
    font.load("courier", 8);
    fbo.allocate(600, 900);
    fbo.begin();
    ofClear(ofColor::black);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(1, 1, fbo.getWidth()-2, fbo.getHeight()-2);
    fbo.end();
}

pl_console &pl_console::instance() {
    static pl_console c;
    return c;
}

void pl_console::setSender(string addrPiA, string addrPiB, string addrPiC, int port) {
    instance().senderPiA.setup(addrPiA, port);
    instance().senderPiB.setup(addrPiB, port);
    instance().senderPiC.setup(addrPiC, port);
}

void pl_console::addLine(string l) {
    
    ofxOscMessage m;
    m.setAddress("/term/line");
    m.addStringArg(l);
    instance().senderPiA.sendMessage(m);
    instance().senderPiB.sendMessage(m);
    instance().senderPiC.sendMessage(m);
    
    instance().lines.push_back(l);
    while(instance().lines.size()>(instance().fbo.getHeight()/12)-1) {
        instance().lines.erase(instance().lines.begin());
    }
    instance().fbo.begin();
    ofClear(ofColor::black);
    ofSetColor(ofColor::white);
    if(instance().lines.size()) {
        for(int i = 0 ; i < instance().lines.size() ; i++ ) {
            instance().font.drawString(instance().lines[i], 8, (i*12)+10);
        }
    }
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(1, 1, instance().fbo.getWidth()-2, instance().fbo.getHeight()-2);
    instance().fbo.end();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

void pl_console::addPerformerLine(int performerIndex, string l) {
    ofxOscMessage m;
    m.setAddress("/perf/line");
    m.addStringArg(l);
    
    if(performerIndex==0) {
        instance().senderPiB.sendMessage(m);
    } else if(performerIndex==1) {
        instance().senderPiC.sendMessage(m);
    }
}

void pl_console::updateAudioCue(int performerIndex, string l) {
    ofxOscMessage m;
    m.setAddress("/performer/audio");
    m.addStringArg(l);
    if(performerIndex==0) {
        instance().senderPiB.sendMessage(m);
    } else if(performerIndex==1) {
        instance().senderPiC.sendMessage(m);
    }
}

void pl_console::draw() {
    ofSetColor(ofColor::white);
    ofFill();
    ofPushMatrix();
    ofTranslate(instance().fboDrawPosition);
    instance().fbo.draw(0, 0);
    ofPopMatrix();
}

void pl_console::setFbo(float x, float y, float w, float h) {
    instance().fbo.allocate(w, h, GL_RGBA, 2);
    instance().fbo.begin();
    ofClear(ofColor::black);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(1, 1, instance().fbo.getWidth()-2, instance().fbo.getHeight()-2);
    instance().fbo.end();
    instance().fboDrawPosition.set(x,y);
}

void pl_console::addConnectedUser(string userName) {
    ofxOscMessage m;
    m.setAddress("/user/connected");
    m.addStringArg(userName);
    instance().senderPiA.sendMessage(m);
}

void pl_console::addDisconnectedUser(string userName) {
    ofxOscMessage m;
    m.setAddress("/user/disconnected");
    m.addStringArg(userName);
    instance().senderPiA.sendMessage(m);
}
