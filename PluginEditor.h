/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Moxfvst3songModeAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Moxfvst3songModeAudioProcessorEditor (Moxfvst3songModeAudioProcessor&);
    ~Moxfvst3songModeAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void dumpStateButtonClicked();
    void sendStateToMoxfClicked();
    void readOnlyToggleClicked();
    void allChannelsToggleClicked();
    void channelToggleButtonClicked(int chn);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Moxfvst3songModeAudioProcessor& processor;
    TextButton dump_state_button_;
    TextButton send_dump_to_moxf_button_;
    ToggleButton read_only_toggle_;
    ToggleButton all_channels_toggle_;
    ToggleButton channel_toggle_[16];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Moxfvst3songModeAudioProcessorEditor)
};
