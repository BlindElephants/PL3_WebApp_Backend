//
//  PL_InstructionManager.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#ifndef PL_InstructionManager_hpp
#define PL_InstructionManager_hpp

#include "ofMain.h"
#include "ofxLibwebsockets.h"
#include "ofxOsc.h"

#include "PL_IB_WAIT.hpp"
#include "PL_IB_A.hpp"
#include "PL_IB_B.hpp"
#include "PL_IB_C.hpp"
#include "PL_IB_D.hpp"
#include "PL_IB_E.hpp"

#include "PL_InstructionBehavior.hpp"

#include "PL_GoalManager.hpp"

#include "pl_console.hpp"

class PL_InstructionManager {
public:
    void update();
    
    PL_InstructionManager(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects);
private:
    ofxLibwebsockets::Connection &connection;
    const int &myId;
    string &userName;
    shared_ptr<PL_InstructionBehavior> ib;
    shared_ptr<PL_GoalManager> gm;
    vector<ofVec2f> &objects;
};

#endif /* PL_InstructionManager_hpp */
