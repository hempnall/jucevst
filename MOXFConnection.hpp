//
//  MOXFConnection.hpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 07/03/2019.
//

#ifndef MOXFConnection_hpp
#define MOXFConnection_hpp

#define JUCE_VST3_LOGFILE_DEFAULT_VALUE "~/vst3.log"
#define JUCE_VST3_LOGFILE_WELCOME_MESSAGE "VST3 Log"
#define MOXF_EDITOR_PORT "Yamaha MOXF6/MOXF8 Port4"
#define MOXF_SYSEX_BULK_PORT "Yamaha MOXF6/MOXF8 Port1"

#include <stdio.h>
#include <memory>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MOXFSongState.hpp"



class MOXFConnection
    : public MidiInputCallback
{
    
public:
    
    
    MOXFConnection();
    ~MOXFConnection();
    void handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message) override ;
    void dumpState();
    void bulkOutput();
    MOXFSongState state_;
    typedef std::unique_ptr<MidiInput,std::function<void(MidiInput*)>> midiinput_t;
    typedef std::unique_ptr<MidiOutput> midioutput_t;
    	
private:

    
    bool openMidiPorts( const String& portname , midiinput_t& , midioutput_t& );
    
    bool isMoxf(const midibyte_t* data , int size);
    bool isBulk(const midibyte_t* data , int size);
    void process_sysex_data( const midibyte_t * data , int size );
    uint16 getBulkDataSize( const midibyte_t* data , int size );
    
    void process_editor_data(const juce::MidiMessage &message);
    void process_midi_data(const juce::MidiMessage &message);
    
    void initialise_logger();
    std::unique_ptr<Logger> logger_;
    
    midiinput_t editor_input_;
    midioutput_t editor_output_;
    
    midiinput_t bulk_input_;
    midioutput_t bulk_output_;
    

};



#endif /* MOXFConnection_hpp */
