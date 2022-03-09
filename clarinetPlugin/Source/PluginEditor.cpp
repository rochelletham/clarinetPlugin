/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "dsp-faust/DspFaust.h"

//==============================================================================
clarinetPluginAudioProcessorEditor::clarinetPluginAudioProcessorEditor (clarinetPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
   // This is where our plugin’s editor size is set.
   setSize (600, 600);

   addAndMakeVisible(&pressureSlider);
   pressureSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
   pressureSlider.setRange(0.0, 1.0);
   pressureSlider.setValue(0.5);
   pressureSlider.hideTextBox(true);
   // update the pressure value whenever the slider changes
   pressureSlider.onValueChange = [this] {
      audioProcessor.setPressure(pressureSlider.getValue());
   };

//   addAndMakeVisible(&breathGainSlider);
//   breathGainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//   breathGainSlider.setRange(0.0, 1.0);
//   breathGainSlider.setValue(0.5);
//   // update the value whenever the slider changes
//   breathGainSlider.onValueChange = [this] {
//      audioProcessor.setBreathGain(breathGainSlider.getValue());
//   };
//
   addAndMakeVisible(&breathCutoffSlider);
   breathCutoffSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
   breathCutoffSlider.setRange(0.0, 1.0);
   breathCutoffSlider.setValue(0.5);
   // update the value whenever the slider changes
   breathCutoffSlider.onValueChange = [this] {
      audioProcessor.setBreathCutoff(breathCutoffSlider.getValue());
   };
//
//   addAndMakeVisible(&vibratoFreqSlider);
//   vibratoFreqSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//   vibratoFreqSlider.setRange(0.0, 1.0);
//   vibratoFreqSlider.setValue(0.5);
//   // update the value whenever the slider changes
//   vibratoFreqSlider.onValueChange = [this] {
//      audioProcessor.setVibratoFreq(vibratoFreqSlider.getValue());
//   };
//
//   addAndMakeVisible(&vibratoGainSlider);
//   vibratoFreqSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//   vibratoGainSlider.setRange(0.0, 1.0);
//   vibratoGainSlider.setValue(0.5);
//   // update the value whenever the slider changes
//   vibratoGainSlider.onValueChange = [this] {
//      audioProcessor.setVibratoGain(vibratoGainSlider.getValue());
//   };
//
//   addAndMakeVisible(&clarinetLenSlider);
//   clarinetLenSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//   clarinetLenSlider.setRange(0.0, 1.0);
//   clarinetLenSlider.setValue(0.5);
//   // update the value whenever the slider changes
//   clarinetLenSlider.onValueChange = [this] {
//      audioProcessor.setTubeLength(clarinetLenSlider.getValue());
//   };
//
//   addAndMakeVisible(&reedStiffnessSlider);
//   reedStiffnessSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//   reedStiffnessSlider.setRange(0.0, 1.0);
//   reedStiffnessSlider.setValue(0.5);
//   // update the value whenever the slider changes
//   reedStiffnessSlider.onValueChange = [this] {
//      audioProcessor.setReedStiffness(reedStiffnessSlider.getValue());
//   };
//
//   addAndMakeVisible(&bellOpeningSlider);
//   bellOpeningSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//   bellOpeningSlider.setRange(0.0, 1.0);
//   bellOpeningSlider.setValue(0.5);
//   // update the value whenever the slider changes
//   bellOpeningSlider.onValueChange = [this] {
//      audioProcessor.setBellOpening(bellOpeningSlider.getValue());
//   };
//
//   addAndMakeVisible(&outGainSlider);
//   outGainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//   outGainSlider.setRange(0.0, 1.0);
//   outGainSlider.setValue(0.5);
//   // update the value whenever the slider changes
//   outGainSlider.onValueChange = [this] {
//      audioProcessor.setOutGain(outGainSlider.getValue());
//   };
//
   addAndMakeVisible(&pressureLabel);
   pressureLabel.setText ("Pressure", dontSendNotification);
   pressureLabel.attachToComponent (&pressureSlider, true);
   pressureLabel.setJustificationType(juce::Justification::bottom);
//
//   addAndMakeVisible(&breathGainLabel);
//   breathGainLabel.setText ("Breath Gain", dontSendNotification);
//   breathGainLabel.attachToComponent (&breathGainSlider, true);
//   breathGainLabel.setJustificationType(juce::Justification::bottom);
//
   addAndMakeVisible(&breathCutoffLabel);
   breathCutoffLabel.setText ("Breath Cutoff", dontSendNotification);
   breathCutoffLabel.attachToComponent (&breathCutoffSlider, true);
   breathCutoffLabel.setJustificationType(juce::Justification::bottom);
//
//   addAndMakeVisible(&vibratoFreqLabel);
//   vibratoFreqLabel.setText ("Vibrato Freq", dontSendNotification);
//   vibratoFreqLabel.attachToComponent (&vibratoFreqSlider, true);
//   vibratoFreqLabel.setJustificationType(juce::Justification::bottom);
//
//   addAndMakeVisible(&vibratoGainLabel);
//   vibratoGainLabel.setText ("Vibrato Gain", dontSendNotification);
//   vibratoGainLabel.attachToComponent (&vibratoGainSlider, true);
//   vibratoGainLabel.setJustificationType(juce::Justification::bottom);
//
//   addAndMakeVisible(&clarinetLenLabel);
//   clarinetLenLabel.setText ("Clarinet Length", dontSendNotification);
//   clarinetLenLabel.attachToComponent (&clarinetLenSlider, true);
//   clarinetLenLabel.setJustificationType(juce::Justification::bottom);
//
//   addAndMakeVisible(&reedStiffnessLabel);
//   reedStiffnessLabel.setText ("Reed Stiffness", dontSendNotification);
//   reedStiffnessLabel.attachToComponent (&reedStiffnessSlider, true);
//   reedStiffnessLabel.setJustificationType(juce::Justification::bottom);
//
//   addAndMakeVisible(&bellOpeningLabel);
//   bellOpeningLabel.setText ("Bell Opening", dontSendNotification);
//   bellOpeningLabel.attachToComponent (&bellOpeningSlider, true);
//   bellOpeningLabel.setJustificationType(juce::Justification::bottom);
}

