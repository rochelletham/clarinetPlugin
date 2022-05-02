/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;
//==============================================================================
clarinetPluginAudioProcessorEditor::clarinetPluginAudioProcessorEditor (clarinetPluginAudioProcessor& p)
    : midiKeyboard (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
      AudioProcessorEditor (&p), audioProcessor (p)
{
   // This is where our plugin’s editor size is set.
   setSize (680, 480);
   setResizable(false, false);
   quitting = false;
   setSliders();
   setLabels();

   addAndMakeVisible(audioProcessor.audioVisualizer);
   audioProcessor.audioVisualizer.setColours(Colours::black,
                                             Colours::whitesmoke.withAlpha(0.5f));
   // Add our editor as the keyboard state's listener.
   keyboardState.addListener(this);
   // set the range to concert G1 to C7 (displays as G#0 to C6 on screen)
   midiKeyboard.setAvailableRange(31, 96);
   addAndMakeVisible(midiKeyboard);
   // Pass the keyboard state to the keyboard component.
   keyboardState.addListener(this);
   setMidiInput();

}

void clarinetPluginAudioProcessorEditor::setSliders() {
   addAndMakeVisible(&zoomSlider);
   zoomSlider.setRange(50, 1024);
   zoomSlider.setSliderStyle(Slider::LinearVertical);
   zoomSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                              kTextWidth, kNumHeight);
   zoomSlider.onValueChange = [this] {
//      std::cout << "zoomSlider: " << zoomSlider.getValue() <<std::endl;
      audioProcessor.audioVisualizer.setBufferSize(zoomSlider.getValue());
   };
   zoomSlider.setNumDecimalPlacesToDisplay(2);

   addAndMakeVisible(&freqSlider);
   // range: G#1 to C6
   freqSlider.setRange(51.91, 2093.005);
   freqSlider.setValue(audioProcessor.getFreq());
   freqSlider.setSliderStyle(Slider::LinearVertical);
   // lambda function instead of overriding slider listener funct.
   // update the freq value whenever the slider changes
   freqSlider.onValueChange = [this] {
      audioProcessor.setFreq(freqSlider.getValue());
   };
   freqSlider.setDoubleClickReturnValue(true, kFreqDEF);
   freqSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                              kTextWidth, kNumHeight);
   freqSlider.setNumDecimalPlacesToDisplay(2);

   // GATE BUTTON
   addAndMakeVisible(&gateButton);
   gateButton.onStateChange = [this] {
      auto gateState = gateButton.getState();
      if (gateState == gateButton.buttonDown) {
         audioProcessor.setGate(true);
      } else {
         audioProcessor.setGate(false);
      }
   };
   gateButton.setButtonText(" gate ");

   addAndMakeVisible(&envAttackSlider);
   envAttackSlider.setSliderStyle(Slider::LinearVertical);
   envAttackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   envAttackSlider.setValue(audioProcessor.getEnvAttack());
   envAttackSlider.setRange(1.0, 30.0);
   envAttackSlider.onValueChange = [this] {
      audioProcessor.setEnvAttack(envAttackSlider.getValue());
   };
   envAttackSlider.setDoubleClickReturnValue(true, kEnvDEF);
   envAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kNumHeight);
   envAttackSlider.setNumDecimalPlacesToDisplay(2);

   addAndMakeVisible(&bendSlider);
   bendSlider.setSliderStyle(Slider::LinearVertical);
   bendSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   bendSlider.setValue(audioProcessor.getBend());
   bendSlider.setRange(-2, 2);
   bendSlider.onValueChange = [this] {
      audioProcessor.setBend(bendSlider.getValue());
   };
   bendSlider.setDoubleClickReturnValue(true, kBendDEF);
   bendSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kNumHeight);
   bendSlider.setNumDecimalPlacesToDisplay(2);


   addAndMakeVisible(&vibratoFreqSlider);
   vibratoFreqSlider.setSliderStyle(Slider::LinearVertical);
   vibratoFreqSlider.setValue(audioProcessor.getVibratoFreq());
   vibratoFreqSlider.setRange(0.0, 10.0);
   vibratoFreqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoFreqSlider.onValueChange = [this] {
      audioProcessor.setVibratoFreq(vibratoFreqSlider.getValue());
   };
   vibratoFreqSlider.setDoubleClickReturnValue(true, kVibratoFreqDEF);
   vibratoFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kNumHeight);
   vibratoFreqSlider.setNumDecimalPlacesToDisplay(2);

   addAndMakeVisible(&vibratoGainSlider);
   vibratoGainSlider.setSliderStyle(Slider::LinearVertical);
   vibratoGainSlider.setValue(audioProcessor.getVibratoGain());
   vibratoGainSlider.setRange(0.0, 1.0);
   vibratoGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoGainSlider.onValueChange = [this] {
      audioProcessor.setVibratoGain(vibratoGainSlider.getValue());
   };
   vibratoGainSlider.setDoubleClickReturnValue(true, kVibratoGainDEF);
   vibratoGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kNumHeight);
   vibratoGainSlider.setNumDecimalPlacesToDisplay(2);

   addAndMakeVisible(&reedStiffnessSlider);
   reedStiffnessSlider.setSliderStyle(Slider::LinearVertical);
   reedStiffnessSlider.setValue(audioProcessor.getReedStiffness());
   reedStiffnessSlider.setRange(0.0, 1.0);
   reedStiffnessSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   reedStiffnessSlider.onValueChange = [this] {
      audioProcessor.setReedStiffness(reedStiffnessSlider.getValue());
   };
   reedStiffnessSlider.setDoubleClickReturnValue(true, kReedStiffDEF);
   reedStiffnessSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kNumHeight);
   reedStiffnessSlider.setNumDecimalPlacesToDisplay(2);

   addAndMakeVisible(&bellOpeningSlider);
   bellOpeningSlider.setSliderStyle(Slider::LinearVertical);
   bellOpeningSlider.setValue(audioProcessor.getBellOpening());
   bellOpeningSlider.setRange(0.0, 1.0);
   bellOpeningSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   bellOpeningSlider.onValueChange = [this] {
      audioProcessor.setBellOpening(bellOpeningSlider.getValue());
   };
   bellOpeningSlider.setDoubleClickReturnValue(true, kBellOpeningDEF);
   bellOpeningSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kNumHeight);
   bellOpeningSlider.setNumDecimalPlacesToDisplay(2);


   addAndMakeVisible(&outGainSlider);
   outGainSlider.setSliderStyle(Slider::LinearVertical);
   outGainSlider.setRange(0.0, 1.0);
   outGainSlider.setValue(audioProcessor.getOutGain());
   outGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   outGainSlider.onValueChange = [this] {
      auto gain = outGainSlider.getValue();
      audioProcessor.setOutGain(gain);
   };
   outGainSlider.setDoubleClickReturnValue(true, kOutGainDEF);
   outGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kNumHeight);
   outGainSlider.setNumDecimalPlacesToDisplay(2);

}

