//
//  PL_AuditoryMessageBuilder.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/25/17.
//
//

#define numberRepeatInstr 4
#define numberPairsInstr 4
#define numberSimpleInstr 7
#define numberDescriptors 6
#define numberDirectives 3
#define numberValues 10

#include "PL_AuditoryMessageBuilder.hpp"

#include <random>
#include <chrono>

PL_AuditoryMessageBuilder &PL_AuditoryMessageBuilder::instance() {
    static PL_AuditoryMessageBuilder m;
    return m;
}

void PL_AuditoryMessageBuilder::init() {
    instance().timeElapsed = 0.0f;
    instance().numberAuditoryMessagesSent=0;
    
    instance().repeatInstr={
        "repeat movement",
        "times"
        "seconds",
        "then"
    };
    
    instance().pairsInstr={
        "mimic other",
        "mirror other",
        "opposite of other",
        "follow other"
    };
    
    instance().simpleInstr={
        "stand",
        "step",
        "stop",
        "face other",
        "away from other",
        "face audience",
        "away from audience"
    };
    
    instance().descriptors={
        "curved",
        "horizontal",
        "linear",
        "minimal",
        "pedestrian",
        "vertical"
    };
    
    instance().directives={
        "height",
//        "range",
        "size",
        "speed"
    };
    
    instance().values={
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
        "ten"
    };
    
    instance().repeatInstrNum={
        26, //"repeat movement",
        34, //"times"
        27, //"seconds",
        33  //"then"
    };
    
    instance().pairsInstrNum={
        20, //"mimic other",
        22, //"mirror other",
        23, //"opposite of other",
        16 //"follow other"
    };
    
    instance().simpleInstrNum={
        30, //"stand",
        31, //"step",
        32, //"stop",
        15, //"face other",
        12, //"away from other",
        14, //"face audience",
        11 //"away from audience"
    };
    
    instance().descriptorsNum={
        13, //"curved",
        18, //"horizontal",
        19, //"linear",
        21, //"minimal",
        24, //"pedestrian",
        35  //"vertical"
    };
    
    instance().directivesNum={
        17, //"height",
//        25, //"range",
        28, //"size",
        29  //"speed"
    };
    
    instance().valuesNum={
        1, //"one",
        2, //"two",
        3, //"three",
        4, //"four",
        5, //"five",
        6, //"six",
        7, //"seven",
        8, //"eight",
        9, //"nine",
        10//"ten"
    };
}

void PL_AuditoryMessageBuilder::tick() {instance().timeElapsed+=ofGetLastFrameTime();}

string PL_AuditoryMessageBuilder::getAuditoryMessage(vector<int> &msgInts) {
    msgInts.clear();
    string m="";
    
    if (instance().timeElapsed<=240.0f) {
        int i=ofRandom(numberSimpleInstr);
        m+=instance().simpleInstr[i];
        msgInts.push_back(instance().simpleInstrNum[i]);
    } else {
        float p = ofRandom(7.5);
        
        if(p<2.5) {
        //choose from repeatInstr
            m+=instance().repeatInstr[0];
            msgInts.push_back(instance().repeatInstrNum[0]);
            m+= " ";
            int i=ofRandom(numberValues);
            m+=instance().values[i];
            msgInts.push_back(instance().valuesNum[i]);
            m+=" ";
            m+=instance().repeatInstr[2];
            msgInts.push_back(instance().repeatInstrNum[2]);
        } else if(p<3.5) {
        //choose from pairsInstr
            int i=ofRandom(numberPairsInstr);
            m+=instance().pairsInstr[i];
            msgInts.push_back(instance().pairsInstrNum[i]);
//        } else if(p<5.0) {
//        //choose from simpleInstr
//            m+=instance().simpleInstr[2];
//            msgInts.push_back(instance().simpleInstrNum[2]);
//            m+= " ";
//            int i=ofRandom(3, 7);
//            m+=instance().simpleInstr[i];
//            msgInts.push_back(instance().simpleInstrNum[i]);
        } else if(p<7.5) {
        //choose from descriptors
            float pa = ofRandom(1);
            if(pa <=1.0) {
                int i=ofRandom(numberDescriptors);
                m+=instance().descriptors[i];
                msgInts.push_back(instance().descriptorsNum[i]);
                int numDir = ofRandom(numberDirectives);
                vector<pair<string, int>> tempDir;
                
                
                for(int i=0; i<numberDirectives; i++ ){
                    pair<string, int> p;
                    p.first=instance().directives[i];
                    p.second=instance().directivesNum[i];
                    tempDir.push_back(p);
                }
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                shuffle(tempDir.begin(), tempDir.end(), std::default_random_engine(seed));
                for(int i=0; i<numDir;i++) {
                    m+= " ";
                    m+= tempDir[0].first;
                    msgInts.push_back(tempDir[0].second);
                    m+= " ";
                    int v = ofRandom(numberValues);
                    m+= instance().values[v];
                    msgInts.push_back(instance().valuesNum[v]);
                    
                    tempDir.erase(tempDir.begin());
                }
            } else {
                int numDir = ofRandom(numberDirectives);
                
                vector<pair<string, int>> tempDir;
                
//                vector<string>tempDir;
                for(int i=0; i<numberDirectives; i++ ){
                    pair<string, int> p;
                    p.first=instance().directives[i];
                    p.second=instance().directivesNum[i];
                    tempDir.push_back(p);
                }
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                shuffle(tempDir.begin(), tempDir.end(), std::default_random_engine(seed));
                for(int i=0; i<numDir;i++) {
                    m+= tempDir[0].first;
                    msgInts.push_back(tempDir[1].second);
                    m+= " ";
                    int v = ofRandom(numberValues);
                    m+= instance().values[v];
                    msgInts.push_back(instance().valuesNum[v]);
                    if(i<(numDir-1)) m+= " ";
                    tempDir.erase(tempDir.begin());
                }
            }
        }
        
        
    }
    
    m+=" range ";
    msgInts.push_back(25);
    int v=ofRandom(numberValues);
    m+=instance().values[v];
    msgInts.push_back(instance().valuesNum[v]);
    
    cout << m << endl;
    return m;
}
