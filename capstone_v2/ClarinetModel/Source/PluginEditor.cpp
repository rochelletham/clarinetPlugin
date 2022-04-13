/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
clarinetPluginAudioProcessorEditor::clarinetPluginAudioProcessorEditor (clarinetPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), audioVisualizer(2)
{
   // This is where our plugin’s editor size is set.
   setSize (780, 500);
   otherLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colours::red);
   setSliders();
   setLabels();

   addAndMakeVisible(audioVisualizer);

}

void clarinetPluginAudioProcessorEditor::setSliders() {
   addAndMakeVisible(&freqSlider);
   freqSlider.setLookAndFeel((&otherLookAndFeel));
   // range: E3 to C7
   // TODO: only allow semitones
   freqSlider.setRange(146.832, 2093.005);
   freqSlider.setValue(audioProcessor.getFreq());
   freqSlider.setSliderStyle(juce::Slider::LinearVertical);


   // update the pressure value whenever the slider changes
   freqSlider.onValueChange = [this] {
      std::cout << "freqSlider: " << freqSlider.getValue() <<std::endl;
      audioProcessor.setFreq(freqSlider.getValue());
   };
   freqSlider.setDoubleClickReturnValue(true, kFreqDEF);
   freqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);


   addAndMakeVisible(&envAttackSlider);
   envAttackSlider.setSliderStyle(juce::Slider::LinearVertical);
   envAttackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   envAttackSlider.setValue(audioProcessor.getEnvAttack());
   envAttackSlider.setRange(1.0, 30.0);
   envAttackSlider.onValueChange = [this] {
      std::cout << "envAttackSlider: " << envAttackSlider.getValue() <<std::endl;
      audioProcessor.setEnvAttack(envAttackSlider.getValue());
   };
   envAttackSlider.setDoubleClickReturnValue(true, kEnvDEF);

   addAndMakeVisible(&bendSlider);
   bendSlider.setSliderStyle(juce::Slider::LinearVertical);
   bendSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   bendSlider.setValue(audioProcessor.getBend());
   bendSlider.setRange(-2, 2);
   bendSlider.onValueChange = [this] {
      std::cout << "bendSlider: " << bendSlider.getValue() <<std::endl;
      audioProcessor.setBend(bendSlider.getValue());
   };
   bendSlider.setDoubleClickReturnValue(true, kBendDEF);


   addAndMakeVisible(&vibratoFreqSlider);
   vibratoFreqSlider.setSliderStyle(juce::Slider::LinearVertical);
   vibratoFreqSlider.setValue(audioProcessor.getVibratoFreq());
   vibratoFreqSlider.setRange(0.0, 10.0);
   vibratoFreqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoFreqSlider.onValueChange = [this] {
      std::cout << "vibratoFreqSlider: " <<vibratoFreqSlider.getValue() <<std::endl;
      audioProcessor.setVibratoFreq(vibratoFreqSlider.getValue());
   };
   vibratoFreqSlider.setDoubleClickReturnValue(true, kVibratoFreqDEF);

   addAndMakeVisible(&vibratoGainSlider);
   vibratoGainSlider.setSliderStyle(juce::Slider::LinearVertical);
   vibratoGainSlider.setValue(audioProcessor.getVibratoGain());
   vibratoGainSlider.setRange(0.0, 1.0);
   vibratoGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoGainSlider.onValueChange = [this] {
      std::cout << "vibratoGainSlider: " <<vibratoGainSlider.getValue() <<std::endl;
      audioProcessor.setVibratoGain(vibratoGainSlider.getValue());
   };
   vibratoGainSlider.setDoubleClickReturnValue(true, kVibratoGainDEF);

   addAndMakeVisible(&reedStiffnessSlider);
   reedStiffnessSlider.setSliderStyle(juce::Slider::LinearVertical);
   reedStiffnessSlider.setValue(audioProcessor.getReedStiffness());
   reedStiffnessSlider.setRange(0.0, 1.0);
   reedStiffnessSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   reedStiffnessSlider.onValueChange = [this] {
      std::cout << "reedStiffness: " <<reedStiffnessSlider.getValue() <<std::endl;
      audioProcessor.setReedStiffness(reedStiffnessSlider.getValue());
   };
   reedStiffnessSlider.setDoubleClickReturnValue(true, kReedStiffDEF);

   addAndMakeVisible(&bellOpeningSlider);
   bellOpeningSlider.setSliderStyle(juce::Slider::LinearVertical);
   bellOpeningSlider.setValue(audioProcessor.getBellOpening());
   bellOpeningSlider.setRange(0.0, 1.0);
   bellOpeningSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   bellOpeningSlider.onValueChange = [this] {
      std::cout << "bellOpening: " <<bellOpeningSlider.getValue() <<std::endl;
      audioProcessor.setBellOpening(bellOpeningSlider.getValue());
   };
   bellOpeningSlider.setDoubleClickReturnValue(true, kBellOpeningDEF);

   addAndMakeVisible(&outGainSlider);
   outGainSlider.setSliderStyle(juce::Slider::LinearVertical);
   outGainSlider.setRange(0.0, 1.0);
   outGainSlider.setValue(audioProcessor.getOutGain());
   outGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   outGainSlider.onValueChange = [this] {
      std::cout << "gain: " << outGainSlider.getValue() <<std::endl;
      auto gain = outGainSlider.getValue();
      // gate only toggled on when the gain is > 0
      if (gain > 0) {
         audioProcessor.setGate(true);
         audioProcessor.setOutGain(gain);
      } else {
         audioProcessor.setGate(false);
      }


   };
   outGainSlider.setDoubleClickReturnValue(true, kOutGainDEF);

}

