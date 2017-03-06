//
//  ClientConnection.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 3/3/17.
//
//

#include "ClientConnection.hpp"

int ClientConnection::ClientID=0;

ClientConnection::ClientConnection(ofxLibwebsockets::Connection& _connection, ofxOscSender& _toSoundRef)
:
connection(_connection),
toSoundRef(_toSoundRef),
age(0.0),
timeSinceLastPing(0.0),
myId(ClientID++)
{

}

void ClientConnection::tick() {
    age += ofGetLastFrameTime();
    timeSinceLastPing+= ofGetLastFrameTime();
    
    if(timeSinceLastPing >= 2.5f) {
        Json::Value m;
        m["address"] = "/get/objects";
        connection.send(m.toStyledString());
        timeSinceLastPing = 0.0f;
        
        int t = ofRandom(3);
        
        if(t==0) {
            if(objects.size()) {
                sendRemoveInstr(objects[ofRandom(objects.size())]);
            }
        } else if(t==1) {
            if(objects.size()) {
                sendMoveInstr(objects[ofRandom(objects.size())], ofVec2f(ofRandom(0, 1), ofRandom(0, 1)));
            }
        } else if(t==2) {
            sendAddInstr(ofVec2f(ofRandom(0, 1), ofRandom(0, 1)), ofRandom(5.0), ofRandom(5.0));
        }
    }
}

void ClientConnection::addObject(ofVec2f _position, bool _user) {
    normalizeCoords(_position);
    objects.push_back(_position);
    if(_user) {
        ofxOscMessage sm;
        sm.setAddress("/client/object_added");
        sm.addFloatArg(_position.x);
        sm.addFloatArg(_position.y);
        toSoundRef.sendMessage(sm);
    }
}

void ClientConnection::moveObject(int _index, ofVec2f _newPosition) {
    normalizeCoords(_newPosition);
    
    ofxOscMessage sm;
    sm.setAddress("/client/object_moved");
    sm.addFloatArg(objects[_index].x);
    sm.addFloatArg(objects[_index].y);
    sm.addFloatArg(_newPosition.x);
    sm.addFloatArg(_newPosition.y);
    toSoundRef.sendMessage(sm);
    
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
            sm.addFloatArg(_oldPosition.x);
            sm.addFloatArg(_oldPosition.y);
            sm.addFloatArg(_newPosition.x);
            sm.addFloatArg(_newPosition.y);
            toSoundRef.sendMessage(sm);
        }
    }
}

void ClientConnection::removeObject(int _index) {
    
    ofxOscMessage sm;
    sm.setAddress("/client/object_removed");
    sm.addFloatArg(objects[_index].x);
    sm.addFloatArg(objects[_index].y);
    toSoundRef.sendMessage(sm);
    
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
        sm.addFloatArg(_position.x);
        sm.addFloatArg(_position.y);
        toSoundRef.sendMessage(sm);
    }
}

void ClientConnection::clearObjects() {
    objects.clear();
}

void ClientConnection::makeNewGoal(int numGoalPoints) {
    goal.clear();
    
    ofxOscMessage sm;
    sm.setAddress("/client/goal_generated");
    
    for(int i = 0 ; i < numGoalPoints ; i ++ ) {
        goal.push_back(ofVec2f(ofRandom(1), ofRandom(1)));
        sm.addFloatArg(goal.back().x);
        sm.addFloatArg(goal.back().y);
    }
    
    toSoundRef.sendMessage(sm);
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

void ClientConnection::sendAddInstr(ofVec2f _goalPosition, float _duration, float _delay) {
    Json::Value m;
    
    ofVec2f _g = _goalPosition;
    
    convertToScreenCoords(_goalPosition);
    m["address"] = "/instruction/add";
    m["args"].append(_goalPosition.x);
    m["args"].append(_goalPosition.y);
    m["args"].append(_duration);
    m["args"].append(_delay);
    connection.send(m.toStyledString());
    pl_console::addLine("add instruction sent");
    
    ofxOscMessage sm;
    sm.setAddress("/instruction/add");
    sm.addFloatArg(_g.x);
    sm.addFloatArg(_g.y);
    sm.addFloatArg(_duration);
    sm.addFloatArg(_delay);
    toSoundRef.sendMessage(sm);
}

void ClientConnection::sendRemoveInstr(ofVec2f _goalPosition, float _duration, float _delay) {
    Json::Value m;
    
    ofVec2f _g = _goalPosition;
    
    convertToScreenCoords(_goalPosition);
    
    m["address"] = "/instruction/remove";
    m["args"].append(_goalPosition.x);
    m["args"].append(_goalPosition.y);
    m["args"].append(_duration);
    m["args"].append(_delay);
    connection.send(m.toStyledString());
    pl_console::addLine("remove instruction sent");
    
    ofxOscMessage sm;
    sm.setAddress("/instruction/remove");
    sm.addFloatArg(_g.x);
    sm.addFloatArg(_g.y);
    sm.addFloatArg(_duration);
    sm.addFloatArg(_delay);
    toSoundRef.sendMessage(sm);
}

void ClientConnection::sendMoveInstr(ofVec2f _startPosition, ofVec2f _endPosition, float _duration, float _delay) {
    Json::Value m;
    
    ofVec2f _s = _startPosition;
    ofVec2f _e = _endPosition;
    
    convertToScreenCoords(_startPosition);
    convertToScreenCoords(_endPosition);
    
    m["address"] = "/instruction/move";
    m["args"].append(_startPosition.x);
    m["args"].append(_startPosition.y);
    m["args"].append(_endPosition.x);
    m["args"].append(_endPosition.y);
    m["args"].append(_duration);
    m["args"].append(_delay);
    connection.send(m.toStyledString());
    pl_console::addLine("move instruction sent");
    
    ofxOscMessage sm;
    sm.setAddress("/instruction/move");
    sm.addFloatArg(_s.x);
    sm.addFloatArg(_s.y);
    sm.addFloatArg(_e.x);
    sm.addFloatArg(_e.y);
    sm.addFloatArg(_duration);
    sm.addFloatArg(_delay);
    toSoundRef.sendMessage(sm);
}

int ClientConnection::getId() { return myId; }
