//
//  MOXFSongState.cpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 10/03/2019.
//

#include "MOXFSongState.hpp"
#include "sysexparams.h"
#include <cstring>
#include <strstream>
#include <iomanip>


void writeToArray( const MidiSysExInfoWrite& update, midibyte_t* start , uint8 max_size)
{
    if ( ( update.destindex + update.size ) > max_size ) return;
    std::memcpy( start + update.destindex , update.sourcedata , update.size   );
}



void MOXFSongState::applySysex( const MidiSysExInfoWrite& update )
{
    switch (update.datatype)
    {
        case BULK_COMMON:
            applyBulkCommon(update);
            break;
        case BULK_PART:
            parts_[update.channel].partdata.writeToArray( update );
            break;
        case BULK_PART_ARPEGGIO:
            parts_[update.channel].arpdata.writeToArray( update);
            break;
        case BULK_AUDIO:
            common_.audio.writeToArray( update);
            break;
        default:
            Logger::writeToLog(String::formatted("[default] datatype=%02x destindex=%02x channel=%02x maxsize=%02x size=%d", update.datatype, update.destindex, update.channel , 0, update.size  ));
            break;
    }
}


void MOXFSongState::applyBulkCommon(const MidiSysExInfoWrite& update)
{
    switch ( update.subtype ) {
        case COMMON_COMMON:
            common_.common.writeToArray(update);
            break;
        case COMMON_CHORUS:
            common_.chorus.writeToArray(update);
            break;
        case COMMON_REVERB:
            common_.reverb.writeToArray(update );
            break;
        case COMMON_ARPEGGION:
            common_.appregio.writeToArray(update );
            break;
        case COMMON_MASTER_EQ:
            common_.master_eq.writeToArray( update  );
            break;
        case COMMON_INSERTION_A:
            common_.insertion_a.writeToArray( update  );
            break;
        case COMMON_INSERTION_B:
            common_.insertion_b.writeToArray( update  );
            break;
        case COMMON_MASTER_EFFECT:
            common_.master_effect.writeToArray( update );
        default:
            break;
    }
}



void MOXFSongState::dumpState()
{
    juce::String header = header_fn( "hi" , "mid" , "lo" , "Parameter", [](uint8 n) {return n;} );
    Logger::writeToLog( header  );
    dumpParameterPage( 37 , [&] (uint8 n ) { return parts_[n].partdata.data; } );
}

MemoryOutputStream& operator << ( MemoryOutputStream& ostrm, const MOXFSongState& state)
{
    ostrm << state.common_.common;
    ostrm << state.common_.chorus ;
    ostrm << state.common_.reverb;
    ostrm << state.common_.appregio ;
    ostrm << state.common_.master_eq ;
    ostrm << state.common_.insertion_a ;
    ostrm << state.common_.insertion_b ;
    ostrm << state.common_.master_eq ;
    for (int i=0; i< 16 ; ++i) {
        ostrm <<  state.parts_[i].partdata;
        ostrm <<  state.parts_[i].arpdata;
    }
    ostrm << state.common_.audio;

    return ostrm;
}


MemoryInputStream& operator >> (  MemoryInputStream& istrm , MOXFSongState& state )
{
    istrm >> state.common_.common ;
    istrm >>  state.common_.chorus ;
    istrm >>  state.common_.reverb ;
    istrm >>  state.common_.appregio ;
    istrm >>  state.common_.master_eq ;
    istrm >>  state.common_.insertion_a ;
    istrm >>  state.common_.insertion_b ;
    istrm >>  state.common_.master_eq ;
    for (int i=0; i< 16 ; ++i) {
        istrm >>  state.parts_[i].partdata;
        istrm >>  state.parts_[i].arpdata;
    }
    istrm >> state.common_.audio;
    return istrm;
}
