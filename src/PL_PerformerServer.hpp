//
//  PL_PerformerServer.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/25/17.
//
//

#ifndef PL_PerformerServer_hpp
#define PL_PerformerServer_hpp

#include "ofMain.h"
#include "ofxOsc.h"

class PL_PerformerServer {
public:
    static PL_PerformerServer &instance();
    static void setup(string serverAddr, int serverPort);
    static void sendMessage(ofxOscMessage m);
    
    static void tick();
    static void setMsgTimerLock(float _msgTimerLock);
    
    static bool sendVibeMessage(string clientName, int performerIndex, int motorNumber, float delay, float atk, float sus, float rel);
    static bool sendAuditoryMessage(string clientName, int performerIndex, string auditoryMessage, vector<int> &msgInts);
    
    static void setVibeLockoutTimer(float _lockoutTimer);
    static void setAuditoryLockoutTimer(float _lockoutTimer);

    static int numInstructionsForAuditory;
private:
    PL_PerformerServer() {};
    PL_PerformerServer(PL_PerformerServer const&) {};
    PL_PerformerServer& operator=(PL_PerformerServer const&) {return *this;}
    ~PL_PerformerServer() {};
    
    ofxOscSender sender;
    
    float msgTimerA, msgTimerB;
    float msgTimerLock;
    bool  canSendMsgA, canSendMsgB;
    
    float auditoryMsgTimerA, auditoryMsgTimerB;
    float auditoryMsgTimerLock;
    bool  canSendAuditoryMsgA, canSendAuditoryMsgB;
    
};

#endif /* PL_PerformerServer_hpp */
