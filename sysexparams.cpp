//
//  sysexparams.cpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 13/03/2019.
//

#include "sysexparams.h"

sysex_page_schema_t param_data_37 = {
    { 0x0  , "reserved" ,1 ,0,0},
    { 0x01 , "Bank Select MSB" , 1 , 0 , 0x7f  },
    { 0x02 , "Bank Select LSB" , 1 , 0 , 0x7f  },
    { 0x03 , "Program Number" , 1 , 0 , 0x7f  },
    { 0x04 , "Receive Channel" ,1 , 0 , 0xf },
    { 0x05 , "Mono/Poly" , 1  , 0 , 1 },
    { 0x06 , "Velocity Limit Low" , 1 , 0, 127 },
    { 0x07 , "Velocity Limit High" , 1 , 0 , 127},
    { 0x08 , "Note Limit Low" , 1 , 0 , 127 },
    { 0x09 , "Note Limit High" , 1 , 0 ,0},
    { 0x0a , "Pitch Bend Range Upper" , 1 , 0 , 127 },
    { 0x0b , "Pitch Bend Range Lower" , 1 , 0 ,0},
    { 0x0c , "Vel Sens Depth" , 1 , 0 , 127 },
    { 0x0d , "Vel Sens Offset" , 1 , 0 ,0},
    { 0x0E , "Volume" , 1 , 0 , 0x7f},
    { 0x0F , "Pan" , 1 , 0 , 0x7f },
    { 0x10 , "Detune" , 2 , 0, 0 }

};

sysex_schema_t moxf_schema = {
    { 37 , param_data_37 }
};



void init_sysex_arrays()
{
//    params[ 37 ] = param_data_37;
//    sizes[ 37 ] = SIZEOFARRAY(param_data_37);
//    for (size_t n = 0 ; n < sizes[ 37 ] ; ++n ) {
//        auto index = param_data_37[n].offset;
//        params_37[ index ] = param_data_37[n];
//    }
}




void dumpParameterPage( uint8 page , std::function<midibyte_t*(uint8)> data )
{
    auto schma = moxf_schema.find(page);
    if ( schma == moxf_schema.end() ) {
        Logger::writeToLog("invalid parameter page in dump paramaeter page");
        return;
    }
    
    auto fn = []( midibyte_t* ptr , uint8 size ) -> uint16 {
        if (size == 1) {
            return *ptr;
        } else if ( size == 2 ) {
            return *ptr + ( ptr[1] << 8  );
        } else {
            return 0;
        }
    };
    
    for ( sysex_param p : schma->second ) {
        std::string out = header_fn( (uint16) page ,(uint16) 0 , (uint16)p.offset , p.name , [&](uint8 n) -> uint16 { return fn( data(n) + p.offset + 4 , p.size ); } );
        Logger::writeToLog( out);
    }

}
