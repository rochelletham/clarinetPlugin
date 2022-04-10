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

   float kPressureDEF = 0.0;
   float kBreathGainDEF = 0.1;
   float kBreathCutoffDEF = 2000;
   float kVibratoFreqDEF = 5.0;
   float kVibratoGainDEF = 0.25;
   float kClarinetLenDEF = 0.8;
   float kReedStiffDEF = 0.5;
   float kBellOpeningDEF = 0.5;
   float kOutGainDEF = 0.0;
   
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
   clarinetPluginAudioProcessor& audioProcessor;

   juce::LookAndFeel_V4 otherLookAndFeel;

   juce::Slider midiVolumeSlider;
   juce::Slider pressureSlider;
   juce::Slider breathCutoffSlider;
   juce::Slider breathGainSlider;
   juce::Slider vibratoFreqSlider;
   juce::Slider vibratoGainSlider;
   juce::Slider clarinetLenSlider;
   juce::Slider reedStiffnessSlider;
   juce::Slider bellOpeningSlider;
   juce::Slider outGainSlider;

   // TODO: change this to button later
   juce::Label audioSettingsButton;
   juce::Label volumeLabel;
   juce::Label pressureLabel;
   juce::Label breathCutoffLabel;
   juce::Label breathGainLabel;
   juce::Label vibratoFreqLabel;
   juce::Label vibratoGainLabel;
   juce::Label clarinetLenLabel;
   juce::Label reedStiffnessLabel;
   juce::Label bellOpeningLabel;
   juce::Label outGainLabel;

   /// A specialized JUCE component that displays a wave form.
   juce::AudioVisualiserComponent audioVisualizer;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (clarinetPluginAudioProcessorEditor)
};