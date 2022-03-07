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

    juce::Slider midiVolume;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (clarinetPluginAudioProcessorEditor)
};
