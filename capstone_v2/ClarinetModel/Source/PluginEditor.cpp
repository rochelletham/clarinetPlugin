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
    : AudioProcessorEditor (&p), audioProcessor (p)
{
   // This is where our plugin’s editor size is set.
   setSize (680, 460);
   setResizable(false, false);
   quitting = false;
   setSliders();
   setLabels();

   addAndMakeVisible(audioProcessor.audioVisualizer);
   audioProcessor.audioVisualizer.setColours(Colours::black,
                                             Colours::whitesmoke.withAlpha(0.5f));
   // Add our editor as the keyboard state's listener.
   keyboardState.addListener(this);
   // Pass the keyboard state to the keyboard component.
   midiKeyboard = std::make_unique<MidiKeyboardComponent>(keyboardState, MidiKeyboardComponent::horizontalKeyboard);
   midiKeyboard->setOctaveForMiddleC(4);
   addAndMakeVisible(*midiKeyboard);
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
   // range: E3 to C7
   freqSlider.setRange(146.832, 2093.005);
   freqSlider.setValue(audioProcessor.getFreq());
   freqSlider.setSliderStyle(Slider::LinearVertical);
   // lambda function instead of overriding slider listener funct.
   // update the freq value whenever the slider changes
   freqSlider.onValueChange = [this] {
//      std::cout << "freqSlider: " << freqSlider.getValue() <<std::endl;
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
//      std::cout << "envAttackSlider: " << envAttackSlider.getValue() <<std::endl;
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
//      std::cout << "bendSlider: " << bendSlider.getValue() <<std::endl;
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
//      std::cout << "vibratoFreqSlider: " <<vibratoFreqSlider.getValue() <<std::endl;
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
//      std::cout << "vibratoGainSlider: " <<vibratoGainSlider.getValue() <<std::endl;
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
//      std::cout << "reedStiffness: " <<reedStiffnessSlider.getValue() <<std::endl;
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
//      std::cout << "bellOpening: " <<bellOpeningSlider.getValue() <<std::endl;
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
//      std::cout << "gain: " << outGainSlider.getValue() <<std::endl;
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
   addAndMakeVisible(&vibratoLabel);
   vibratoLabel.setText("Tremolo\nRate       Gain", dontSendNotification);
//   vibratoLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   vibratoLabel.setJustificationType(Justification::centredBottom);
   vibratoLabel.setSize(vibratoLabel.getWidth(), kTextHeight);

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
   zoomLabel.setSize(zoomLabel.getWidth(), kTextHeight);
//   zoomLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   zoomLabel.attachToComponent (&zoomSlider, false);
   zoomLabel.setJustificationType(Justification::centred);

}


clarinetPluginAudioProcessorEditor::~clarinetPluginAudioProcessorEditor()
{
   //Remove this component as keyboard states listener.
   keyboardState.removeListener(this);
   quitting = true;
   deviceManager.removeMidiInputDeviceCallback("", this);
}

//============================== MIDI FUNCTIONS =============================//
/** Starts listening to a MIDI input device, enabling it if necessary. */
void clarinetPluginAudioProcessorEditor::setMidiInput ()
{
   auto input_list = juce::MidiInput::getAvailableDevices();
   MidiDeviceInfo input;
   for (auto i : input_list) {
      if (i.name != "IAC Driver Bus 1") {
         input = i;
         std::cout << "setted input to " << i.name <<std::endl;
         break;
      }
   }
   if (input.name == "") {
      std::cout << "Couldn't find external midi keyboard :(" << std::endl;
   }
    if (! deviceManager.isMidiInputDeviceEnabled (input.identifier))
        deviceManager.setMidiInputDeviceEnabled (input.identifier, true);
   std::cout << "midi device enabled" << std::endl;
    deviceManager.addMidiInputDeviceCallback (input.identifier, this);
   std::cout << "added midi input device callback" << std::endl;
}

void clarinetPluginAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int chan, int note, float vel) {
   auto m = MidiMessage::noteOn (chan, note, vel);
   // convert midi to freq
   float freq = (440) * pow(2, float((note - 69) / 12.0));
   std::cout << "MIDI key: " << note << ", freq: " << freq <<std::endl;
   gateButton.setState(juce::Button::buttonDown);
   freqSlider.setValue(freq);
}

void clarinetPluginAudioProcessorEditor::handleNoteOff (juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber,
                    float velocity) {
   if (! isAddingFromMidiInput)
  {
      auto m = juce::MidiMessage::noteOff (midiChannel, midiNoteNumber);
  }
   gateButton.setState(juce::Button::buttonNormal);
}

void clarinetPluginAudioProcessorEditor::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage &message) {
   if (quitting || message.isActiveSense()) {
         return;
      }
   //blocks message thread during update
   const MessageManagerLock mmlock;
   if (message.isNoteOn() || message.isNoteOff()) {
      if (! isAddingFromMidiInput)
         keyboardState.processNextMidiEvent (message);
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
   area.reduce(12,8);
   auto sliderWidth = 60;
   area.removeFromBottom(24);
   area.removeFromTop(24);
   area.removeFromLeft(12);
   auto lineOne = area.removeFromTop(24);
   freqLabel.setBounds(lineOne.removeFromLeft(sliderWidth));
   bendLabel.setBounds(lineOne.removeFromLeft(sliderWidth));
   vibratoLabel.setBounds(lineOne.removeFromLeft(sliderWidth*2));
   envAttackLabel.setBounds(lineOne.removeFromLeft(sliderWidth));


   outGainSlider.setBounds(area.removeFromRight(sliderWidth));
   lineOne.removeFromRight(sliderWidth*2);
   bellOpeningLabel.setBounds(lineOne.removeFromRight(sliderWidth));
   reedStiffnessLabel.setBounds(lineOne.removeFromRight(sliderWidth));
   area.removeFromTop(12);
   //================== AUDIO VISUALIZER ==================//
   auto visualSpace = area.removeFromBottom(150);
   visualSpace.reduce(20,5);
   visualSpace.removeFromTop(32);

   gateButton.setBounds(visualSpace.removeFromLeft(40).withSizeKeepingCentre(40, 20));
   zoomSlider.setBounds(visualSpace.removeFromLeft(sliderWidth));
   audioProcessor.audioVisualizer.setBounds(visualSpace.withSizeKeepingCentre(
                                                               visualSpace.getWidth(),
                                                               visualSpace.getHeight()));

//   auto keySpace = visualSpace.removeFromBottom(100);
//   midiKeyboard->setBounds(keySpace);

   auto sliderGroup = area.removeFromTop(280);
   freqSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   bendSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   vibratoFreqSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   vibratoGainSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   envAttackSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));

   sliderGroup.removeFromRight(sliderWidth);
   bellOpeningSlider.setBounds(sliderGroup.removeFromRight(sliderWidth));
   reedStiffnessSlider.setBounds(sliderGroup.removeFromRight(sliderWidth));


}
