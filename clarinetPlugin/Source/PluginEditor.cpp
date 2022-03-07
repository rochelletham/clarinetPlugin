/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
clarinetPluginAudioProcessorEditor::clarinetPluginAudioProcessorEditor (clarinetPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
   // This is where our plugin’s editor size is set.
   setSize (200, 200);
   midiVolume.setSliderStyle (juce::Slider::LinearBarVertical);
   midiVolume.setRange(0, 127, 1);
   midiVolume.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
   midiVolume.setPopupDisplayEnabled (true, false, this);
   midiVolume.setTextValueSuffix (" Volume");
   midiVolume.setValue(1);

   // makes midiVolume slider visible in window
   addAndMakeVisible (&midiVolume);
}

clarinetPluginAudioProcessorEditor::~clarinetPluginAudioProcessorEditor()
{
}

//==============================================================================
void clarinetPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
//   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
   g.fillAll (juce::Colours::white);
   g.setColour (juce::Colours::blue);
   g.setFont (15.0f);
   g.drawFittedText ("Midi Volume", 0,0, getWidth(), 30, juce::Justification::centred, 1);
}

void clarinetPluginAudioProcessorEditor::resized()
{
   // This is generally where you'll want to lay out the positions of any
   // subcomponents in your editor..
   //(x, y, width, height)
   midiVolume.setBounds (40, 30, 20, getHeight() - 60);
}
