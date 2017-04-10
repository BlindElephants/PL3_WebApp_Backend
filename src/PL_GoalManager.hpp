//
//  PL_GoalManager.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#ifndef PL_GoalManager_hpp
#define PL_GoalManager_hpp

#include "ofMain.h"
#include "PL_Goal.hpp"

class PL_GoalManager {
    static const int maxNumberOfGoals;
public:
    void makeNewGoalSet_Random(int numberGoals);
    ofVec2f &getDeviceScreenDimensions() {return deviceScreenDimensions;}
    float &getDeviceObjectSize() {return deviceObjectSize;}
    vector<shared_ptr<PL_Goal>> & getGoals() {return goals;}
    vector<shared_ptr<PL_Goal>> & getCompletedGoals() {return completedGoals;}
    PL_GoalManager(ofVec2f &_deviceScreenDimensions, float &_deviceObjectSize) : deviceScreenDimensions(_deviceScreenDimensions), deviceObjectSize(_deviceObjectSize) {};
private:
    bool checkForCollisions(ofVec2f &p);
    ofVec2f &deviceScreenDimensions;
    float &deviceObjectSize;
    vector<shared_ptr<PL_Goal>> goals;
    vector<shared_ptr<PL_Goal>> completedGoals;
};

#endif /* PL_GoalManager_hpp */
