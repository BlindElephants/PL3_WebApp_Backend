//
//  PL_VisServer.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/26/17.
//
//

#ifndef PL_VisServer_hpp
#define PL_VisServer_hpp

#include "ofMain.h"
#include "ofxOsc.h"

class PL_VisServer {
public:
    static PL_VisServer &instance();
    static void setup(string serverAddr, int serverPort);
    static void sendMessage(ofxOscMessage m);
    
    
private:
    PL_VisServer() {};
    PL_VisServer(PL_VisServer const&) {};
    PL_VisServer& operator=(PL_VisServer const&) {return *this;}
    ~PL_VisServer() {};
    ofxOscSender sender;
};

#endif /* PL_VisServer_hpp */
