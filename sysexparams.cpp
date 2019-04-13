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
    { 0x10 , "Detune" , 2 , 0, 0 },
    { 0x12,"Reverb Send ",1,0,0},
    { 0x13,"Chorus Send ",1,0,0},
    { 0x14,"reserved ",1,0,0},
    { 0x15,"Dry Level ",1,0,0},
    { 0x16,"Note Shift ",1,0,0},
    { 0x17,"reserved ",1,0,0},
    { 0x18,"Param. with Voice ",1,0,0},
    { 0x19,"Voice with Arp ",1,0,0},
    { 0x1A ,"Portamento Switch ",1,0,0},
    { 0x1B ,"Portamento Time ",1,0,0},
    { 0x1C ,"Portamento Mode ",1,0,0},
    { 0x1D ,"reserved ",1,0,0},
    { 0x1E ,"USB Audio Output Select ",1,0,0},
    { 0x1F ,"Receive PB",1,0,0},
    { 0x20,"Receive FC2",1,0,0},
    { 0x21,"Receive Assignable Function 2",1,0,0},
    { 0x22,"Voice Element Pan ",1,0,0},
    { 0x23,"AEG Attack Time ",1,0,0},
    { 0x24,"AEG Decay Time ",1,0,0},
    { 0x25,"AEG Sustain Level ",1,0,0},
    { 0x26,"AEG Release Time ",1,0,0},
    { 0x27,"FEG Attack Time ",1,0,0},
    { 0x28,"FEG Decay Time ",1,0,0},
    { 0x29,"FEG Sustain Level ",1,0,0},
    { 0x2A ,"FEG Release Time ",1,0,0},
    { 0x2B ,"FEG Depth ",1,0,0},
    { 0x2C ,"reserved ",1,0,0},
    { 0x2D ,"Filter Cutoff Frequency ",1,0,0},
    { 0x2E ,"Filter Resonance/Width ",1,0,0},
    { 0x2F ,"reserved ",1,0,0},
    { 0x30,"EQ Low Frequency ",2,0,0},
    { 0x32,"EQ Low Gain ",1,0,0},
    { 0x33,"reserved ",1,0,0},
    { 0x34,"EQ Mid Frequency ",2,0,0},
    { 0x36,"EQ Mid Gain ",1,0,0},
    { 0x37,"EQ Mid Q ",1,0,0},
    { 0x38,"EQ High Frequency ",2,0,0},
    { 0x3A ,"EQ High Gain ",1,0,0},
    { 0x3B ,"reserved ",1,0,0},
    { 0x3C ,"Assignable Knob 1 Value ",1,0,0},
    { 0x3D ,"Assignable Knob 2 Value ",1,0,0}
};

