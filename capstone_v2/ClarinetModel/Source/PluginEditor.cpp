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
   setSize (780, 500);

   getLookAndFeel().setColour (Slider::thumbColourId, Colours::orange);
   getLookAndFeel().setColour(Slider::trackColourId, Colours::floralwhite);
   setSliders();
   setLabels();

   addAndMakeVisible(audioProcessor.audioVisualizer);
   audioProcessor.audioVisualizer.setColours(Colours::black,
                                             Colours::whitesmoke.withAlpha(0.5f));

}

void clarinetPluginAudioProcessorEditor::setSliders() {
   addAndMakeVisible(&zoomSlider);
   zoomSlider.setLookAndFeel((&otherLookAndFeel));
   zoomSlider.setRange(100, 1024);
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
   freqSlider.setLookAndFeel((&otherLookAndFeel));
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

   // TODO: fix gate toggle
   addAndMakeVisible(&gateButton);

   gateButton.onStateChange = [this] {
      auto gateState = gateButton.getState();
      if (gateState == gateButton.buttonDown) {
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
   addAndMakeVisible(&freqLabel);
   freqLabel.setText("Freq", dontSendNotification);
   freqLabel.attachToComponent (&freqSlider, false);
   freqLabel.setJustificationType(Justification::centredTop);

   addAndMakeVisible(&bendLabel);
   bendLabel.setText ("Bend", dontSendNotification);
   bendLabel.attachToComponent (&bendSlider, false);
   bendLabel.setJustificationType(Justification::centredTop);

   addAndMakeVisible(&vibratoFreqLabel);
   vibratoFreqLabel.setText ("Vibrato", dontSendNotification);
   vibratoFreqLabel.attachToComponent (&vibratoFreqSlider, false);
   vibratoFreqLabel.setJustificationType(Justification::centredTop);

   addAndMakeVisible(&vibratoGainLabel);
   vibratoGainLabel.setText ("Vibrato Gain", dontSendNotification);
   vibratoGainLabel.attachToComponent (&vibratoGainSlider, false);
   vibratoGainLabel.setJustificationType(Justification::centredTop);

   addAndMakeVisible(&reedStiffnessLabel);
   reedStiffnessLabel.setText ("Reed Stiffness", dontSendNotification);
   reedStiffnessLabel.attachToComponent (&reedStiffnessSlider, false);
   reedStiffnessLabel.setJustificationType(Justification::centredTop);

   addAndMakeVisible(&bellOpeningLabel);
   bellOpeningLabel.setText ("Bell Opening", dontSendNotification);
   bellOpeningLabel.attachToComponent (&bellOpeningSlider, false);
   bellOpeningLabel.setJustificationType(Justification::centredTop);

   addAndMakeVisible(&envAttackLabel);
   outGainLabel.setText ("Envelope Attack", dontSendNotification);
   outGainLabel.attachToComponent (&envAttackSlider, false);
   outGainLabel.setJustificationType(Justification::centredTop);

   addAndMakeVisible(&outGainLabel);
   outGainLabel.setText ("Gain", dontSendNotification);
   outGainLabel.attachToComponent (&outGainSlider, false);
   outGainLabel.setJustificationType(Justification::centredBottom);

   addAndMakeVisible(&zoomLabel);
   zoomLabel.setText ("Zoom", dontSendNotification);
   zoomLabel.attachToComponent (&zoomSlider, false);
   zoomLabel.setJustificationType(Justification::centredBottom);

}


clarinetPluginAudioProcessorEditor::~clarinetPluginAudioProcessorEditor()
{
}

//==============================================================================
void clarinetPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll(Colours::wheat);
   g.setFont (15.0f);
}

void clarinetPluginAudioProcessorEditor::resized()
{
   // the area of the entire rectangle of the plugin window
   auto area = getLocalBounds();
   area.reduce(8,8);
   auto bottomLine = area.removeFromBottom(24);
   auto lineOne = area.removeFromTop(24);
   auto lineTwo = area.removeFromTop(32);
   auto visualSpace = area.removeFromBottom(150).removeFromLeft(600);
   auto sliderWidth = 60;
   visualSpace.reduce(20,5);
   gateButton.setBounds(visualSpace.removeFromLeft(40).withSizeKeepingCentre(40, 20));
   zoomSlider.setBounds(visualSpace.removeFromLeft(sliderWidth));
   audioProcessor.audioVisualizer.setBounds(visualSpace.withSizeKeepingCentre(
                                                               visualSpace.getWidth(),
                                                               visualSpace.getHeight()));


   lineOne.removeFromTop(8);
   lineTwo.removeFromTop(8);


   outGainLabel.setBounds(bottomLine.removeFromBottom(12));
   outGainSlider.setBounds(area.removeFromRight(sliderWidth));

   auto leftGroup = area.removeFromLeft(400);
   leftGroup = leftGroup.removeFromTop(200);
   freqSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
   bendSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
   vibratoFreqSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
   vibratoGainSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
   envAttackSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));

   auto rightGroup = area.removeFromRight(400);
   rightGroup = rightGroup.removeFromTop(200);

   clarinetLenSlider.setBounds(rightGroup.removeFromRight(sliderWidth));
   bellOpeningSlider.setBounds(rightGroup.removeFromRight(sliderWidth));
   reedStiffnessSlider.setBounds(rightGroup.removeFromRight(sliderWidth));
}