void clarinetPluginAudioProcessorEditor::setLabels() {
   // TODO: add unit labels for the text
   addAndMakeVisible(&tremoloLabel);
   tremoloLabel.setText("Tremolo\nRate       Gain", dontSendNotification);
//   tremoloLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   tremoloLabel.setJustificationType(Justification::centredBottom);
   tremoloLabel.setSize(tremoloLabel.getWidth(), kTextHeight);

   addAndMakeVisible(&freqLabel);
   freqLabel.setText("Freq", dontSendNotification);
   freqLabel.setSize(freqLabel.getWidth(), kTextHeight);
//   freqLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   freqLabel.setJustificationType(Justification::centredBottom);

   addAndMakeVisible(&bendLabel);
   bendLabel.setText ("Bend", dontSendNotification);
   bendLabel.setSize(bendLabel.getWidth(), kTextHeight);
//   bendLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   bendLabel.setJustificationType(Justification::centredBottom);

   addAndMakeVisible(&reedStiffnessLabel);
   reedStiffnessLabel.setText ("Reed Stiffness", dontSendNotification);
   reedStiffnessLabel.setSize(reedStiffnessLabel.getWidth(), kTextHeight);
//   reedStiffnessLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   reedStiffnessLabel.setJustificationType(Justification::centredBottom);

   addAndMakeVisible(&bellOpeningLabel);
   bellOpeningLabel.setText ("Bell Opening", dontSendNotification);
   bellOpeningLabel.setSize(bellOpeningLabel.getWidth(), kTextHeight);
//   bellOpeningLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   bellOpeningLabel.setJustificationType(Justification::centredBottom);


   addAndMakeVisible(&envAttackLabel);
   envAttackLabel.setText ("Envelope Attack", dontSendNotification);
   envAttackLabel.setSize(envAttackLabel.getWidth(), kTextHeight);
//   envAttackLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   envAttackLabel.setJustificationType(Justification::centredBottom);

   addAndMakeVisible(&outGainLabel);
   outGainLabel.setText ("Gain", dontSendNotification);
   outGainLabel.setSize(outGainLabel.getWidth(), kTextHeight);
   outGainLabel.attachToComponent(&outGainSlider, false);
//   outGainLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   outGainLabel.setJustificationType(Justification::centredBottom);

   addAndMakeVisible(&zoomLabel);
   zoomLabel.setText ("Zoom", dontSendNotification);
   zoomLabel.setSize(zoomLabel.getWidth(), kNumHeight);
//   zoomLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   zoomLabel.setJustificationType(Justification::centred);

}


