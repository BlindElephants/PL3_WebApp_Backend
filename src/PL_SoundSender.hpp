//
//  PL_SoundSender.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/10/17.
//
//

#ifndef PL_SoundSender_hpp
#define PL_SoundSender_hpp

#include "ofMain.h"
#include "ofxOsc.h"

class PL_SoundSender {
public:
    static PL_SoundSender &instance();
    static void setup(string serverAddr, int serverPort);
    static void sendMessage(ofxOscMessage m);
    
    enum InstructionType {
        ADD,
        MOVE,
        REMOVE
    };
    
    static void addInstructionEvent(InstructionType _myType, ofVec2f _targetPosition, float _delay, float _duration, int _id);
    static void addInstructionEvent(InstructionType _myType, ofVec2f _startPosition, ofVec2f _targetPosition, float _delay, float _duration, int _id);
    static void tick();
    
    
    struct soundInstructionEvent {
        InstructionType myType;
        ofVec2f targetPosition;
        ofVec2f startPosition;
        float delay;
        float duration;
        int clientId;
    };
    
private:
    PL_SoundSender() {};
    PL_SoundSender(PL_SoundSender const&) {};
    PL_SoundSender& operator=(PL_SoundSender const&) {return *this;}
    ~PL_SoundSender() {};
    
    ofxOscSender sender;
    
    vector<soundInstructionEvent> events;
};

#endif /* PL_SoundSender_hpp */
