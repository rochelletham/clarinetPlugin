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
   addAndMakeVisible(&pressureSlider);
   pressureSlider.setLookAndFeel((&otherLookAndFeel));
   pressureSlider.setSliderStyle(juce::Slider::LinearVertical);
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
   audioVisualizer.setBounds(visualSpace);
   //TODO: Implement audio settings button
   audioSettingsButton.setBounds(lineOne.removeFromLeft(118));
   lineOne.removeFromLeft(8);
   lineTwo.removeFromTop(8);
   //TODO: Implement save preset button
   //   savePresetButton.setBounds(lineTwo.removeFromLeft(118));

   auto sliderWidth = 50;
   outGainLabel.setBounds(bottomLine.removeFromBottom(12));
   outGainSlider.setBounds(area.removeFromRight(sliderWidth));

   auto leftGroup = area.removeFromLeft(400);
   leftGroup = leftGroup.removeFromTop(200);
   pressureSlider.setBounds(leftGroup.removeFromLeft (sliderWidth));
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
