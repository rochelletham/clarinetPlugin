/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class clarinetPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
   clarinetPluginAudioProcessorEditor (clarinetPluginAudioProcessor&);
    ~clarinetPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
   clarinetPluginAudioProcessor& audioProcessor;

   juce::Slider midiVolumeSlider;
   juce::Slider pressureSlider;
   juce::Slider breathCutoffSlider;
   juce::Slider breathGainSlider;

   juce::Label volumeLabel;
   juce::Label pressureLabel;
   juce::Label breathCutoffLabel;
   juce::Label breathGainLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (clarinetPluginAudioProcessorEditor)
};
