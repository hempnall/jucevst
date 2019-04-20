/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Moxfvst3songModeAudioProcessor::Moxfvst3songModeAudioProcessor()
     : AudioProcessor (BusesProperties().withOutput ("Output", AudioChannelSet::stereo(), true)  )
{
    Logger::writeToLog("Plugin constructed");
    setToSongMode();
}

Moxfvst3songModeAudioProcessor::~Moxfvst3songModeAudioProcessor()
{
}

//==============================================================================
const String Moxfvst3songModeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Moxfvst3songModeAudioProcessor::acceptsMidi() const
{
    return true;
}

bool Moxfvst3songModeAudioProcessor::producesMidi() const
{
    return false;
}

bool Moxfvst3songModeAudioProcessor::isMidiEffect() const
{
    return false;
}

double Moxfvst3songModeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Moxfvst3songModeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Moxfvst3songModeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Moxfvst3songModeAudioProcessor::setCurrentProgram (int index)
{}

const String Moxfvst3songModeAudioProcessor::getProgramName (int index)
{
    return {};
}

void Moxfvst3songModeAudioProcessor::changeProgramName (int index, const String& newName)
{}

//==============================================================================
void Moxfvst3songModeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{}

void Moxfvst3songModeAudioProcessor::releaseResources()
{}


bool Moxfvst3songModeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{

    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    return true;

}


void Moxfvst3songModeAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

}

//==============================================================================
bool Moxfvst3songModeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Moxfvst3songModeAudioProcessor::createEditor()
{
    return new Moxfvst3songModeAudioProcessorEditor (*this);
}

//==============================================================================
void Moxfvst3songModeAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    Logger::writeToLog("getStateInformation");

    MemoryOutputStream ostr( destData , false );
    ostr << connection_.state_;
    destData.setSize(2618);
    Logger::writeToLog(String::formatted("sha256[%d bytes]: %s", destData.getSize() , SHA256(destData).toHexString().getCharPointer() ));
}

void Moxfvst3songModeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    Logger::writeToLog("setStateInformation");
    Logger::writeToLog(String::formatted("sha256[%d bytes]: %s", sizeInBytes  , SHA256(data,sizeInBytes).toHexString().getCharPointer() ));
    MemoryInputStream instr(data,sizeInBytes,true);
    
    instr >> connection_.state_;
    sendStateToMoxf();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Moxfvst3songModeAudioProcessor();
}

void Moxfvst3songModeAudioProcessor::dumpState()
{
    connection_.dumpState();
}

void Moxfvst3songModeAudioProcessor::sendStateToMoxf()
{
    connection_.bulkOutput();
}

void Moxfvst3songModeAudioProcessor::updateTrackProperties (const TrackProperties &properties)
{
    Logger::writeToLog(properties.name);
}


void Moxfvst3songModeAudioProcessor::setToSongMode()
{
    
}

void Moxfvst3songModeAudioProcessor::setReadOnly(bool isReadOnly) {
    connection_.setReadOnly(isReadOnly);
}

void Moxfvst3songModeAudioProcessor::setMuteChannel(int chn, bool isMuted)
{
    connection_.setMuteChannel(chn, isMuted);
}
