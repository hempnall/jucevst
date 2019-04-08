//
//  MOXFTypes.h
//  MOXFVst3SongMode
//
//  Created by James on 24/03/2019.
//

#ifndef MOXFTypes_h
#define MOXFTypes_h

typedef juce::uint8 midibyte_t;
typedef juce::uint8 midichannel_t;
typedef juce::uint8 parameterpage_t;

struct MidiSysExInfoWrite
{
    parameterpage_t datatype;
    union {
        midichannel_t channel;
        midibyte_t subtype;
    };
    midibyte_t *sourcedata;
    uint8 destindex;
    uint8 size;
};

#endif /* MOXFTypes_h */
