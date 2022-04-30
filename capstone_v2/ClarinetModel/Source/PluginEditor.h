/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MidiMessageLog.h"
#include <vector>
#include <string>
using namespace juce;
//==============================================================================
/**
*/
class clarinetPluginAudioProcessorEditor  :
   public AudioProcessorEditor,
   public juce::MidiInputCallback,
   public juce::MidiKeyboardStateListener
    {

public:
   clarinetPluginAudioProcessorEditor (clarinetPluginAudioProcessor&);
    ~clarinetPluginAudioProcessorEditor() override;

    //==============================================================================
   void paint (juce::Graphics&) override;
   void resized() override;
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
   float kTextHeight = 40;
   float kNumHeight = 20;
   //==============================================================================
   // MidiInputCallback overrides

   /// The callback that responds whenever a MIDI message arrives at the
   /// midiInputDevice. Note: this function does not run in the main message thread
   /// and must never attempt to update GUI components with taking steps to insure
   /// that both threads do not access components at the same time.  Your method
   /// should take the following action:
   /// * If the quitting member is true or if the incoming midi message
   /// is an Active Sensing message this method should immediately return.
   // uses the ScopedValueSetter class which does the following:
      // stores the current state of the isAddingFromMidiInput member
      // sets the isAddingFromMidiInput member to true
      // When the function exits it reset the value of isAddingFromMidiInput
      // member to the state it was in at the start of the function.
   void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage &message) override;

   //==============================================================================
   /// The MidiKeyboardComponent callback that responds to NoteOns. When
   /// triggered this method will create a NoteOn and route it to the
   /// sfZeroAudioProcessor for audio playback and to either the midiMessageLog
   /// or the midiPianoRoll, whichever is currently active.
   void handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber,
                     float velocity) override;

   /// The MidiKeyboardComponent callback that responds to NoteOffs. When
   /// triggered this method will create a NoteOff and route it to
   /// showMidiMessage() and playMidiMessage().
   void handleNoteOff (juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber,
                       float velocity) override;
   // handles cases when the user clicks the midikeyboard in editor or uses an
   // external midikeyboard
//   void postMessageToList (const juce::MidiMessage& message, const juce::String& source);

   // setting midi input
   void setMidiInput ();

   bool quitting;


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

   juce::Label freqLabel;
   juce::Label envLabel;
   juce::Label envAttackLabel;
   juce::Label bendLabel;
   juce::Label vibratoLabel;
   juce::Label vibratoFreqLabel;
   juce::Label vibratoGainLabel;
   juce::Label reedLabel;
   juce::Label reedStiffnessLabel;
   juce::Label bellLabel;
   juce::Label bellOpeningLabel;
   juce::Label outGainLabel;
   juce::Label gateLabel;
   juce::Label zoomLabel;


   std::vector<string> labelText = {"Freq", "Bend", "Rate", "Gain",
                                    "Envelope\nAttack", "Reed\nStiffness",
                                    "Bell\nOpening", "Out Gain", "Zoom"};


   //**************** MIDI variables ****************//
   /// An object that manages a MidiKeyboardComponent
   juce::MidiKeyboardState keyboardState;

   /// A juce component that displays an interactive midi keyboard.
   juce::MidiKeyboardComponent midiKeyboard;
   // used to find which MIDI input devices are enabled
   juce::AudioDeviceManager deviceManager;
   MidiDeviceInfo input;
   int lastInputIndex = 0;

   // indicates that MIDI data is arriving from an external source,
   // rather than mouse-clicks on the on-screen keyboard.
   bool isAddingFromMidiInput = false;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (clarinetPluginAudioProcessorEditor)
};
