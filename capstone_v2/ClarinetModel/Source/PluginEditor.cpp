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
//   addAndMakeVisible(&pressureSlider);
//   pressureSlider.setLookAndFeel((&otherLookAndFeel));
//   pressureSlider.setSliderStyle(juce::Slider::LinearVertical);
//   pressureSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
//
//   pressureSlider.setValue(kPressureDEF);
//   pressureSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the pressure value whenever the slider changes
//   pressureSlider.onValueChange = [this] {
//      std::cout << "pressureSlider: " << pressureSlider.getValue() <<std::endl;
//      audioProcessor.setPressure(pressureSlider.getValue());
//   };
//   pressureSlider.setDoubleClickReturnValue(true, kPressureDEF);

   addAndMakeVisible(&freqSlider);
   freqSlider.setLookAndFeel((&otherLookAndFeel));
   freqSlider.setSliderStyle(juce::Slider::LinearVertical);
   freqSlider.setValue(kFreqDEF);
   // range: E3 to C7
   freqSlider.setRange(164.81, 2093.005);
   freqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the pressure value whenever the slider changes
   freqSlider.onValueChange = [this] {
      std::cout << "freqSlider: " << freqSlider.getValue() <<std::endl;
      audioProcessor.setFreq(freqSlider.getValue());
   };
   freqSlider.setDoubleClickReturnValue(true, kFreqDEF);

   addAndMakeVisible(&breathGainSlider);
   breathGainSlider.setSliderStyle(juce::Slider::LinearVertical);
   breathGainSlider.setRange(0.0, 1.0);
   breathGainSlider.setValue(kBreathGainDEF);
   breathGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   breathGainSlider.onValueChange = [this] {
      std::cout << "breathGainSlider: " << breathGainSlider.getValue() <<std::endl;
      audioProcessor.setBreathGain(breathGainSlider.getValue());
   };
   breathGainSlider.setDoubleClickReturnValue(true, kBreathGainDEF);

   addAndMakeVisible(&breathCutoffSlider);
   breathCutoffSlider.setSliderStyle(juce::Slider::LinearVertical);
   breathCutoffSlider.setRange(20.0, 20000.0);
   breathCutoffSlider.setValue(kBreathCutoffDEF);
   breathCutoffSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   breathCutoffSlider.onValueChange = [this] {
      std::cout << "breathCutoffSlider: " << breathCutoffSlider.getValue() <<std::endl;
      audioProcessor.setBreathCutoff(breathCutoffSlider.getValue());
   };
   breathCutoffSlider.setDoubleClickReturnValue(true, kBreathCutoffDEF);


   addAndMakeVisible(&vibratoFreqSlider);
   vibratoFreqSlider.setSliderStyle(juce::Slider::LinearVertical);
   vibratoFreqSlider.setRange(0.0, 10.0);
   vibratoFreqSlider.setValue(kVibratoFreqDEF);
   vibratoFreqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoFreqSlider.onValueChange = [this] {
      std::cout << "vibratoFreqSlider: " <<vibratoFreqSlider.getValue() <<std::endl;
      audioProcessor.setVibratoFreq(vibratoFreqSlider.getValue());
   };
   vibratoFreqSlider.setDoubleClickReturnValue(true, kVibratoFreqDEF);

   addAndMakeVisible(&vibratoGainSlider);
   vibratoGainSlider.setSliderStyle(juce::Slider::LinearVertical);
   vibratoGainSlider.setRange(0.0, 1.0);
   vibratoGainSlider.setValue(kVibratoGainDEF);
   vibratoGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   vibratoGainSlider.onValueChange = [this] {
      std::cout << "vibratoGainSlider: " <<vibratoGainSlider.getValue() <<std::endl;
      audioProcessor.setVibratoGain(vibratoGainSlider.getValue());
   };
   vibratoGainSlider.setDoubleClickReturnValue(true, kVibratoGainDEF);

   addAndMakeVisible(&clarinetLenSlider);
   clarinetLenSlider.setSliderStyle(juce::Slider::LinearVertical);
   clarinetLenSlider.setRange(0.0, 3.0);
   clarinetLenSlider.setValue(kClarinetLenDEF);
   clarinetLenSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   clarinetLenSlider.onValueChange = [this] {
      std::cout << "clarinet len: " <<clarinetLenSlider.getValue() <<std::endl;
      audioProcessor.setTubeLength(clarinetLenSlider.getValue());
   };
   clarinetLenSlider.setDoubleClickReturnValue(true, kClarinetLenDEF);

   addAndMakeVisible(&reedStiffnessSlider);
   reedStiffnessSlider.setSliderStyle(juce::Slider::LinearVertical);
   reedStiffnessSlider.setRange(0.0, 1.0);
   reedStiffnessSlider.setValue(kReedStiffDEF);
   reedStiffnessSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   reedStiffnessSlider.onValueChange = [this] {
      std::cout << "reedStiffness: " <<reedStiffnessSlider.getValue() <<std::endl;
      audioProcessor.setReedStiffness(reedStiffnessSlider.getValue());
   };
   reedStiffnessSlider.setDoubleClickReturnValue(true, kReedStiffDEF);

   addAndMakeVisible(&bellOpeningSlider);
   bellOpeningSlider.setSliderStyle(juce::Slider::LinearVertical);
   bellOpeningSlider.setRange(0.0, 1.0);
   bellOpeningSlider.setValue(kBellOpeningDEF);
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
   outGainSlider.setValue(kOutGainDEF);
   outGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
   // update the value whenever the slider changes
   outGainSlider.onValueChange = [this] {
      std::cout << "gain: " << outGainSlider.getValue() <<std::endl;
      audioProcessor.setOutGain(outGainSlider.getValue());
   };
   outGainSlider.setDoubleClickReturnValue(true, kOutGainDEF);


