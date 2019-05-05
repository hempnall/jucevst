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
    setSize (800, 500);
    
    addAndMakeVisible (&dump_state_button_);
    dump_state_button_.setButtonText ("Dump State...");
    dump_state_button_.onClick = [this] { dumpStateButtonClicked(); };
    
    addAndMakeVisible (&send_dump_to_moxf_button_);
    send_dump_to_moxf_button_.setButtonText ("Send state to MOXF...");
    send_dump_to_moxf_button_.onClick = [this] { sendStateToMoxfClicked(); };
    
    addAndMakeVisible(&read_only_toggle_);
    read_only_toggle_.setButtonText("Read Only");
    read_only_toggle_.setToggleState(false, NotificationType::dontSendNotification);
    read_only_toggle_.onClick = [this] { readOnlyToggleClicked(); };
    
    addAndMakeVisible(&all_channels_toggle_);
    all_channels_toggle_.setButtonText("All Channels");
    all_channels_toggle_.setToggleState(false, NotificationType::dontSendNotification);
    all_channels_toggle_.onClick = [this] { allChannelsToggleClicked(); };
    
    
    for (int i=0; i < 16 ; ++i) {
        addAndMakeVisible( &channel_toggle_[i] );
        channel_toggle_[i].setButtonText(String::formatted("%d", i+1));
        channel_toggle_[i].onClick = [this,i] { channelToggleButtonClicked(i); };
    }
    
    allChannelsToggleClicked();
    readOnlyToggleClicked();
    
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
    int width = getWidth();
    int colwidth = ( width - 20 ) / 4;
    
    dump_state_button_          .setBounds (10, 10,  width - 20, 20);
    send_dump_to_moxf_button_   .setBounds (10, 40,  width - 20, 20);
    read_only_toggle_           .setBounds (10, 70,  colwidth * 2, 20);
    all_channels_toggle_        .setBounds (10 + (colwidth * 2) , 70 , colwidth * 2 , 20);
    
    for ( int i = 0 ; i < 16 ; ++i ) {
        int col = i % 4;
        int row = i / 4;
        Logger::writeToLog(String::formatted("i=%d col=%d row=%d p1=%d p2=%d p3=%d p4=%d", i , col , row ,10 + ( col * colwidth) , 100 + ( 30 * row ) , colwidth  , 20 ));
        channel_toggle_[i]      .setBounds ( 10 + ( col * colwidth) , 100 + ( 30 * row ) , colwidth  , 20 );
    }
}

void Moxfvst3songModeAudioProcessorEditor::dumpStateButtonClicked()
{
    processor.dumpState();
}

void Moxfvst3songModeAudioProcessorEditor::sendStateToMoxfClicked()
{
    processor.sendStateToMoxf();
}


void Moxfvst3songModeAudioProcessorEditor::readOnlyToggleClicked()
{
    processor.setReadOnly(  read_only_toggle_.getToggleState()  );
}

void Moxfvst3songModeAudioProcessorEditor::allChannelsToggleClicked()
{
    for ( int i = 0 ; i < 16 ;  ++i ) {
        channel_toggle_[i].setToggleState(  all_channels_toggle_.getToggleState()  , NotificationType::sendNotification );
    }
}

void Moxfvst3songModeAudioProcessorEditor::channelToggleButtonClicked(int chn)
{
    Logger::writeToLog(String::formatted("channel clicked: %d", chn));
    processor.setMuteChannel(chn,  channel_toggle_[chn].getToggleState()  );
}