void clarinetPluginAudioProcessorEditor::setLabels() {
   addAndMakeVisible(&freqLabel);
   freqLabel.setText("Freq", juce::dontSendNotification);
   freqLabel.attachToComponent (&freqSlider, false);
   freqLabel.setJustificationType(juce::Justification::top);

   addAndMakeVisible(&bendLabel);
   bendLabel.setText ("Bend", juce::dontSendNotification);
   bendLabel.attachToComponent (&bendSlider, false);
   bendLabel.setJustificationType(juce::Justification::top);

   addAndMakeVisible(&vibratoFreqLabel);
   vibratoFreqLabel.setText ("Vibrato", juce::dontSendNotification);
   vibratoFreqLabel.attachToComponent (&vibratoFreqSlider, false);
   vibratoFreqLabel.setJustificationType(juce::Justification::top);

   addAndMakeVisible(&vibratoGainLabel);
   vibratoGainLabel.setText ("Vibrato Gain", juce::dontSendNotification);
   vibratoGainLabel.attachToComponent (&vibratoGainSlider, false);
   vibratoGainLabel.setJustificationType(juce::Justification::top);

   addAndMakeVisible(&reedStiffnessLabel);
   reedStiffnessLabel.setText ("Reed Stiffness", juce::dontSendNotification);
   reedStiffnessLabel.attachToComponent (&reedStiffnessSlider, false);
   reedStiffnessLabel.setJustificationType(juce::Justification::top);

   addAndMakeVisible(&bellOpeningLabel);
   bellOpeningLabel.setText ("Bell Opening", juce::dontSendNotification);
   bellOpeningLabel.attachToComponent (&bellOpeningSlider, false);
   bellOpeningLabel.setJustificationType(juce::Justification::top);

   addAndMakeVisible(&outGainLabel);
   outGainLabel.setText ("Gain", juce::dontSendNotification);
   outGainLabel.attachToComponent (&outGainSlider, false);
   outGainLabel.setJustificationType(juce::Justification::bottom);

}


clarinetPluginAudioProcessorEditor::~clarinetPluginAudioProcessorEditor()
{
}

//==============================================================================
void clarinetPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
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
   visualSpace.reduce(20,5);
   audioVisualizer.setBounds(visualSpace.removeFromLeft(300));

   lineOne.removeFromTop(8);
   lineTwo.removeFromTop(8);

   auto sliderWidth = 50;
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