sysex_page_schema_t param_data_38 = {
    { 0x0,"ARP Switch ",1,0,0},
    { 0x1,"ARP MIDI Out Switch ",1,0,0},
    { 0x2,"ARP Transmit Channel ",1,0,0},
    { 0x3,"ARP Play Only ",1,0,0},
    { 0x4,"ARP Fixed SD/BD ",1,0,0},
    { 0x5,"reserved ",1,0,0},
    { 0x6,"ARP Loop ",1,0,0},
    { 0x7,"ARP Hold ",1,0,0},
    { 0x8,"ARP Unit Multiply ",1,0,0},
    { 0x9,"ARP Note Limit Low ",1,0,0},
    { 0x0A ,"ARP Note Limit High ",1,0,0},
    { 0x0B ,"ARP Velocity Limit Low ",1,0,0},
    { 0x0C ,"ARP Velocity Limit High ",1,0,0},
    { 0x0D ,"ARP Key Mode ",1,0,0},
    { 0x0E ,"ARP Velocity Mode ",1,0,0},
    { 0x0F ,"ARP Change Timing ",1,0,0},
    { 0x10,"ARP Quantize Value ",1,0,0},
    { 0x11,"ARP Quantize Strength ",1,0,0},
    { 0x12,"ARP Velocity Rate ",2,0,0},
    { 0x14,"ARP Gate Time Rate ",2,0,0},
    { 0x16,"reserved ",1,0,0},
    { 0x17,"reserved ",1,0,0},
    { 0x18,"reserved ",1,0,0},
    { 0x19,"reserved ",1,0,0},
    { 0x1A ,"ARP Swing ",2,0,0},
    { 0x1C ,"ARP Accent Velocity Threshold ",1,0,0},
    { 0x1D ,"ARP Accent Start Quantize ",1,0,0},
    { 0x1E ,"ARP Octave Range ",1,0,0},
    { 0x1F ,"ARP Output Octave Shift ",1,0,0},
    { 0x20,"ARP Trigger Mode ",1,0,0},
    { 0x21,"ARP Random SFX ",1,0,0},
    { 0x22,"ARP Random SFX Keyon Control ",1,0,0},
    { 0x23,"ARP Random SFX Velocity Offset ",1,0,0},
    { 0x24,"ARP Assign Velocity Rate Offset SF1 ",2,0,0},
    { 0x26,"ARP Assign Gate Time Rate Offset SF1 ",2,0,0},
    { 0x28,"ARP Assign Velocity Rate Offset SF2 ",2,0,0},
    { 0x2A ,"ARP Assign Gate Time Rate Offset SF2 ",2,0,0},
    { 0x2C ,"ARP Assign Velocity Rate Offset SF3 ",2,0,0},
    { 0x2E ,"ARP Assign Gate Time Rate Offset SF3 ",2,0,0},
    { 0x30,"ARP Assign Velocity Rate Offset SF4 ",2,0,0},
    { 0x32,"ARP Assign Gate Time Rate Offset SF4 ",2,0,0},
    { 0x34,"ARP Assign Velocity Rate Offset SF5 ",2,0,0},
    { 0x36,"ARP Assign Gate Time Rate Offset SF5 ",2,0,0},
    { 0x38,"ARP Assign Velocity Rate Offset SF6 ",2,0,0},
    { 0x3A ,"ARP Assign Gate Time Rate Offset SF6 ",2,0,0},
    { 0x3C ,"ARP SF1 Assign Type ",2,0,0},
    { 0x3E ,"ARP SF2 Assign Type ",2,0,0},
    { 0x40,"ARP SF3 Assign Type ",2,0,0},
    { 0x42,"ARP SF4 Assign Type ",2,0,0},
    { 0x44,"ARP SF5 Assign Type ",2,0,0},
    { 0x46,"ARP SF6 Assign Type ",2,0,0}
};

sysex_page_schema_t param_data_39_40 = {
    { 0x0,"Audio Input Mode ",1,0,0},
    { 0x1,"Audio Input Part Volume ",1,0,0},
    { 0x2,"Audio Input Part Pan ",1,0,0},
    { 0x3,"Audio Input Part Reverb Send ",1,0,0},
    { 0x4,"Audio Input Part Chorus Send ",1,0,0},
    { 0x5,"reserved ",1,0,0},
    { 0x6,"Audio Input Part Dry Level ",1,0,0}
};

sysex_page_schema_t param_data_36_11 = {
    { 0x0,"Master Effect Type ",2,0,0},
    { 0x2,"Preset Number ",1,0,0},
    { 0x3,"reserved ",1,0,0},
    { 0x4,"Master Effect Parameter 1 ",2,0,0},
    { 0x6,"Master Effect Parameter 2 ",2,0,0},
    { 0x8,"Master Effect Parameter 3 ",2,0,0},
    { 0x0A ,"Master Effect Parameter 4 ",2,0,0},
    { 0x0C ,"Master Effect Parameter 5 ",2,0,0},
    { 0x0E ,"Master Effect Parameter 6 ",2,0,0},
    { 0x10,"Master Effect Parameter 7 ",2,0,0},
    { 0x12,"Master Effect Parameter 8 ",2,0,0},
    { 0x14,"Master Effect Parameter 9 ",2,0,0},
    { 0x16,"Master Effect Parameter 10 ",2,0,0},
    { 0x18,"Master Effect Parameter 11 ",2,0,0},
    { 0x1A ,"Master Effect Parameter 12 ",2,0,0},
    { 0x1C ,"Master Effect Parameter 13 ",2,0,0},
    { 0x1E ,"Master Effect Parameter 14 ",2,0,0},
    { 0x20,"Master Effect Parameter 15 ",2,0,0},
    { 0x22,"Master Effect Parameter 16 ",2,0,0},
    { 0x24,"Master Effect Switch ",1,0,0},
    { 0x25,"reserved ",1,0,0}
};

