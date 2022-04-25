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
   setSize (660, 460);
   setResizable(true, true);
   setResizeLimits(660, 460, 660*5, 460*5);
   setWantsKeyboardFocus(true);
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

   setMidiInput(1);

}


//TODO: 1) midi -- sliderval change without changing sound --> lambda changes freq
//TODO: look at slider listener ^
//TODO: or convert midi to freq (already have lambda callbacks)
void clarinetPluginAudioProcessorEditor::setSliders() {
   addAndMakeVisible(&zoomSlider);
   zoomSlider.setRange(50, 1024);
   zoomSlider.setSliderStyle(Slider::LinearVertical);
   zoomSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                              kTextWidth, kTextHeight);
   zoomSlider.onValueChange = [this] {
      std::cout << "zoomSlider: " << zoomSlider.getValue() <<std::endl;
      audioProcessor.audioVisualizer.setBufferSize(zoomSlider.getValue());
   };
   zoomSlider.setNumDecimalPlacesToDisplay(2);
   zoomSlider.setColour(Slider::textBoxOutlineColourId,
                        Colours::transparentWhite);

   addAndMakeVisible(&freqSlider);
   // range: E3 to C7
   freqSlider.setRange(146.832, 2093.005);
   freqSlider.setValue(audioProcessor.getFreq());
   freqSlider.setSliderStyle(Slider::LinearVertical);
   freqSlider.setColour(Slider::textBoxOutlineColourId,
                        Colours::transparentWhite);
   // lambda function instead of overriding slider listener funct.
   // update the freq value whenever the slider changes
   freqSlider.onValueChange = [this] {
      std::cout << "freqSlider: " << freqSlider.getValue() <<std::endl;
      audioProcessor.setFreq(freqSlider.getValue());
   };
   freqSlider.setDoubleClickReturnValue(true, kFreqDEF);
   freqSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                              kTextWidth, kTextHeight);
   freqSlider.setNumDecimalPlacesToDisplay(2);

   // GATE BUTTON
   addAndMakeVisible(&gateButton);
   gateButton.onStateChange = [this] {
      auto gateState = gateButton.getState();
      if (gateState == gateButton.buttonDown || KeyPress::isKeyCurrentlyDown(KeyPress::spaceKey)) {
             audioProcessor.setGate(true);
      } else {
         audioProcessor.setGate(false);
      }
   };
   gateButton.setButtonText("gate");

   addAndMakeVisible(&envAttackSlider);
   envAttackSlider.setSliderStyle(Slider::LinearVertical);
   envAttackSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   envAttackSlider.setValue(audioProcessor.getEnvAttack());
   envAttackSlider.setRange(1.0, 30.0);
   envAttackSlider.onValueChange = [this] {
      std::cout << "envAttackSlider: " << envAttackSlider.getValue() <<std::endl;
      audioProcessor.setEnvAttack(envAttackSlider.getValue());
   };
   envAttackSlider.setDoubleClickReturnValue(true, kEnvDEF);
   envAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kTextHeight);
   envAttackSlider.setNumDecimalPlacesToDisplay(2);
   envAttackSlider.setColour(Slider::textBoxOutlineColourId,
                             Colours::transparentWhite);

   addAndMakeVisible(&bendSlider);
   bendSlider.setSliderStyle(Slider::LinearVertical);
   bendSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   bendSlider.setValue(audioProcessor.getBend());
   bendSlider.setRange(-2, 2);
   bendSlider.onValueChange = [this] {
      std::cout << "bendSlider: " << bendSlider.getValue() <<std::endl;
      audioProcessor.setBend(bendSlider.getValue());
   };
   bendSlider.setDoubleClickReturnValue(true, kBendDEF);
   bendSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kTextHeight);
   bendSlider.setNumDecimalPlacesToDisplay(2);
   bendSlider.setColour(Slider::textBoxOutlineColourId,
                        Colours::transparentWhite);

   addAndMakeVisible(&vibratoFreqSlider);
   vibratoFreqSlider.setSliderStyle(Slider::LinearVertical);
   vibratoFreqSlider.setValue(audioProcessor.getVibratoFreq());
   vibratoFreqSlider.setRange(0.0, 10.0);
   vibratoFreqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoFreqSlider.onValueChange = [this] {
      std::cout << "vibratoFreqSlider: " <<vibratoFreqSlider.getValue() <<std::endl;
      audioProcessor.setVibratoFreq(vibratoFreqSlider.getValue());
   };
   vibratoFreqSlider.setDoubleClickReturnValue(true, kVibratoFreqDEF);
   vibratoFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kTextHeight);
   vibratoFreqSlider.setNumDecimalPlacesToDisplay(2);
   vibratoFreqSlider.setColour(Slider::textBoxOutlineColourId,
                               Colours::transparentWhite);

   addAndMakeVisible(&vibratoGainSlider);
   vibratoGainSlider.setSliderStyle(Slider::LinearVertical);
   vibratoGainSlider.setValue(audioProcessor.getVibratoGain());
   vibratoGainSlider.setRange(0.0, 1.0);
   vibratoGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoGainSlider.onValueChange = [this] {
      std::cout << "vibratoGainSlider: " <<vibratoGainSlider.getValue() <<std::endl;
      audioProcessor.setVibratoGain(vibratoGainSlider.getValue());
   };
   vibratoGainSlider.setDoubleClickReturnValue(true, kVibratoGainDEF);
   vibratoGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kTextHeight);
   vibratoGainSlider.setNumDecimalPlacesToDisplay(2);
   vibratoGainSlider.setColour(Slider::textBoxOutlineColourId,
                               Colours::transparentWhite);

   addAndMakeVisible(&reedStiffnessSlider);
   reedStiffnessSlider.setSliderStyle(Slider::LinearVertical);
   reedStiffnessSlider.setValue(audioProcessor.getReedStiffness());
   reedStiffnessSlider.setRange(0.0, 1.0);
   reedStiffnessSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   reedStiffnessSlider.onValueChange = [this] {
      std::cout << "reedStiffness: " <<reedStiffnessSlider.getValue() <<std::endl;
      audioProcessor.setReedStiffness(reedStiffnessSlider.getValue());
   };
   reedStiffnessSlider.setDoubleClickReturnValue(true, kReedStiffDEF);
   reedStiffnessSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kTextHeight);
   reedStiffnessSlider.setNumDecimalPlacesToDisplay(2);
   reedStiffnessSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);


   addAndMakeVisible(&bellOpeningSlider);
   bellOpeningSlider.setSliderStyle(Slider::LinearVertical);
   bellOpeningSlider.setValue(audioProcessor.getBellOpening());
   bellOpeningSlider.setRange(0.0, 1.0);
   bellOpeningSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   bellOpeningSlider.onValueChange = [this] {
      std::cout << "bellOpening: " <<bellOpeningSlider.getValue() <<std::endl;
      audioProcessor.setBellOpening(bellOpeningSlider.getValue());
   };
   bellOpeningSlider.setDoubleClickReturnValue(true, kBellOpeningDEF);
   bellOpeningSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kTextHeight);
   bellOpeningSlider.setNumDecimalPlacesToDisplay(2);
   bellOpeningSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);

   addAndMakeVisible(&outGainSlider);
   outGainSlider.setSliderStyle(Slider::LinearVertical);
   outGainSlider.setRange(0.0, 1.0);
   outGainSlider.setValue(audioProcessor.getOutGain());
   outGainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   outGainSlider.onValueChange = [this] {
      std::cout << "gain: " << outGainSlider.getValue() <<std::endl;
      auto gain = outGainSlider.getValue();
      audioProcessor.setOutGain(gain);
   };
   outGainSlider.setDoubleClickReturnValue(true, kOutGainDEF);
   outGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false,
                                   kTextWidth, kTextHeight);
   outGainSlider.setNumDecimalPlacesToDisplay(2);
   outGainSlider.setColour(Slider::textBoxOutlineColourId, Colours::transparentWhite);

}

