//
//  PL_GoalManager.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#include "PL_GoalManager.hpp"
#include "ClientUtilities.hpp"
const int PL_GoalManager::maxNumberOfGoals=12;

void PL_GoalManager::makeNewGoalSet_Random(int numberGoals) {
    if(numberGoals>maxNumberOfGoals) numberGoals=maxNumberOfGoals;
    goals.clear();
    completedGoals.clear();
    cout << deviceScreenDimensions << endl;

    for(int i=0; i<numberGoals; i++ ) {
        ofVec2f p;
        p = ofVec2f(ofRandom(deviceScreenDimensions.x), ofRandom(deviceScreenDimensions.y));
        p=ClientUtilities::offsetForScreen(p, deviceScreenDimensions);
//        do {
//            p = ofVec2f(ofRandom(deviceScreenDimensions.x), ofRandom(deviceScreenDimensions.y));
//        } while(checkForCollisions(p));
        shared_ptr<PL_Goal> g = make_shared<PL_Goal>(p);
        goals.push_back(g);
    }
}

bool PL_GoalManager::checkForCollisions(ofVec2f &p) {
    float d2=(deviceObjectSize*0.5);
    d2*=d2;
    if(goals.size()) {
        for(int i=0; i<goals.size(); i++ ) {
            if(goals[i]->getPosition().squareDistance(p) < d2) {
                return true;
            }
        }
    }
    return false;
}
