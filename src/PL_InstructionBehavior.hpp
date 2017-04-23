//
//  PL_InstructionBehavior.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#ifndef PL_InstructionBehavior_hpp
#define PL_InstructionBehavior_hpp

#include "ofMain.h"
#include "PL_InstructionBehaviorType.h"
#include "PL_GoalManager.hpp"
#include "ofxLibwebsockets.h"
#include "ofxOsc.h"
#include "pl_console.hpp"

class PL_InstructionBehavior {
public:
    virtual void update();
    virtual float getNextInstruction()=0;
    virtual void tick();
    
    void sortObjectsGoals(vector<ofVec2f> tempObjects);
    
    void sendAddInstr(ofVec2f _goalPosition, float _duration=4.0f, float _delay=0.0f);
    void sendRemoveInstr(ofVec2f _goalPosition, float _duration=4.0f, float _delay=0.0f);
    void sendMoveInstr(ofVec2f _startPosition, ofVec2f _endPosition, float _duration=4.0f, float _delay=0.0f);
    
    
    const PL_InstructionBehaviorType &getType() {return myType;}
    PL_InstructionBehaviorType &getFollowType() {return followType;}
    
    bool &checkIsFinished() {return isFinished;}
    PL_InstructionBehavior(float _timeTillFirstInstruction, PL_InstructionBehaviorType _myType, shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects);
protected:
    const PL_InstructionBehaviorType myType;
    PL_InstructionBehaviorType followType;
    
    float timer;
    float timeTillNextInstruction;
    bool nextInstructionNow;
    
    bool isFinished;
    const int &myId;
    string &userName;
    
    ofxLibwebsockets::Connection &connection;

    shared_ptr<PL_GoalManager> gm;
    vector<ofVec2f> &objects;

};

#endif /* PL_InstructionBehavior_hpp */