clarinetPluginAudioProcessorEditor::~clarinetPluginAudioProcessorEditor()
{
   //Remove this component as keyboard states listener.
   keyboardState.removeListener(this);
   quitting = true;
   deviceManager.removeMidiInputDeviceCallback(input.name, this);
}

//============================== MIDI FUNCTIONS =============================//
/** Starts listening to a MIDI input device, enabling it if necessary. */
void clarinetPluginAudioProcessorEditor::setMidiInput ()
{
   auto input_list = juce::MidiInput::getAvailableDevices();
   for (auto i : input_list) {
      if (i.name != "IAC Driver Bus 1") {
         input = i;
         std::cout << "setted input to " << i.name <<std::endl;
         break;
      }
   }
   if (input.name == "") {
      std::cout << "Couldn't find external midi keyboard :(" << std::endl;
   //   enables the device if it is currently disabled
   } else if (! deviceManager.isMidiInputDeviceEnabled (input.identifier)) {
        deviceManager.setMidiInputDeviceEnabled (input.identifier, true);
        std::cout << "midi device enabled" << std::endl;
   }

   deviceManager.addMidiInputDeviceCallback (input.identifier, this);
   std::cout << "added midi input device callback" << std::endl;

}

void clarinetPluginAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int chan, int note, float vel) {
   auto m = MidiMessage::noteOn (chan, note, vel);
   // convert MIDI num to freq. A4 (MIDI key 69 = 440 Hz)
   float freq = (440) * pow(2, float((note - 69) / 12.0));
   std::cout << "MIDI key: " << note << ", freq: " << freq << " vel: " << vel << " chan: " << chan << std::endl;
   gateButton.setState(juce::Button::buttonDown);
   freqSlider.setValue(freq);
}

void clarinetPluginAudioProcessorEditor::handleNoteOff (juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber,
                    float velocity) {
   if (!isAddingFromMidiInput)
  {
      auto m = juce::MidiMessage::noteOff (midiChannel, midiNoteNumber);
      gateButton.setState(juce::Button::buttonNormal);
  }

}

