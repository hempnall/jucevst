//
//  MOXFSongState.hpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 10/03/2019.
//

#ifndef MOXFSongState_hpp
#define MOXFSongState_hpp

#include <stdio.h>
#include <cstring>
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
#define MODEL_ID_EDITOR 0x01
#define MIN_SYSEX_SIZE 9
#define PARAM_HEADER_SIZE 5
#define BULK_HEADER_SIZE 7
#define MIDIMESSAGESENDDELAY 200

struct MOXFParametersBase
{
    virtual void writeToArray( const MidiSysExInfoWrite& update ) = 0;
    virtual void compareArray( const MidiSysExInfoWrite& update ) = 0;
};

struct MOXFParametersDummy : public MOXFParametersBase
{
    virtual void writeToArray( const MidiSysExInfoWrite& update ) {};
    virtual void compareArray( const MidiSysExInfoWrite& update ) {};
};

template< midibyte_t ID_HI, uint8 SIZE ,midibyte_t MIDID = 0 >
struct MOXFParameters
: public MOXFParametersBase
{
    const midibyte_t HI = ID_HI;
    const midibyte_t MAXSIZE = SIZE;
    bool isMuted_ = false;
    midibyte_t MID = MIDID;
    midibyte_t LO;
    midibyte_t data[SIZE] = {0 , ID_HI , MIDID, 0 };
    
    virtual void writeToArray( const MidiSysExInfoWrite& update)
    {
        if ( ( update.destindex + update.size ) > MAXSIZE ) return;
        std::memcpy( data + update.destindex , update.sourcedata , update.size   );
    }
    
    virtual void compareArray( const MidiSysExInfoWrite& update )
    {
        if ( ( update.destindex + update.size ) > MAXSIZE ) {
            Logger::writeToLog("reflected bulk dump is larger than structure");
        }
        
        if ( update.size < 2 ) return;
        
        midibyte_t* start_of_stored_data = data + update.destindex + 1;
        midibyte_t* start_of_incoming_data = update.sourcedata + 1;
        
        int diff = std::memcmp( start_of_stored_data , start_of_incoming_data  , update.size - 1 );
        
        if ( diff == 0 ) {
            Logger::writeToLog("reflected bulk dump is OK!!!!!!");
        } else {
            Logger::writeToLog("reflected bulk dump differs from original");
        }
    }

    midibyte_t calcChecksum(midibyte_t* start , midibyte_t* end)
    {
        // The Check sum is the value that results in a value of 0 for the lower 7 bits
        // when the Model ID, Start Address, Data and Check sum itself are added
        midibyte_t total = 0;
        for (midibyte_t* it = start  ; it !=  end; ++it) {
            total += *it;
            total &= 0x7f;
        }
        return ( 0x80 - total ) % 0x80;

    }
    
    void sendToSysEx( MidiOutput* output , midichannel_t chn = 0 )
    {
        if ( isMuted_ ) return;
        
        midibyte_t message[ 7 + SIZE ];
        message[0] =  YAMAHA;
        message[1] =  0x00; // bulk message
        message[2] =  MOXF_HI;
        message[3] =  MOXF_LO;
        message[4] =  0x00;
        message[5] =  MAXSIZE;
        std::memcpy( message + 6 , data , SIZE );
        
        if ( ID_HI == BULK_PART || ID_HI == BULK_PART_ARPEGGIO ) {
            message[8] = chn;
        }

        message[ 6 + SIZE ] = calcChecksum( message + 6 , message + SIZE + 6 );
        
        MidiMessage m = MidiMessage::createSysExMessage(message, SIZE + 7);
        Logger::writeToLog( String::toHexString( m.getRawData() , m.getRawDataSize() ) );
        output->sendMessageNow( m );

    }
    
    void setMuted( bool isMuted )
    {
        isMuted_ = isMuted;
    }
    
 

};

template< typename T >
MemoryOutputStream& operator<<( MemoryOutputStream& ostrm, const T& item )
{
    Logger::writeToLog(String::formatted("[<<] sha256[%d bytes]: %s", item.MAXSIZE , SHA256( item.data , item.MAXSIZE  ).toHexString().getCharPointer() ));
    ostrm.write( item.data ,item.MAXSIZE );
    return ostrm;
}

template< typename T >
MemoryInputStream& operator>>( MemoryInputStream& istrm,  T& item )
{
    istrm.read( item.data , item.MAXSIZE );
    Logger::writeToLog(String::formatted("[>>] sha256[%d bytes]: %s", item.MAXSIZE , SHA256( item.data , item.MAXSIZE  ).toHexString().getCharPointer() ));
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
    bool is_initialised_ = false;
    MOXFCommon common_;
    MOXFPart parts_[16];
    midibyte_t audiopart_[8];
    
    void applyBulkCommon( const MidiSysExInfoWrite& update );
    void compareBulkCommon( const MidiSysExInfoWrite& update );
    void applySysex( const MidiSysExInfoWrite& update );
    void compareSysex( const MidiSysExInfoWrite& update );
    void dumpState();
    bool isInitialised();
    void initialise();
    
    MOXFParametersBase& getSysex( const MidiSysExInfoWrite& update );
    MOXFParametersBase& getBulkCommon( const MidiSysExInfoWrite& update );
};

MemoryOutputStream& operator << ( MemoryOutputStream& , const MOXFSongState& state);
MemoryInputStream& operator >> ( MemoryInputStream& istrm , MOXFSongState& state );


#endif /* MOXFSongState_hpp */
