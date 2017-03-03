//
//  ClientConnection.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 3/3/17.
//
//

#include "ClientConnection.hpp"

ClientConnection::ClientConnection(ofxLibwebsockets::Connection& _connection)
:
connection(_connection),
age(0.0),
timeSinceLastPing(0.0)
{

}

void ClientConnection::tick() {

    
    age += ofGetLastFrameTime();
    timeSinceLastPing+= ofGetLastFrameTime();
    
    if(timeSinceLastPing >= 10.0f) {
        Json::Value m;
        m["address"] = "/get/objects";
        connection.send(m.toStyledString());
        timeSinceLastPing = 0.0f;
    }
}

void ClientConnection::addObject(ofVec2f _position) {
    normalizeCoords(_position);
    objects.push_back(_position);
}

void ClientConnection::moveObject(int _index, ofVec2f _newPosition) {
    normalizeCoords(_newPosition);
    objects[_index].set(_newPosition);
}

void ClientConnection::moveObject(ofVec2f _oldPosition, ofVec2f _newPosition) {
    
    normalizeCoords(_oldPosition);
    normalizeCoords(_newPosition);
    
    for (ofVec2f &o : objects) {
        if(o == _oldPosition) {
            o.set(_newPosition);
        }
    }
}

void ClientConnection::removeObject(int _index) {
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
    
    if(ti>=0) objects.erase(objects.begin()+ti);
}

void ClientConnection::clearObjects() {
    objects.clear();
}

void ClientConnection::makeNewGoal() {
    goal.clear();
    for(int i = 0 ; i < 10 ; i ++ ) {
        goal.push_back(ofVec2f(ofRandom(1), ofRandom(1)));
    }
}

void ClientConnection::setClientScreenDimensions(float w, float h) {
    ClientScreenDimensions.set(w, h);
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