sysex_page_schema_t param_data_36_10 = {
    { 0x0,"EQ Low Gain ",1,0,0},
    { 0x1,"EQ Low Frequency ",1,0,0},
    { 0x2,"EQ Low Q ",1,0,0},
    { 0x3,"EQ Low Shape ",1,0,0},
    { 0x4,"EQ Low-Mid Gain ",1,0,0},
    { 0x5,"EQ Low-Mid Frequency ",1,0,0},
    { 0x6,"EQ Low-Mid Q ",1,0,0},
    { 0x7,"reserved ",1,0,0},
    { 0x8,"EQ Mid Gain ",1,0,0},
    { 0x9,"EQ Mid Frequency ",1,0,0},
    { 0x0A ,"EQ Mid Q ",1,0,0},
    { 0x0B ,"reserved ",1,0,0},
    { 0x0C ,"EQ High-Mid Gain ",1,0,0},
    { 0x0D ,"EQ High-Mid Frequency ",1,0,0},
    { 0x0E ,"EQ High-Mid Q ",1,0,0},
    { 0x0F ,"reserved ",1,0,0},
    { 0x10,"EQ High Gain ",1,0,0},
    { 0x11,"EQ High Frequency ",1,0,0},
    { 0x12,"EQ High Q ",1,0,0},
    { 0x13,"EQ High Shape ",1,0,0},
};

sysex_page_schema_t param_data_36_04 = {
    { 0x0,"Insertion B Type ",2,0,0},
    { 0x2,"Preset Number ",1,0,0},
    { 0x3,"reserved ",1,0,0},
    { 0x4,"Insertion B Parameter 1 ",2,0,0},
    { 0x6,"Insertion B Parameter 2 ",2,0,0},
    { 0x8,"Insertion B Parameter 3 ",2,0,0},
    { 0x0A ,"Insertion B Parameter 4 ",2,0,0},
    { 0x0C ,"Insertion B Parameter 5 ",2,0,0},
    { 0x0E ,"Insertion B Parameter 6 ",2,0,0},
    { 0x10,"Insertion B Parameter 7 ",2,0,0},
    { 0x12,"Insertion B Parameter 8 ",2,0,0},
    { 0x14,"Insertion B Parameter 9 ",2,0,0},
    { 0x16,"Insertion B Parameter 10 ",2,0,0},
    { 0x18,"Insertion B Parameter 11 ",2,0,0},
    { 0x1A ,"Insertion B Parameter 12 ",2,0,0},
    { 0x1C ,"Insertion B Parameter 13 ",2,0,0},
    { 0x1E ,"Insertion B Parameter 14 ",2,0,0},
    { 0x20,"Insertion B Parameter 15 ",2,0,0},
    { 0x22,"Insertion B Parameter 16 ",2,0,0}
} ;

sysex_page_schema_t param_data_36_03 = {
    { 0x0,"Insertion A Type ",2,0,0},
    { 0x2,"Preset Number ",1,0,0},
    { 0x3,"reserved ",1,0,0},
    { 0x4,"Insertion A Parameter 1 ",2,0,0},
    { 0x6,"Insertion A Parameter 2 ",2,0,0},
    { 0x8,"Insertion A Parameter 3 ",2,0,0},
    { 0x0A ,"Insertion A Parameter 4 ",2,0,0},
    { 0x0C ,"Insertion A Parameter 5 ",2,0,0},
    { 0x0E ,"Insertion A Parameter 6 ",2,0,0},
    { 0x10,"Insertion A Parameter 7 ",2,0,0},
    { 0x12,"Insertion A Parameter 8 ",2,0,0},
    { 0x14,"Insertion A Parameter 9 ",2,0,0},
    { 0x16,"Insertion A Parameter 10 ",2,0,0},
    { 0x18,"Insertion A Parameter 11 ",2,0,0},
    { 0x1A ,"Insertion A Parameter 12 ",2,0,0},
    { 0x1C ,"Insertion A Parameter 13 ",2,0,0},
    { 0x1E ,"Insertion A Parameter 14 ",2,0,0},
    { 0x20,"Insertion A Parameter 15 ",2,0,0},
    { 0x22,"Insertion A Parameter 16 ",2,0,0}
} ;

