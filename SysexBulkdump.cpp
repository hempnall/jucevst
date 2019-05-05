//
//  SysexBulkdump.cpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 22/04/2019.
//

#include "SysexBulkdump.hpp"


midibyte_t bulkheader[] = {
    0x43, 0x00, 0x7F, 0x1C, 0x00, 0x04, 0x00 , 0x0E, 0x5F , 0x00, 0x13
};

midibyte_t bulkfooter[] = {
    0x43, 0x00, 0x7F, 0x1C, 0x00, 0x04, 0x00 , 0x0F, 0x5F , 0x00, 0x12
};

#define SLEEP( DELAY ) Time::waitForMillisecondCounter(Time::getMillisecondCounter() + DELAY);
#define DELAY( CMD , PORT , DELAY ) { \
    state_.CMD.sendToSysEx( PORT );; \
    SLEEP( DELAY ) \
}

MOXFBulkdump::MOXFBulkdump( MOXFSongState& state,  MidiOutput* output, int millisconds  )
    : state_(state), send_delay_(millisconds), output_(output)
{
    bulk_header_ = MidiMessage::createSysExMessage( bulkheader, sizeof(bulkheader));
    bulk_footer_ = MidiMessage::createSysExMessage( bulkfooter, sizeof(bulkfooter));
    
    output_->sendMessageNow(bulk_header_);
}

MOXFBulkdump::~MOXFBulkdump()
{
    output_->sendMessageNow(bulk_footer_);
}

void MOXFBulkdump::send( int milliseconds )
{
    int one_time_send_delay = milliseconds > 0 ? milliseconds : send_delay_;

    Logger::writeToLog("bulkOutput");

    if ( output_ == nullptr ) return;

    DELAY( common_.common , output_ , one_time_send_delay )
    DELAY( common_.reverb , output_ , one_time_send_delay )
    DELAY( common_.common, output_ , one_time_send_delay )
    DELAY( common_.reverb, output_ , one_time_send_delay )
    DELAY( common_.chorus, output_ , one_time_send_delay )
    DELAY( common_.insertion_a, output_ , one_time_send_delay )
    DELAY( common_.insertion_b, output_ , one_time_send_delay )
    DELAY( common_.master_eq, output_ , one_time_send_delay )
    DELAY( common_.master_effect, output_ , one_time_send_delay )
    DELAY( common_.appregio, output_ , one_time_send_delay )
    
//    for ( int i=0 ; i < 16 ; ++i ) {
//        state_.parts_[i].partdata.sendToSysEx(output_ , i);
//        SLEEP( one_time_send_delay )
//    }
//    
//    for ( int i=0 ; i < 16 ; ++i ) {
//        state_.parts_[i].arpdata.sendToSysEx(output_ , i);
//        SLEEP( one_time_send_delay );
//    }
    
    DELAY( common_.audio, output_ , one_time_send_delay )
}
