//
//  PL_IB_C.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#ifndef PL_IB_C_hpp
#define PL_IB_C_hpp

#include "PL_InstructionBehavior.hpp"

class PL_IB_C : public PL_InstructionBehavior {
public:
    virtual float getNextInstruction();
    PL_IB_C(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects);
private:
    
};

#endif /* PL_IB_C_hpp */