sysex_page_schema_t param_data_36_02 = {
    { 0x0,"Chorus Type ",2,0,0},
    { 0x2,"Preset Number ",1,0,0},
    { 0x3,"reserved ",1,0,0},
    { 0x4,"Chorus Parameter 1 ",2,0,0},
    { 0x6,"Chorus Parameter 2 ",2,0,0},
    { 0x8,"Chorus Parameter 3 ",2,0,0},
    { 0x0A ,"Chorus Parameter 4 ",2,0,0},
    { 0x0C ,"Chorus Parameter 5 ",2,0,0},
    { 0x0E ,"Chorus Parameter 6 ",2,0,0},
    { 0x10,"Chorus Parameter 7 ",2,0,0},
    { 0x12,"Chorus Parameter 8 ",2,0,0},
    { 0x14,"Chorus Parameter 9 ",2,0,0},
    { 0x16,"Chorus Parameter 10 ",2,0,0},
    { 0x18,"Chorus Parameter 11 ",2,0,0},
    { 0x1A ,"Chorus Parameter 12 ",2,0,0},
    { 0x1C ,"Chorus Parameter 13 ",2,0,0},
    { 0x1E ,"Chorus Parameter 14 ",2,0,0},
    { 0x20,"Chorus Parameter 15 ",2,0,0},
    { 0x22,"Chorus Parameter 16 ",2,0,0},
    { 0x24,"Chorus Return ",1,0,0},
    { 0x25,"Chorus Pan ",1,0,0},
    { 0x26,"Send Chorus To Reverb ",1,0,0},
    { 0x27,"reserved ",1,0,0}
};

sysex_page_schema_t param_data_36_01 = {
    { 0x0,"Reverb Type ",2,0,0},
    { 0x2,"Preset Number ",1,0,0},
    { 0x3,"reserved ",1,0,0},
    { 0x4,"Reverb Parameter 1 ",2,0,0},
    { 0x6,"Reverb Parameter 2 ",2,0,0},
    { 0x8,"Reverb Parameter 3 ",2,0,0},
    { 0x0A ,"Reverb Parameter 4 ",2,0,0},
    { 0x0C ,"Reverb Parameter 5 ",2,0,0},
    { 0x0E ,"Reverb Parameter 6 ",2,0,0},
    { 0x10,"Reverb Parameter 7 ",2,0,0},
    { 0x12,"Reverb Parameter 8 ",2,0,0},
    { 0x14,"Reverb Parameter 9 ",2,0,0},
    { 0x16,"Reverb Parameter 10 ",2,0,0},
    { 0x18,"Reverb Parameter 11 ",2,0,0},
    { 0x1A ,"Reverb Parameter 12 ",2,0,0},
    { 0x1C ,"Reverb Parameter 13 ",2,0,0},
    { 0x1E ,"Reverb Parameter 14 ",2,0,0},
    { 0x20,"Reverb Parameter 15 ",2,0,0},
    { 0x22,"Reverb Parameter 16 ",2,0,0},
    { 0x24,"Reverb Return ",1,0,0},
    { 0x25,"Reverb Pan ",1,0,0}
};

sysex_page_schema_t param_data_36_30 = {
    { 0x0,"ARP SF Select ",1,0,0},
    { 0x1,"reserved ",1,0,0},
    { 0x2,"reserved ",2,0,0},
    { 0x4,"ARP Common Switch ",1,0,0},
    { 0x5,"ARP Synchro Quantize Value ",1,0,0},
    { 0x6,"ARP Quantize Strength Offset ",2,0,0},
    { 0x8,"ARP Gate Time Rate Offset ",2,0,0},
    { 0x0A ,"ARP Velocity Rate Offset ",2,0,0},
    { 0x0C ,"ARP Swing Offset ",2,0,0}
};