void clarinetPluginAudioProcessorEditor::setLabels() {
   // TODO: add unit labels for the text
   // TODO: set label to width of text, height 24
   // TODO: set to widest text length (getstringwidth)
   // TODO: :draw rectangles around the labels for dimensions

   addAndMakeVisible(&TEST);
   TEST.setText("TEST", dontSendNotification);

   addAndMakeVisible(&freqLabel);
   freqLabel.setText("Freq", dontSendNotification);
   float freqStrWidth = vibratoFreqLabel.getFont().getStringWidthFloat("Freq");
   // width, height
   freqLabel.setSize(freqStrWidth, 40);
   freqLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   freqLabel.attachToComponent (&freqSlider, false);
   freqLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&bendLabel);
   bendLabel.setText ("Bend", dontSendNotification);
   float bendStrWidth = bendLabel.getFont().getStringWidthFloat("Bend");
   bendLabel.setSize(bendStrWidth, 40);
   bendLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   bendLabel.attachToComponent (&bendSlider, false);
   bendLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&vibratoFreqLabel);
   vibratoFreqLabel.setText ("Rate", dontSendNotification);
   float vibStrWidth = vibratoFreqLabel.getFont().getStringWidthFloat("Rate");
   vibratoFreqLabel.setSize(vibStrWidth, 40);
   vibratoFreqLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   vibratoFreqLabel.attachToComponent (&vibratoFreqSlider, false);
   vibratoFreqLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&vibratoGainLabel);
   vibratoGainLabel.setText ("Gain", dontSendNotification);
   float vibGainStrWidth = vibratoGainLabel.getFont().getStringWidthFloat("Gain");
   vibratoGainLabel.setSize(vibGainStrWidth, 40);
   vibratoGainLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   vibratoGainLabel.attachToComponent (&vibratoGainSlider, false);
   vibratoGainLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&reedStiffnessLabel);
   reedStiffnessLabel.setText ("Reed\nStiffness", dontSendNotification);
   float reedStrWidth = reedStiffnessLabel.getFont().getStringWidthFloat("Reed\nStiffness");
   float reedStrHeight = reedStiffnessLabel.getFont().getHeight();
   kTextHeight = reedStrHeight;
   std::cout << kTextHeight << std::endl;
   reedStiffnessLabel.setSize(reedStrWidth, reedStrHeight);
   reedStiffnessLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   reedStiffnessLabel.attachToComponent (&reedStiffnessSlider, false);
   reedStiffnessLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&bellOpeningLabel);
   bellOpeningLabel.setText ("Bell\nOpening", dontSendNotification);
   float bellStrWidth = bellOpeningLabel.getFont().getStringWidthFloat("Bell\nOpening");
   bellOpeningLabel.setSize(bellStrWidth, 40);
   bellOpeningLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   bellOpeningLabel.attachToComponent (&bellOpeningSlider, false);
   bellOpeningLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&envAttackLabel);
   envAttackLabel.setText ("Envelope\nAttack", dontSendNotification);
   float envStrWidth = envAttackLabel.getFont().getStringWidthFloat("Envelope\nAttack");
   envAttackLabel.setSize(envStrWidth, 40);
   envAttackLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   envAttackLabel.attachToComponent (&envAttackSlider, false);
   envAttackLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&outGainLabel);
   outGainLabel.setText ("Gain", dontSendNotification);
   float gainStrWidth = outGainLabel.getFont().getStringWidthFloat("Gain");
   outGainLabel.setSize(gainStrWidth, 40);
   outGainLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   outGainLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
   outGainLabel.attachToComponent (&outGainSlider, false);
   outGainLabel.setJustificationType(Justification::centred);

   addAndMakeVisible(&zoomLabel);
   zoomLabel.setText ("Zoom", dontSendNotification);
   float zoomStrWidth = zoomLabel.getFont().getStringWidthFloat("Zoom");
   zoomLabel.setSize(zoomStrWidth, 40);
   zoomLabel.setColour(juce::Label::outlineColourId,  juce::Colours::white);
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
void clarinetPluginAudioProcessorEditor::setMidiInput (int index)
{
    auto input = juce::MidiInput::getAvailableDevices()[index];
   std::cout << "Got input!: " << input.name <<std::endl;
    if (! deviceManager.isMidiInputDeviceEnabled (input.identifier))
        deviceManager.setMidiInputDeviceEnabled (input.identifier, true);

    deviceManager.addMidiInputDeviceCallback (input.identifier, this);
}

