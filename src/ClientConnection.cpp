//
//  ClientConnection.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 3/3/17.
//
//

#include "ClientConnection.hpp"
#include "PL_SoundSender.hpp" 

int ClientConnection::ClientID=0;

ClientConnection::ClientConnection(ofxLibwebsockets::Connection& _connection)
:
connection(_connection),
age(0.0),
timeSinceLastPing(0.0),
myId(ClientID++)
{
    gm=make_shared<PL_GoalManager>(ClientScreenDimensions, ClientObjectSize);
    im=make_shared<PL_InstructionManager>(gm, myId, connection, objects);
}

void ClientConnection::tick() {
    age += ofGetLastFrameTime();
    timeSinceLastPing+= ofGetLastFrameTime();
    if(timeSinceLastPing >= 2.5f) {
        Json::Value m;
        m["address"] = "/get/objects";
        connection.send(m.toStyledString());
        timeSinceLastPing = 0.0f;
    }
    im->update();
}

void ClientConnection::addObject(ofVec2f _position, bool _user) {
    normalizeCoords(_position);
    objects.push_back(_position);
    if(_user) {
        ofxOscMessage sm;
        sm.setAddress("/client/object_added");
        sm.addIntArg(myId);
        sm.addFloatArg(_position.x);
        sm.addFloatArg(_position.y);
        PL_SoundSender::sendMessage(sm);
    }
}

void ClientConnection::moveObject(int _index, ofVec2f _newPosition) {
    normalizeCoords(_newPosition);
    
    ofxOscMessage sm;
    sm.setAddress("/client/object_moved");
    sm.addIntArg(myId);
    sm.addFloatArg(objects[_index].x);
    sm.addFloatArg(objects[_index].y);
    sm.addFloatArg(_newPosition.x);
    sm.addFloatArg(_newPosition.y);
    PL_SoundSender::sendMessage(sm);
    
    objects[_index].set(_newPosition);
}

void ClientConnection::moveObject(ofVec2f _oldPosition, ofVec2f _newPosition) {
    
    normalizeCoords(_oldPosition);
    normalizeCoords(_newPosition);
    
    for (ofVec2f &o : objects) {
        if(o == _oldPosition) {
            o.set(_newPosition);
            ofxOscMessage sm;
            sm.setAddress("/client/object_moved");
            sm.addIntArg(myId);
            sm.addFloatArg(_oldPosition.x);
            sm.addFloatArg(_oldPosition.y);
            sm.addFloatArg(_newPosition.x);
            sm.addFloatArg(_newPosition.y);
            PL_SoundSender::sendMessage(sm);
        }
    }
}

void ClientConnection::removeObject(int _index) {
    
    ofxOscMessage sm;
    sm.setAddress("/client/object_removed");
    sm.addIntArg(myId);
    sm.addFloatArg(objects[_index].x);
    sm.addFloatArg(objects[_index].y);
    PL_SoundSender::sendMessage(sm);
    
    objects.erase(objects.begin()+_index);
}
void ClientConnection::removeObject(ofVec2f _position) {
    normalizeCoords(_position);
    
    float ti = -1;
    float d = 10000.0;
    
    for(int i = objects.size()-1 ; i>=0 ; i--) {
        float td = objects[i].squareDistance(_position);
        if(td<d) {
            d = td;
            ti = i;
        }
    }
    
    if(ti>=0) {
        objects.erase(objects.begin()+ti);
        ofxOscMessage sm;
        sm.setAddress("/client/object_removed");
        sm.addIntArg(myId);
        sm.addFloatArg(_position.x);
        sm.addFloatArg(_position.y);
        PL_SoundSender::sendMessage(sm);
    }
}

void ClientConnection::clearObjects() {objects.clear();}

void ClientConnection::setClientScreenDimensions(float w, float h, float objectSize) {
    ClientScreenDimensions.set(w, h);
    ClientObjectSize=objectSize;
    cout << "Screen Dimensions Set: " << w << ", " << h << endl;
}

void ClientConnection::normalizeCoords(ofVec2f &position) {
    position += (ClientScreenDimensions*0.5);
    position /= ClientScreenDimensions;
}


void ClientConnection::convertToScreenCoords(ofVec2f &position) {
    position *= ClientScreenDimensions;
    position -= (ClientScreenDimensions*0.5);
}
void ClientConnection::setObjects(vector<ofVec2f> _objects) {
    objects.clear();
    
    if(_objects.size()>0) {
        for(int i=0; i<_objects.size(); i++) {
            normalizeCoords(_objects[i]);
        }
    }
    
    objects=_objects;
    
    ofxOscMessage sm;
    sm.setAddress("/client/allobjects");
    sm.addIntArg(myId);
    sm.addIntArg(objects.size());
    if(objects.size()>0) {
        for(int i=0; i<objects.size(); i++ ) {
            sm.addFloatArg(objects[i].x);
            sm.addFloatArg(objects[i].y);
        }
    }
    PL_SoundSender::sendMessage(sm);
}

int ClientConnection::getId() { return myId; }