sysex_page_schema_t param_data_36_00 = {
    { 0x0,"reserved ",1,0,0},
    { 0x1,"reserved ",1,0,0},
    { 0x2,"reserved ",1,0,0},
    { 0x3,"reserved ",1,0,0},
    { 0x4,"reserved ",1,0,0},
    { 0x5,"reserved ",1,0,0},
    { 0x6,"reserved ",1,0,0},
    { 0x7,"reserved ",1,0,0},
    { 0x8,"reserved ",1,0,0},
    { 0x9,"reserved ",1,0,0},
    { 0x0A ,"reserved ",1,0,0},
    { 0x0B ,"reserved ",1,0,0},
    { 0x0C ,"reserved ",1,0,0},
    { 0x0D ,"reserved ",1,0,0},
    { 0x0E ,"reserved ",1,0,0},
    { 0x0F ,"reserved ",1,0,0},
    { 0x10,"reserved ",1,0,0},
    { 0x11,"reserved ",1,0,0},
    { 0x12,"reserved ",1,0,0},
    { 0x13,"reserved ",1,0,0},
    { 0x14,"reserved ",1,0,0},
    { 0x15,"reserved ",1,0,0},
    { 0x16,"reserved ",1,0,0},
    { 0x17,"reserved ",1,0,0},
    { 0x18,"reserved ",1,0,0},
    { 0x19,"reserved ",1,0,0},
    { 0x1A ,"reserved ",1,0,0},
    { 0x1B ,"reserved ",1,0,0},
    { 0x1C ,"reserved ",1,0,0},
    { 0x1D ,"reserved ",1,0,0},
    { 0x1E ,"Knob Function Select ",1,0,0},
    { 0x1F ,"reserved ",1,0,0},
    { 0x20,"reserved ",1,0,0},
    { 0x21,"reserved ",1,0,0},
    { 0x22,"reserved ",1,0,0},
    { 0x23,"reserved ",1,0,0},
    { 0x24,"reserved ",1,0,0},
    { 0x25,"reserved ",1,0,0},
    { 0x26,"reserved ",1,0,0},
    { 0x27,"reserved ",1,0,0},
    { 0x28,"reserved ",1,0,0},
    { 0x29,"reserved ",1,0,0},
    { 0x2A ,"reserved ",1,0,0},
    { 0x2B ,"reserved ",1,0,0},
    { 0x2C ,"reserved ",1,0,0},
    { 0x2D ,"reserved ",1,0,0},
    { 0x2E ,"reserved ",1,0,0},
    { 0x2F ,"reserved ",1,0,0},
    { 0x30,"reserved ",1,0,0},
    { 0x31,"reserved ",1,0,0},
    { 0x32,"reserved ",1,0,0},
    { 0x33,"reserved ",1,0,0},
    { 0x34,"reserved ",1,0,0},
    { 0x35,"reserved ",1,0,0},
    { 0x36,"reserved ",1,0,0},
    { 0x37,"reserved ",1,0,0},
    { 0x38,"reserved ",1,0,0},
    { 0x39,"reserved ",1,0,0},
    { 0x3A ,"reserved ",1,0,0},
    { 0x3B ,"reserved ",1,0,0},
    { 0x3C ,"reserved ",1,0,0},
    { 0x3D ,"reserved ",1,0,0},
    { 0x3E ,"reserved ",1,0,0},
    { 0x3F ,"Assignable Function 1 Mode ",1,0,0},
    { 0x40,"Assignable Function 2 Mode ",1,0,0},
    { 0x41,"reserved ",1,0,0},
    { 0x42,"reserved ",1,0,0},
    { 0x43,"reserved ",1,0,0},
    { 0x44,"reserved ",1,0,0},
    { 0x45,"reserved ",1,0,0},
    { 0x46,"reserved ",1,0,0},
    { 0x47,"reserved ",1,0,0},
    { 0x48,"reserved ",1,0,0},
    { 0x49,"reserved ",1,0,0},
    { 0x4A ,"reserved ",1,0,0},
    { 0x4B ,"A/D Input Insertion Connect Type ",1,0,0},
    { 0x4C ,"Insertion Part Sw ",4,0,0}
};


sysex_schema_t moxf_schema = {
    { 0x37 , param_data_37 },
    { 0x38 , param_data_38 },
    { 0x3940 , param_data_39_40 },
    { 0x3611 , param_data_36_11 },
    { 0x3610 , param_data_36_10 },
    { 0x3603 , param_data_36_03 },
    { 0x3604 , param_data_36_04 },
    { 0x3602 , param_data_36_02 },
    { 0x3601 , param_data_36_01 },
    { 0x3600 , param_data_36_00 },
    { 0x3630 , param_data_36_30 },
};


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
