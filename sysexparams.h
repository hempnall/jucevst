//
//  sysexparams.h
//  MOXFVst3SongMode
//
//  Created by James on 11/03/2019.
//

#ifndef sysexparams_h
#define sysexparams_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "MOXFTypes.h"
#include <vector>
#include <map>

struct sysex_param {
    uint8 offset;
    String name;
    uint8 size;
    int16 range_hi; 
    int16 range_lo;
};

typedef std::vector<sysex_param> sysex_page_schema_t;
typedef std::map< uint8 , sysex_page_schema_t> sysex_schema_t;


void dumpParameterPage( uint8 page , std::function<midibyte_t*(uint8)> data );

const sysex_param& get_sysex_param( uint8 hi , uint8 mid );

template < typename DATA >
std::string header_fn(DATA hi, DATA mid, DATA lo, juce::String param , std::function<uint16(uint8)> data_fn)
{
    std::ostringstream ostr;
    constexpr uint8 INTWIDTH=7;
    constexpr uint8 TITLEWIDTH=24;
    ostr << std::setw(INTWIDTH) << hi;
    ostr << std::setw(INTWIDTH) << mid;
    ostr << std::setw(INTWIDTH) << lo;
    ostr << std::setw(TITLEWIDTH) << param;
    for (int i=0 ; i < 16 ; ++i) {
        ostr << std::setw(INTWIDTH) << data_fn(i);
    }
    return ostr.str();
};

#endif /* sysexparams_h */
