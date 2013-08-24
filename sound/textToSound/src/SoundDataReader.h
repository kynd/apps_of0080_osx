

#ifndef __textToSound__SoundDataReader__
#define __textToSound__SoundDataReader__

#include "ofMain.h"
class SoundDataReader {
    
public:
    void open(string str);
    bool next();
    bool nextMS(float ms);
    
    ofBuffer buffer;
    vector<float> data;
    
};

#endif /* defined(__textToSound__SoundDataReader__) */
