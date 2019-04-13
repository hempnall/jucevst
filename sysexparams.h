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

#define PP_COMMON_COMMON 0x3600
#define PP_COMMON_REVERB 0x3601
#define PP_COMMON_CHORUS 0x3602
#define PP_COMMON_INSERTION_A 0x3603
#define PP_COMMON_INSERTION_B 0x3604
#define PP_COMMON_MASTER_EQ 0x3610
#define PP_COMMON_MASTER_EFFECT 0x3611
#define PP_COMMON_ARPEGGIO 0x3630
#define PP_PART 0x37
#define PP_ARPEGGIO 0x38
#define PP_AUDIO_DATA 0x3940

struct sysex_param {
    uint8 offset;
    String name;
    uint8 size;
    int16 range_hi; 
    int16 range_lo;
};

typedef std::vector<sysex_param> sysex_page_schema_t;
typedef std::map< uint8 , sysex_page_schema_t> sysex_schema_t;

void dumpParameterPage( uint16 page , midibyte_t* data );
void dumpParameterPageWithChannel( uint8 page , std::function<midibyte_t*(uint8)> data );

const sysex_param& get_sysex_param( uint8 hi , uint8 mid );

template < typename DATA >
std::string header_fn(DATA hi, DATA mid, DATA lo, juce::String param , uint8 count , std::function<uint16(uint8)> data_fn)
{
    std::ostringstream ostr;
    constexpr uint8 INTWIDTH=7;
    constexpr uint8 TITLEWIDTH=40;
    ostr << std::setw(INTWIDTH) << std::hex << hi;
    ostr << std::setw(INTWIDTH) << mid;
    ostr << std::setw(INTWIDTH) << lo << std::dec ;
    ostr << std::setw(TITLEWIDTH) << param;
    for (int i=0 ; i < count ; ++i) {
        ostr << std::setw(INTWIDTH) << data_fn(i);
    }
    return ostr.str();
};

#endif /* sysexparams_h */