void clarinetPluginAudioProcessorEditor::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage &message) {
   if (quitting || message.isActiveSense()) {
         return;
      }
   //blocks message thread during update
   const MessageManagerLock mmlock;
   // when a MIDI key is pressed or lifted
   if (message.isNoteOn() || message.isNoteOff()) {
      if (! isAddingFromMidiInput)
         keyboardState.processNextMidiEvent (message);
   }
   // when a MIDI pitch wheel receives value changes
   // use this for mapping: https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another
   if (message.isPitchWheel()) {
      auto input = message.getPitchWheelValue();
      auto PITCH_WHEEL_MAX = 16383;
      auto PITCH_WHEEL_MIN = 0;
      // pitch wheel at center means 0 bend
      // auto PITCH_WHEEL_CENTER = 8192;
      auto sliderRange = bendSlider.getMaximum() - bendSlider.getMinimum();
      // get the ratio of bendslider range to the MIDIkeyboard pitchwheel range
      auto slope = (sliderRange) / (PITCH_WHEEL_MAX-PITCH_WHEEL_MIN);
      // slider range: [-2,2] where 0 means 0 bend. need to translate bend down by 2.
      auto bend = slope * (input - PITCH_WHEEL_MIN) -2;
      bendSlider.setValue(bend);
   }

   // currently, the MIDI controller controls the reed stiffness slider
   if (message.isController()) {
      auto input = message.getControllerValue();
      auto CONTROLLER_MAX = 127;
      auto CONTROLLER_MIN = 0;
      auto sliderRange = reedStiffnessSlider.getMaximum() - reedStiffnessSlider.getMinimum();
      // get the ratio of bendslider range to the MIDIkeyboard pitchwheel range
      auto slope = (sliderRange) / (CONTROLLER_MAX-CONTROLLER_MIN);
      auto reed_param = slope * (input - CONTROLLER_MIN);
      reedStiffnessSlider.setValue(reed_param);
   }
}


//==============================================================================
void clarinetPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
   g.setFont (kTextHeight);

}

void clarinetPluginAudioProcessorEditor::resized()
{
   // the area of the entire rectangle of the plugin window
   auto area = getLocalBounds();
   area.reduce(12,0);
   auto sliderWidth = 60;
   area.removeFromTop(24);
   area.removeFromLeft(12);
   auto keyboardSpace = area.removeFromBottom(70);
   // had issues with extra white spacing
   keyboardSpace.removeFromLeft(midiKeyboard.getKeyWidth()*2);
   keyboardSpace.removeFromRight(midiKeyboard.getKeyWidth()*2+36);
   midiKeyboard.setBounds(keyboardSpace.removeFromLeft(midiKeyboard.getTotalKeyboardWidth()));
   area.removeFromBottom(24);
   auto lineOne = area.removeFromTop(24);
   lineOne.removeFromLeft(sliderWidth);
   freqLabel.setBounds(lineOne.removeFromLeft(sliderWidth));
   bendLabel.setBounds(lineOne.removeFromLeft(sliderWidth));
   lineOne.removeFromLeft(sliderWidth*0.5);
   tremoloLabel.setBounds(lineOne.removeFromLeft(sliderWidth*2));
   lineOne.removeFromLeft(sliderWidth*0.5);
   envAttackLabel.setBounds(lineOne.removeFromLeft(sliderWidth));

   auto gainSliderArea = area.removeFromRight(sliderWidth);
   gainSliderArea.removeFromBottom(12);
   outGainSlider.setBounds(gainSliderArea);

   lineOne.removeFromRight(sliderWidth);
   bellOpeningLabel.setBounds(lineOne.removeFromLeft(sliderWidth));
   reedStiffnessLabel.setBounds(lineOne.removeFromLeft(sliderWidth));
   area.removeFromTop(12);
   //================== AUDIO VISUALIZER ==================//
   auto visualSpace = area.removeFromBottom(150);
   visualSpace.removeFromTop(32);
   visualSpace.removeFromRight(30);

   gateButton.setBounds(visualSpace.removeFromLeft(40).withSizeKeepingCentre(40, 20));
   auto zoomSliderSpace = visualSpace.removeFromLeft(sliderWidth);
   zoomLabel.setBounds(zoomSliderSpace.removeFromTop(kNumHeight));
   zoomSlider.setBounds(zoomSliderSpace.removeFromLeft(sliderWidth));
   audioProcessor.audioVisualizer.setBounds(visualSpace.withSizeKeepingCentre(
                                                               visualSpace.getWidth(),
                                                               visualSpace.getHeight()));

   auto sliderGroup = area.removeFromTop(280);
   sliderGroup.removeFromLeft(sliderWidth);
   freqSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   bendSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   sliderGroup.removeFromLeft(sliderWidth*0.5);
   vibratoFreqSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   vibratoGainSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   sliderGroup.removeFromLeft(sliderWidth*0.5);
   envAttackSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));

   bellOpeningSlider.setBounds(sliderGroup.removeFromLeft(sliderWidth));
   reedStiffnessSlider.setBounds(sliderGroup.removeFromLeft(sliderWidth));


}