void clarinetPluginAudioProcessorEditor::handleNoteOn(MidiKeyboardState*, int chan, int note, float vel) {
   auto m = MidiMessage::noteOn (chan, note, vel);
   // convert midi to freq
   float freq = (440) * pow(2, float((note - 69) / 12.0));
   std::cout << "midi key: " << note << ", freq: " << freq <<std::endl;
   gateButton.setState(juce::Button::buttonDown);
   freqSlider.setValue(freq);


}

void clarinetPluginAudioProcessorEditor::handleNoteOff (juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber,
                    float velocity) {
   if (! isAddingFromMidiInput)
  {
      auto m = juce::MidiMessage::noteOff (midiChannel, midiNoteNumber);
//      m.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001);
//      postMessageToList (m, "On-Screen Keyboard");
  }
   gateButton.setState(juce::Button::buttonNormal);
}

void clarinetPluginAudioProcessorEditor::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage &message) {
   if (quitting || message.isActiveSense()) {
         return;
      }

   const juce::ScopedValueSetter<bool> scopedInputFlag (isAddingFromMidiInput, true);
   keyboardState.processNextMidiEvent (message);
//   postMessageToList (message, source->getName());

   //blocks message thread during update
//   const MessageManagerLock mmlock;
//   if (message.isNoteOn() || message.isNoteOff()) {if (! isAddingFromMidiInput)
//      keyboardState.processNextMidiEvent (message);
//   }
}


