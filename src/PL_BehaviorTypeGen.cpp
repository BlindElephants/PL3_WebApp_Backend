//
//  PL_BehaviorTypeGen.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#include "PL_BehaviorTypeGen.hpp"

FollowGen &FollowGen::instance() {
    static FollowGen f;
    return f;
}

void FollowGen::setup() {
    float tempProbs[(int)NUM_BEHAVIORTYPES][(int)NUM_BEHAVIORTYPES] = {
        {   0.0,    1.0,    1.0,    1.0,    1.0,    1.0     },
        {   0.0,    0.0,    1.0,    1.0,    1.0,    1.0     },
        {   0.0,    1.0,    1.0,    1.0,    1.0,    1.0     },
        {   0.0,    1.0,    1.0,    1.0,    1.0,    1.0     },
        {   0.0,    1.0,    1.0,    1.0,    1.0,    1.0     },
        {   0.0,    1.0,    1.0,    1.0,    1.0,    1.0     }
    };
    
    
    instance().followProbabilities = new float*[(int)NUM_BEHAVIORTYPES];
    for(int i=0; i<(int)NUM_BEHAVIORTYPES; i++) {
        instance().followProbabilities[i]=new float[(int)NUM_BEHAVIORTYPES];
    }
    
    for(int x=0; x<(int)NUM_BEHAVIORTYPES; x++) {
        for(int y=0; y<(int)NUM_BEHAVIORTYPES; y++) {
            instance().followProbabilities[x][y]=tempProbs[x][y];
        }
    }
}

PL_InstructionBehaviorType FollowGen::getFollowType(const PL_InstructionBehaviorType &myType) {
    float probTotal=0.0f;
    for(int i=0;i<(int)NUM_BEHAVIORTYPES;i++) {
        probTotal+=instance().followProbabilities[myType][i];
    }
    float thisPick=ofRandom(probTotal);
    float runningMax=0.0;
    for(int i=0; i<(int)NUM_BEHAVIORTYPES; i++ ){
        runningMax+=instance().followProbabilities[myType][i];
        if(thisPick<runningMax) return (PL_InstructionBehaviorType)i;
    }
}
