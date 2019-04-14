//
//  MOXFSongState.hpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 10/03/2019.
//

#ifndef MOXFSongState_hpp
#define MOXFSongState_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MOXFTypes.h"

#define BULK_COMMON 0x36
#define COMMON_COMMON 0x00
#define COMMON_REVERB 0x01
#define COMMON_CHORUS 0x02
#define COMMON_INSERTION_A 0x03
#define COMMON_INSERTION_B 0x04
#define COMMON_MASTER_EQ 0x10
#define COMMON_MASTER_EFFECT 0x11
#define COMMON_ARPEGGION 0x30
#define BULK_PART 0x37
#define BULK_PART_ARPEGGIO 0x38
#define PARAMETER_PART 0x37
#define PARAMETER_PART_ARPEGGIO 0x38
#define BULK_AUDIO 0x39
#define BULK_AUDIO_MID 0x40
#define PARTSIZE  0x42
#define ARPSIZE  0x4c
#define BULKAUDIOSIZE  0x0c
#define INSERTIONSIZE  37
#define COMMONSIZE  81
#define REVERBSIZE  39
#define CHORUSSIZE  41
#define MASTEREQSIZE  0x17
#define MASTEREFFECTSIZE  0x2A
#define ARPCOMMONSIZE  0x12
#define YAMAHA 0x43
#define MOXF_HI 0x7f
#define MOXF_LO 0x1c
#define MODEL_ID 0x00
#define MIN_SYSEX_SIZE 9
#define PARAM_HEADER_SIZE 5
#define BULK_HEADER_SIZE 7

template< midibyte_t ID_HI, uint8 SIZE ,midibyte_t MIDID = 0 >
struct MOXFParameters
{
    const midibyte_t HI = ID_HI;
    const midibyte_t MAXSIZE = SIZE;
    midibyte_t MID = MIDID;
    midibyte_t LO;
    midibyte_t data[SIZE] = {0 , ID_HI , MIDID, 0 };
    
    void writeToArray( const MidiSysExInfoWrite& update)
    {
        if ( ( update.destindex + update.size ) > MAXSIZE ) return;
        std::memcpy( data + update.destindex , update.sourcedata , update.size   );
    }

    midibyte_t calcChecksum()
    {
        midibyte_t total = 0;
        for (int i=0 ; i < MAXSIZE ; ++i) {
            total += data[i];
            total &= 0x7f;
        }
        midibyte_t chksum =  ( 0x80 - total ) & 0x7f;
        return chksum ;
    }
    
    void sendToSysEx( MidiOutput* output , midichannel_t chn = 0 )
    {
        midibyte_t message[ 7 + SIZE ];
        message[0] =  YAMAHA;
        message[1] =  0x00; // bulk message
        message[2] =  MOXF_HI;
        message[3] =  MOXF_LO;
        message[4] =  0x00;
        message[5] =  MAXSIZE;
        std::memcpy( message + 6 , data , SIZE );
        message[ 6 + SIZE ] = calcChecksum();
        
        if ( ID_HI == BULK_PART || ID_HI == BULK_PART_ARPEGGIO ) {
            message[8] = chn;
        }
        
        MidiMessage m = MidiMessage::createSysExMessage(message, SIZE + 7);
        Logger::writeToLog( String::toHexString( m.getRawData() , m.getRawDataSize() ) );
        output->sendMessageNow( m );
        Time::waitForMillisecondCounter(100);
    }

};

template< typename T >
MemoryOutputStream& operator<<( MemoryOutputStream& ostrm, const T& item )
{
    ostrm.write( item.data ,item.MAXSIZE );
    return ostrm;
}

template< typename T >
MemoryInputStream& operator>>( MemoryInputStream& istrm,  T& item )
{
    istrm.read( item.data , item.MAXSIZE );
    return istrm;
}

struct MOXFCommon
{
    MOXFParameters<BULK_COMMON, 0x54 , COMMON_COMMON> common;
    MOXFParameters<BULK_COMMON, 0x2a , COMMON_REVERB> reverb;
    MOXFParameters<BULK_COMMON, 0x2c , COMMON_CHORUS> chorus;
    MOXFParameters<BULK_COMMON, 0x28 , COMMON_INSERTION_A> insertion_a;
    MOXFParameters<BULK_COMMON, 0x28 , COMMON_INSERTION_B> insertion_b;
    MOXFParameters<BULK_COMMON, 0x18 , COMMON_MASTER_EQ> master_eq;
    MOXFParameters<BULK_COMMON, 0x2a , COMMON_MASTER_EQ> master_effect;
    MOXFParameters<BULK_COMMON, 0x12 , COMMON_ARPEGGION> appregio;
    MOXFParameters<BULK_AUDIO,  0x0c , BULK_AUDIO_MID> audio;
};

struct MOXFPart
{
    MOXFParameters<BULK_PART, 0x42 > partdata;
    MOXFParameters<BULK_PART_ARPEGGIO , 0x4c > arpdata;
};



struct MOXFSongState
{

    
    MOXFCommon common_;
    MOXFPart parts_[16];
    midibyte_t audiopart_[8];
    

    void applyBulkCommon( const MidiSysExInfoWrite& update );
    void applySysex( const MidiSysExInfoWrite& update );
    void dumpState();

};

MemoryOutputStream& operator << ( MemoryOutputStream& , const MOXFSongState& state);
MemoryInputStream& operator >> ( MemoryInputStream& istrm , MOXFSongState& state );


#endif /* MOXFSongState_hpp */
