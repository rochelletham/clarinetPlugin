/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <vector>
#include <string>
using namespace juce;
//==============================================================================
/**
*/
class clarinetPluginAudioProcessorEditor  :
//   public AudioAppComponent,
//   public Button::Listener,
   public AudioProcessorEditor {

public:
   clarinetPluginAudioProcessorEditor (clarinetPluginAudioProcessor&);
    ~clarinetPluginAudioProcessorEditor() override;

    //==============================================================================
   void paint (juce::Graphics&) override;
   void resized() override;
//   void openAudioSettings();
//   bool keyPressed(KeyPress &k) override;
   float kFreqDEF = 146.832;
   float kEnvDEF = 1.0;
   float kBendDEF = 0;
   float kPressureDEF = 0.0;
   float kBreathGainDEF = 0.1;
   float kBreathCutoffDEF = 2000;
   float kVibratoFreqDEF = 5.0;
   float kVibratoGainDEF = 0.25;
   float kClarinetLenDEF = 0.8;
   float kReedStiffDEF = 0.5;
   float kBellOpeningDEF = 0.5;
   float kOutGainDEF = 0.0;

   float kTextWidth = 55;
   float kTextHeight = 20;

//      float freqStrWidth;
private:
   /**
    initializes the gui sliders
    */
   void setSliders();
   /**
    initializes the gui labels
    */
   void setLabels();
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
   clarinetPluginAudioProcessor& audioProcessor;

   juce::TextButton gateButton;
   juce::Slider freqSlider;
   juce::Slider envAttackSlider;
   juce::Slider bendSlider;
   juce::Slider vibratoFreqSlider;
   juce::Slider vibratoGainSlider;

   juce::Slider reedStiffnessSlider;
   juce::Slider bellOpeningSlider;
   juce::Slider outGainSlider;
   juce::Slider zoomSlider;

      // These parameters are not available in the clarinet midi version. 
      //   juce::Slider pressureSlider;
      //   juce::Slider breathCutoffSlider;
      //   juce::Slider breathGainSlider;
      //   juce::Slider clarinetLenSlider;

   juce::Label freqLabel;
   juce::Label envAttackLabel;
   juce::Label bendLabel;
   juce::Label vibratoFreqLabel;
   juce::Label vibratoGainLabel;
   juce::Label reedStiffnessLabel;
   juce::Label bellOpeningLabel;
   juce::Label outGainLabel;
   juce::Label gateLabel;
   juce::Label zoomLabel;

   std::vector<string> labelText = {"Freq", "Bend", "Rate", "Gain",
                                    "Envelope\nAttack", "Reed\nStiffness",
                                    "Bell\nOpening", "Out Gain", "Zoom"};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (clarinetPluginAudioProcessorEditor)
};
