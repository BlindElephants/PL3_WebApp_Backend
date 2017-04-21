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

#include "PL_GoalManager.hpp"
#include "PL_InstructionManager.hpp"

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
    
    string &getUserName();
    
    void setClientUser(string _userName, float w, float h, float objectSize);
    void tick();

    int getId();
    
    ClientConnection(ofxLibwebsockets::Connection& _connection);
    
private:
    void normalizeCoords(ofVec2f &position);
    void convertToScreenCoords(ofVec2f &position);
    
    ofxLibwebsockets::Connection& connection;
    float age;
    vector <ofVec2f> objects;
    float timeSinceLastPing;
    
    string userName;
    ofVec2f ClientScreenDimensions;
    float   ClientObjectSize;
    
    shared_ptr<PL_GoalManager> gm;
    shared_ptr<PL_InstructionManager> im;
    
    const int myId;
};

#endif /* ClientConnection_hpp */
