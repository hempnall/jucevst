/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Moxfvst3songModeAudioProcessorEditor::Moxfvst3songModeAudioProcessorEditor (Moxfvst3songModeAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible (&dump_state_button_);
    dump_state_button_.setButtonText ("Dump State...");
    dump_state_button_.onClick = [this] { dumpStateButtonClicked(); };
    
    addAndMakeVisible (&send_dump_to_moxf_button_);
    send_dump_to_moxf_button_.setButtonText ("Send state to MOXF...");
    send_dump_to_moxf_button_.onClick = [this] { sendStateToMoxfClicked(); };
}

Moxfvst3songModeAudioProcessorEditor::~Moxfvst3songModeAudioProcessorEditor()
{
}

//==============================================================================
void Moxfvst3songModeAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
   
}

void Moxfvst3songModeAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    dump_state_button_          .setBounds (10, 10,  getWidth() - 20, 20);
    send_dump_to_moxf_button_   .setBounds (10, 40,  getWidth() - 20, 20);
}

void Moxfvst3songModeAudioProcessorEditor::dumpStateButtonClicked()
{
    processor.dumpState();
}

void Moxfvst3songModeAudioProcessorEditor::sendStateToMoxfClicked()
{
    processor.sendStateToMoxf();
}
