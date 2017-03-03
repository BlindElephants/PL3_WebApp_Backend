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

class ClientConnection {
public:
    void addObject(ofVec2f _position);
    void moveObject(int _index, ofVec2f _newPosition);
    void moveObject(ofVec2f _oldPosition, ofVec2f _newPosition);
    void removeObject(int _index);
    void removeObject(ofVec2f _position);
    void clearObjects();
    void makeNewGoal();
    void setClientScreenDimensions(float w, float h);
    void tick();
    ClientConnection(ofxLibwebsockets::Connection& _connection);
private:
    
    void normalizeCoords(ofVec2f &position);
    void convertToScreenCoords(ofVec2f &position);
    
    ofxLibwebsockets::Connection& connection;
    float age;
    vector < ofVec2f > objects;
    float timeSinceLastPing;
    
    ofVec2f ClientScreenDimensions;
    
    vector < ofVec2f > goal;
    
};

#endif /* ClientConnection_hpp */