clarinetPluginAudioProcessorEditor::~clarinetPluginAudioProcessorEditor()
{
}

//==============================================================================
void clarinetPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//   g.fillAll (juce::Colours::white);
   g.setColour (juce::Colours::blue);
   g.setFont (15.0f);

}

void clarinetPluginAudioProcessorEditor::resized()
{
   // the area of the entire rectangle of the plugin window
   auto area = getLocalBounds();
   const int leftMargin = 100;
   pressureSlider.setBounds (area.removeFromLeft (leftMargin+pressureSlider.getWidth()));
   breathCutoffSlider.setBounds(area.removeFromLeft(breathCutoffSlider.getWidth()+leftMargin));
//   breathGainSlider.setBounds(area.removeFromLeft(breathCutoffSlider.getWidth()+10));
//   vibratoFreqSlider.setBounds(area.removeFromLeft(breathGainSlider.getWidth()+10));
//   vibratoGainSlider.setBounds(area.removeFromLeft(vibratoFreqSlider.getWidth()+10));
//   clarinetLenSlider.setBounds(area.removeFromLeft(vibratoGainSlider.getWidth()+10));
//   reedStiffnessSlider.setBounds(area.removeFromLeft(clarinetLenSlider.getWidth()+10));
//   bellOpeningSlider.setBounds(area.removeFromLeft(reedStiffnessSlider.getWidth()+10));
//   outGainSlider.setBounds(area.removeFromLeft(bellOpeningSlider.getWidth()+10));

}
