//
//  MidiInfoWrite.hpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 24/03/2019.
//

#ifndef MidiInfoWrite_hpp
#define MidiInfoWrite_hpp

#include "../JuceLibraryCode/JuceHeader.h"

struct MidiInfoWrite
{
    midibyte_t datatype;
    midibyte_t channel;
    midibyte_t *sourcedata;
    uint8 destindex;
    uint8 size;
};


#endif /* MidiInfoWrite_hpp */
