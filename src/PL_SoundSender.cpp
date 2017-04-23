//
//  PL_SoundSender.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/10/17.
//
//

#include "PL_SoundSender.hpp"

PL_SoundSender &PL_SoundSender::instance() {
    static PL_SoundSender s;
    return s;
}

void PL_SoundSender::setup(string serverAddr, int serverPort) {instance().sender.setup(serverAddr, serverPort);}
void PL_SoundSender::sendMessage(ofxOscMessage m) {instance().sender.sendMessage(m);}

void PL_SoundSender::tick() {
    if(instance().events.size()) {
        for(int i=instance().events.size()-1; i>=0; i--) {
            instance().events[i].delay -= ofGetLastFrameTime();
            if(instance().events[i].delay <= 0.0f) {
                ofxOscMessage m;
                switch (instance().events[i].myType) {
                    case ADD:
                        m.setAddress("/instruction/add");
                        break;
                        
                    case MOVE:
                        m.setAddress("/instruction/move");
                        break;
                        
                    case REMOVE:
                        m.setAddress("/instruction/remove");
                        break;
                        
                    default:
                        cout << "[error]" << endl;
                        break;
                }
                
                m.addIntArg(instance().events[i].clientId);
                if(instance().events[i].myType==MOVE) {
                    m.addFloatArg(instance().events[i].startPosition.x);
                    m.addFloatArg(instance().events[i].startPosition.y);
                }
                m.addFloatArg(instance().events[i].targetPosition.x);
                m.addFloatArg(instance().events[i].targetPosition.y);
                m.addFloatArg(instance().events[i].duration);
                
                instance().sender.sendMessage(m);
                instance().events.erase(instance().events.begin()+i);
            }
        }
    }
}

void PL_SoundSender::addInstructionEvent(PL_SoundSender::InstructionType _myType, ofVec2f _targetPosition, float _delay, float _duration, int _id) {
    soundInstructionEvent i;
    i.myType=_myType;
    i.targetPosition=_targetPosition;
    i.delay=_delay;
    i.duration=_duration;
    i.clientId=_id;
    instance().events.push_back(i);
}

void PL_SoundSender::addInstructionEvent(PL_SoundSender::InstructionType _myType, ofVec2f _startPosition, ofVec2f _targetPosition, float _delay, float _duration, int _id) {
    soundInstructionEvent i;
    i.myType=_myType;
    i.startPosition=_startPosition;
    i.targetPosition=_targetPosition;
    i.delay=_delay;
    i.duration=_duration;
    i.clientId=_id;
    instance().events.push_back(i);
}
