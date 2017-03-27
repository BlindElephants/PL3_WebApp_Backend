//
//  ClientConnection.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 3/3/17.
//
//

#ifndef ClientConnection_hpp
#define ClientConnection_hpp

#include "ofMain.h"
#include "ofxLibwebsockets.h"
#include "ofxOsc.h"
#include "pl_console.hpp"

class ClientConnection {
public:
    static int ClientID;
    
    void addObject(ofVec2f _position, bool _user=true);
    void moveObject(int _index, ofVec2f _newPosition);
    void moveObject(ofVec2f _oldPosition, ofVec2f _newPosition);
    void removeObject(int _index);
    void removeObject(ofVec2f _position);
    void clearObjects();
    
    void setObjects(vector<ofVec2f> _objects);
    
    void makeNewGoal(int numGoalPoints=10);
    void setClientScreenDimensions(float w, float h);
    void tick();
    
    void sendAddInstr(ofVec2f _goalPosition, float _duration=4.0f, float _delay=0.0f);
    void sendRemoveInstr(ofVec2f _goalPosition, float _duration=4.0f, float _delay=0.0f);
    void sendMoveInstr(ofVec2f _startPosition, ofVec2f _endPosition, float _duration=4.0f, float _delay=0.0f);
    
    int getId();
    
    ClientConnection(ofxLibwebsockets::Connection& _connection, ofxOscSender& _toSoundRef);
    
private:
    void normalizeCoords(ofVec2f &position);
    void convertToScreenCoords(ofVec2f &position);
    
    ofxLibwebsockets::Connection& connection;
    float age;
    vector < ofVec2f > objects;
    float timeSinceLastPing;
    
    ofVec2f ClientScreenDimensions;
    
    vector < ofVec2f > goal[3];
    
    ofxOscSender& toSoundRef;
    
    const int myId;
};

#endif /* ClientConnection_hpp */
