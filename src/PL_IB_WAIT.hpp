//
//  PL_IB_WAIT.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/10/17.
//
//

#ifndef PL_IB_WAIT_hpp
#define PL_IB_WAIT_hpp

#include "ofMain.h"
#include "PL_InstructionBehavior.hpp"

class PL_IB_WAIT : public PL_InstructionBehavior {
public:
    virtual float getNextInstruction();
    virtual void update();
    PL_IB_WAIT(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects, ofVec2f &_ClientScreenDimensions);
private:
    
};

#endif /* PL_IB_WAIT_hpp */
