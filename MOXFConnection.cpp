//
//  MOXFConnection.cpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 07/03/2019.
//

#include "MOXFConnection.hpp"
#include "sysexparams.h"

midibyte_t bulkheader[] = {
    0x43, 0x00, 0x7F, 0x1C, 0x00, 0x04, 0x00 , 0x0E, 0x5F , 0x00, 0x13
};

midibyte_t bulkfooter[] = {
   0x43, 0x00, 0x7F, 0x1C, 0x00, 0x04, 0x00 , 0x0F, 0x5F , 0x00, 0x12
};

MidiMessage bulkheadermsg = MidiMessage::createSysExMessage( bulkheader, sizeof(bulkheader));
MidiMessage bulkfootermsg = MidiMessage::createSysExMessage( bulkfooter, sizeof(bulkfooter));

#define PORT_NOT_FOUND -1
template< typename T >
int getMidiPortIndex( String port )
{
    auto devices = T::getDevices();
    String * device = std::find( devices.begin() , devices.end() ,  port );
    if (device == devices.end() ) {
        return PORT_NOT_FOUND;
    } else {
        int index = std::distance(devices.begin(), device);
        return  index;
    }
}

bool MOXFConnection::openMidiPorts( const String& portname, midiinput_t& input , midioutput_t& output )
{
    int input_device_index = getMidiPortIndex<MidiInput>( portname );
    int output_device_index = getMidiPortIndex<MidiInput>( portname );
    
    if (input_device_index == PORT_NOT_FOUND || output_device_index == PORT_NOT_FOUND ) {
        Logger::writeToLog("unable to open midi port");
        return false;
    }
    input = std::unique_ptr<MidiInput,std::function<void(MidiInput*)>>( MidiInput::openDevice(input_device_index, this) , [](MidiInput* i) {
        i->stop(); delete i;
    });
    output = std::unique_ptr<MidiOutput>( MidiOutput::openDevice(output_device_index) );
    return true;
}

MOXFConnection::MOXFConnection()
{
    initialise_logger();
    
    if ( ! openMidiPorts(MOXF_EDITOR_PORT, editor_input_, editor_output_) ) {
        return;
    }
    
    if ( !openMidiPorts(MOXF_SYSEX_BULK_PORT, bulk_input_, bulk_output_) ) {
        return;
    }

    Logger::writeToLog( editor_input_->getName() );

    editor_input_->start();
    bulk_input_->start();
}

MOXFConnection::~MOXFConnection()
{
    Logger::writeToLog("destructor");
    
}

void MOXFConnection::initialise_logger()
{
    File f(  JUCE_VST3_LOGFILE_DEFAULT_VALUE );
    if (f.existsAsFile()) {
        logger_ = std::make_unique<FileLogger>(  f , JUCE_VST3_LOGFILE_WELCOME_MESSAGE   );
        Logger::setCurrentLogger(logger_.get());
    }
}


void MOXFConnection::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message)
{
    if (is_read_only_) return;
    
    if ( source == editor_input_.get()   ) {
        process_editor_data(message);
    } else if ( source == bulk_input_.get() ) {
        process_midi_data(message);
    } else {
        Logger::writeToLog("mididata - not interested");
    }
}


void MOXFConnection::process_sysex_data( const midibyte_t * data , int size )
{

    if ( ! isMoxf(data, size) ) return;
    
    MidiSysExInfoWrite sysex;
    
    if ( isBulk( data , size )) {

        uint16 datasize = getBulkDataSize(data, size);
        if ( datasize + 7 != size ) return;
 
        sysex.channel = data[8];
        sysex.datatype = data[7];
        sysex.destindex = data[9];
        sysex.size = datasize ;
        sysex.sourcedata = (midibyte_t*) &data[6];
        
        if ( data[6] == MODEL_ID ) {
            state_.applySysex(sysex);
        } else if ( data[6] == MODEL_ID_EDITOR ) {
            state_.compareSysex(sysex);
        } else {
            return;
        }

    } else {
        
        if ( size < 9 ) return;
        
        sysex.channel = data[6];
        sysex.datatype = data[5];
        sysex.destindex = data[7] + 4;
        sysex.size = size - 8;
        sysex.sourcedata = (midibyte_t*) &data[8];
        state_.applySysex(sysex);
    }
    
}

bool MOXFConnection::isBulk(const midibyte_t* data , int size)
{
    if ( ( data[1] & 0xF0 ) == 0x00 ) return true;
    return false;
}

bool MOXFConnection::isMoxf(const midibyte_t* data , int size)
{
    if ( size < MIN_SYSEX_SIZE ) return false;
    if ( data[0] != YAMAHA )  return false;
    if ( data[2] != MOXF_HI ) return false;
    if ( data[3] != MOXF_LO ) return false;
    return true;
}

uint16  MOXFConnection::getBulkDataSize( const midibyte_t* data , int size )
{
    return data[4] << 8 | data[5];
}



void MOXFConnection::process_editor_data(const juce::MidiMessage &message) {
    if (!message.isSysEx()) {
        Logger::writeToLog("editor data - notSysEx");
        return;
    }
    const uint8* data = message.getSysExData();
    int size = message.getSysExDataSize();
    process_sysex_data( data , size);
}

void MOXFConnection::process_midi_data(const juce::MidiMessage &message) {
    if (!message.isSysEx()) {
        return;
    }
    const uint8* data = message.getSysExData();
    int size = message.getSysExDataSize();
    process_sysex_data( data , size);
}


void MOXFConnection::dumpState()
{
    state_.dumpState();
}

void MOXFConnection::bulkOutput()
{
    Logger::writeToLog("bulkOutput");
    MidiOutput* output = bulk_output_.get();
    if ( output == nullptr ) return;
//
    output->sendMessageNow(bulkheadermsg);
    state_.common_.common.sendToSysEx( output );
    state_.common_.reverb.sendToSysEx( output );
    state_.common_.chorus.sendToSysEx( output );
    state_.common_.insertion_a.sendToSysEx( output );
    state_.common_.insertion_b.sendToSysEx( output );
    state_.common_.master_eq.sendToSysEx(output);
    state_.common_.master_effect.sendToSysEx(output);
    state_.common_.appregio.sendToSysEx(output);
    for ( int i=0 ; i < 16 ; ++i ) {
        state_.parts_[i].partdata.sendToSysEx(output , i);
    }
    for ( int i=0 ; i < 16 ; ++i ) {
        state_.parts_[i].arpdata.sendToSysEx(output , i);
    }
    state_.common_.audio.sendToSysEx(output);
    output->sendMessageNow(bulkfootermsg);
    
}

void MOXFConnection::setReadOnly(bool isReadOnly)
{
    is_read_only_ = isReadOnly;
}

void MOXFConnection::setMuteChannel( midichannel_t chn ,  bool isMuted )
{
    state_.parts_[chn].partdata.setMuted( isMuted);
    state_.parts_[chn].arpdata.setMuted( isMuted);
}
