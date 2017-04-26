//
//  PL_AuditoryMessageBuilder.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/25/17.
//
//

#ifndef PL_AuditoryMessageBuilder_hpp
#define PL_AuditoryMessageBuilder_hpp

#include "ofMain.h"
#include "ofxOscMessage.h"

class PL_AuditoryMessageBuilder {
public:
    static PL_AuditoryMessageBuilder &instance();
    static void init();
    static void tick();
    static string getAuditoryMessage(vector<int> &msgInts);
    
private:
    PL_AuditoryMessageBuilder() {};
    PL_AuditoryMessageBuilder(PL_AuditoryMessageBuilder const&) {};
    PL_AuditoryMessageBuilder& operator=(PL_AuditoryMessageBuilder const&) {return *this;}
    ~PL_AuditoryMessageBuilder() {};
    
    vector<string> repeatInstr;
    vector<string> pairsInstr;
    vector<string> simpleInstr;
    vector<string> descriptors;
    vector<string> directives;
    vector<string> values;
    
    
    vector<int> repeatInstrNum;
    vector<int> pairsInstrNum;
    vector<int> simpleInstrNum;
    vector<int> descriptorsNum;
    vector<int> directivesNum;
    vector<int> valuesNum;
    
    
    float timeElapsed;
    int numberAuditoryMessagesSent;
};

#endif /* PL_AuditoryMessageBuilder_hpp */
