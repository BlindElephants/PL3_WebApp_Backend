//
//  PL_BehaviorTypeGen.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#ifndef PL_BehaviorTypeGen_hpp
#define PL_BehaviorTypeGen_hpp

#include "ofMain.h"
#include "PL_InstructionBehaviorType.h"


class FollowGen {
public:
    static FollowGen &instance();
    static PL_InstructionBehaviorType getFollowType(const PL_InstructionBehaviorType &myType);
    static void setup();
    
private:
    FollowGen() {};
    FollowGen(FollowGen const&) {};
    FollowGen& operator=(FollowGen const&) {return *this;}
    ~FollowGen() {};
    
    float ** followProbabilities;
};
#endif /* PL_BehaviorTypeGen_hpp */
