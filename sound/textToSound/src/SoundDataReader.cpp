
#include "SoundDataReader.h"

void SoundDataReader::open(string str) {
    buffer = ofBufferFromFile(str);
}

bool SoundDataReader::next() {
    if (!buffer.isLastLine()) {
        string line = buffer.getNextLine();
        vector<string> sdata = ofSplitString(line, ",");
        data.clear();
        for (int i = 0; i < sdata.size(); i ++) {
            data.push_back(ofToFloat(sdata[i]));
        }
        return true;
    } else {
        return false;
    }
}
bool SoundDataReader::nextMS(float ms) {
    if (data.size() == 0) {
        next();
    }
    while (data[0] < ms) {
        if (buffer.isLastLine()) return false;
        next();
    }
}
