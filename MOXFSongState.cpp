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

MOXFParametersDummy dummy;

void MOXFSongState::applySysex( const MidiSysExInfoWrite& update )
{
    MOXFParametersBase& array = getSysex( update );
    array.writeToArray(update);
}

void MOXFSongState::compareSysex( const MidiSysExInfoWrite& update )
{
    MOXFParametersBase& array = getSysex( update );
    array.compareArray(update);
}

MOXFParametersBase& MOXFSongState::getSysex( const MidiSysExInfoWrite& update )
{
    switch (update.datatype)
    {
        case BULK_COMMON:
            return getBulkCommon(update);
            break;
        case BULK_PART:
            return parts_[update.channel].partdata;
            break;
        case BULK_PART_ARPEGGIO:
            return parts_[update.channel].arpdata;
            break;
        case BULK_AUDIO:
            return common_.audio;
            break;
        default:
            Logger::writeToLog(String::formatted("[default] datatype=%02x destindex=%02x channel=%02x maxsize=%02x size=%d", update.datatype, update.destindex, update.channel , 0, update.size  ));
            break;
    }
    return dummy;
}

MOXFParametersBase& MOXFSongState::getBulkCommon(const MidiSysExInfoWrite& update)
{
    switch ( update.subtype ) {
        case COMMON_COMMON:
            return common_.common;
            break;
        case COMMON_CHORUS:
            return common_.chorus;
            break;
        case COMMON_REVERB:
            return common_.reverb;
            break;
        case COMMON_ARPEGGION:
            return common_.appregio;
            break;
        case COMMON_MASTER_EQ:
            return common_.master_eq;
            break;
        case COMMON_INSERTION_A:
            return common_.insertion_a;
            break;
        case COMMON_INSERTION_B:
            return common_.insertion_b;
            break;
        case COMMON_MASTER_EFFECT:
            return common_.master_effect;
        default:
            return dummy;
            break;
    }
}

void MOXFSongState::initialise()
{
    is_initialised_ = true;
}

bool MOXFSongState::isInitialised()
{
    return is_initialised_;
}

void MOXFSongState::dumpState()
{
    juce::String header = header_fn( "hi" , "mid" , "lo" , "Parameter", 16, [](uint8 n) {return n;} );
    Logger::writeToLog( header  );
    
//    dumpParameterPage(  PP_COMMON_COMMON  , common_.common.data );
//    dumpParameterPage(  PP_COMMON_REVERB  , common_.reverb.data );
//    dumpParameterPage(  PP_COMMON_CHORUS  , common_.chorus.data );
//    dumpParameterPage(  PP_COMMON_INSERTION_A  , common_.insertion_a.data );
//    dumpParameterPage(  PP_COMMON_INSERTION_B  , common_.insertion_b.data );
//    dumpParameterPage(  PP_COMMON_MASTER_EQ  , common_.master_eq.data );
//    dumpParameterPage(  PP_COMMON_MASTER_EFFECT  , common_.master_effect.data );
//    dumpParameterPage(  PP_COMMON_ARPEGGIO  , common_.appregio.data );
    dumpParameterPageWithChannel( PARAMETER_PART , [&] (uint8 n ) { return parts_[n].partdata.data; } );
//    dumpParameterPageWithChannel( PARAMETER_PART_ARPEGGIO , [&] (uint8 n ) { return parts_[n].arpdata.data; } );
//    dumpParameterPage(PP_AUDIO_DATA, common_.audio.data);
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
    ostrm << state.common_.master_effect ;
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
    istrm >>  state.common_.master_effect ;
    for (int i=0; i< 16 ; ++i) {
        istrm >>  state.parts_[i].partdata;
        istrm >>  state.parts_[i].arpdata;
    }
    istrm >> state.common_.audio;
    return istrm;
}
