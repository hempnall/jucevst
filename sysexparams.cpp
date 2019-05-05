//
//  sysexparams.cpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 13/03/2019.
//

#include "sysexparams.h"
#include "moxf_structure_defs.h"



sysex_schema_t moxf_schema = {
    { PP_PART , param_data_37 },
    { PP_ARPEGGIO , param_data_38 },
    { PP_AUDIO_DATA , param_data_39_40 },
    { PP_COMMON_MASTER_EFFECT , param_data_36_11 },
    { PP_COMMON_MASTER_EQ , param_data_36_10 },
    { PP_COMMON_INSERTION_A , param_data_36_03 },
    { PP_COMMON_INSERTION_B , param_data_36_04 },
    { PP_COMMON_CHORUS , param_data_36_02 },
    { PP_COMMON_REVERB , param_data_36_01 },
    { PP_COMMON_COMMON , param_data_36_00 },
    { PP_COMMON_ARPEGGIO , param_data_36_30 },
};

uint16 convert_fn( midibyte_t* ptr , uint8 size )  {
    if (size == 1) {
        return *ptr;
    } else if ( size == 2 ) {
        return *ptr + ( ptr[1] << 8  );
    } else {
        return 0;
    }
};

void dumpParameterPage( uint16 page , midibyte_t* data  )
{
    auto schma = moxf_schema.find(page);
    if ( schma == moxf_schema.end() ) {
        Logger::writeToLog("invalid parameter page in dump paramaeter page");
        return;
    }
    
    for ( sysex_param p : schma->second ) {
        std::string out = header_fn( (uint16) ( page >> 8 ) ,(uint16) (page & 0x00ff) , (uint16)p.offset , p.name , 1 ,[&](uint8 n) -> uint16 { return convert_fn( data + p.offset + 4 , p.size ); }  );
        Logger::writeToLog( out);
    }
}


void dumpParameterPageWithChannel( uint8 page , std::function<midibyte_t*(uint8)> data )
{
    auto schma = moxf_schema.find(page);
    if ( schma == moxf_schema.end() ) {
        Logger::writeToLog("invalid parameter page in dump paramaeter page");
        return;
    }

    for ( sysex_param p : schma->second ) {
        std::string out = header_fn( (uint16) page ,(uint16) 0 , (uint16)p.offset , p.name , 16 ,[&](uint8 n) -> uint16 { return convert_fn( data(n) + p.offset + 4 , p.size ); } );
        Logger::writeToLog( out);
    }

}