//void clarinetPluginAudioProcessorEditor::postMessageToList (const juce::MidiMessage& message,
//                                                            const juce::String& source) {
//  (new IncomingMessageCallback (this, message, source))->post();
//}
//==============================================================================
void clarinetPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
   g.setFont (15.0f);

}

void clarinetPluginAudioProcessorEditor::resized()
{
   // the area of the entire rectangle of the plugin window
   auto area = getLocalBounds();
   area.reduce(8,8);
   auto sliderWidth = 60;
   auto bottomLine = area.removeFromBottom(24);
   area.removeFromTop(48);

   outGainLabel.setBounds(bottomLine.removeFromBottom(12));
   outGainSlider.setBounds(area.removeFromRight(sliderWidth));

   //================== AUDIO VISUALIZER ==================//
   auto visualSpace = area.removeFromBottom(150);
   visualSpace.reduce(20,5);
   visualSpace.removeFromTop(32);

   gateButton.setBounds(visualSpace.removeFromLeft(40).withSizeKeepingCentre(40, 20));
   zoomSlider.setBounds(visualSpace.removeFromLeft(sliderWidth));
   audioProcessor.audioVisualizer.setBounds(visualSpace.withSizeKeepingCentre(
                                                               visualSpace.getWidth(),
                                                               visualSpace.getHeight()));
//   midiKeyboard->setBounds(keySpace);
   auto keySpace = visualSpace.removeFromBottom(100);
   TEST.setBounds(keySpace);

   auto sliderGroup = area.removeFromTop(400);
   freqSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   bendSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   vibratoFreqSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   vibratoGainSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));
   envAttackSlider.setBounds(sliderGroup.removeFromLeft (sliderWidth));

   sliderGroup.removeFromRight(sliderWidth);
   bellOpeningSlider.setBounds(sliderGroup.removeFromRight(sliderWidth));
   reedStiffnessSlider.setBounds(sliderGroup.removeFromRight(sliderWidth));
   sliderGroup.removeFromBottom(48);


}