//   addAndMakeVisible(freqLabel);
//   addAndMakeVisible(&pressureLabel);
   pressureLabel.setText ("Pressure", juce::dontSendNotification);
//   pressureLabel.attachToComponent (&pressureSlider, true);
   pressureLabel.setJustificationType(juce::Justification::top);

//   addAndMakeVisible(&breathGainLabel);
   breathGainLabel.setText ("Breath Gain", juce::dontSendNotification);
//   breathGainLabel.attachToComponent (&breathGainSlider, true);
   breathGainLabel.setJustificationType(juce::Justification::top);

//   addAndMakeVisible(&breathCutoffLabel);
   breathCutoffLabel.setText ("Breath Cutoff", juce::dontSendNotification);
//   breathCutoffLabel.attachToComponent (&breathCutoffSlider, true);
   breathCutoffLabel.setJustificationType(juce::Justification::bottom);

//   addAndMakeVisible(&vibratoFreqLabel);
   vibratoFreqLabel.setText ("Vibrato Freq", juce::dontSendNotification);
//   vibratoFreqLabel.attachToComponent (&vibratoFreqSlider, true);
   vibratoFreqLabel.setJustificationType(juce::Justification::top);

//   addAndMakeVisible(&vibratoGainLabel);
   vibratoGainLabel.setText ("Vibrato Gain", juce::dontSendNotification);
//   vibratoGainLabel.attachToComponent (&vibratoGainSlider, true);
   vibratoGainLabel.setJustificationType(juce::Justification::top);

//   addAndMakeVisible(&clarinetLenLabel);
   clarinetLenLabel.setText ("Clarinet Length", juce::dontSendNotification);
//   clarinetLenLabel.attachToComponent (&clarinetLenSlider, true);
   clarinetLenLabel.setJustificationType(juce::Justification::top);

//   addAndMakeVisible(&reedStiffnessLabel);
   reedStiffnessLabel.setText ("Reed Stiffness", juce::dontSendNotification);
//   reedStiffnessLabel.attachToComponent (&reedStiffnessSlider, true);
   reedStiffnessLabel.setJustificationType(juce::Justification::top);

//   addAndMakeVisible(&bellOpeningLabel);
   bellOpeningLabel.setText ("Bell Opening", juce::dontSendNotification);
//   bellOpeningLabel.attachToComponent (&bellOpeningSlider, true);
   bellOpeningLabel.setJustificationType(juce::Justification::top);

//   addAndMakeVisible(&outGainLabel);
   outGainLabel.setText ("Gain", juce::dontSendNotification);
//   outGainLabel.attachToComponent (&outGainSlider, true);
   outGainLabel.setJustificationType(juce::Justification::bottom);

   addAndMakeVisible(audioVisualizer);

   gateButton.onClick = [this] {
     audioProcessor.setGate(gateButton.getToggleState());
   };
   addAndMakeVisible(gateButton);


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

//void clarinetPluginAudioProcessorEditor::buttonClicked(juce::Button* button) {
//   if (button == &gateButton) {
//      audioProcessor.setGate(true);
//   }
//   gateButton.addListener(this);
//}

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
   gateButton.setBounds(visualSpace.removeFromLeft(300));
   //TODO: Implement audio settings button
//   audioSettingsButton.setBounds(lineOne.removeFromLeft(118));
   lineOne.removeFromLeft(8);
   lineTwo.removeFromTop(8);

   auto sliderWidth = 50;
   outGainLabel.setBounds(bottomLine.removeFromBottom(12));
   outGainSlider.setBounds(area.removeFromRight(sliderWidth));

   auto leftGroup = area.removeFromLeft(400);
   leftGroup = leftGroup.removeFromTop(200);
   freqSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
   vibratoFreqSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
   vibratoGainSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
   breathCutoffSlider.setBounds (leftGroup.removeFromLeft (sliderWidth));
   breathGainSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));

   auto rightGroup = area.removeFromRight(400);
   rightGroup = rightGroup.removeFromTop(200);
   // TODO: centre
   clarinetLenSlider.setBounds(rightGroup.removeFromRight(sliderWidth));
   bellOpeningSlider.setBounds(rightGroup.removeFromRight(sliderWidth));
   reedStiffnessSlider.setBounds(rightGroup.removeFromRight(sliderWidth));
}
