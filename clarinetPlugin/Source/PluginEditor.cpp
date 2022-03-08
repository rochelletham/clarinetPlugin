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
   setSize (500, 200);
   midiVolumeSlider.setSliderStyle (juce::Slider::LinearBarVertical);
   midiVolumeSlider.setRange(0, 127, 1);
   midiVolumeSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
   midiVolumeSlider.setPopupDisplayEnabled (true, false, this);
   midiVolumeSlider.setTextValueSuffix (" Volume");
   midiVolumeSlider.setValue(1);
   // makes midiVolume slider visible in window
   addAndMakeVisible (&midiVolumeSlider);

   addAndMakeVisible(pressureSlider);
   pressureSlider.setRange(0.0, 1.0);
   pressureSlider.setValue(0.5);
   // update the pressure value whenever the slider changes
   pressureSlider.onValueChange = [this] {
      audioProcessor.setPressure(pressureSlider.getValue());
   };

   addAndMakeVisible(pressureLabel);
   pressureLabel.setText ("Pressure", dontSendNotification);
   pressureLabel.attachToComponent (&pressureSlider, true);
}

clarinetPluginAudioProcessorEditor::~clarinetPluginAudioProcessorEditor()
{
}

//==============================================================================
void clarinetPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
//   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
   g.fillAll (juce::Colours::white);
   g.setColour (juce::Colours::blue);
   g.setFont (15.0f);
   g.drawFittedText ("Midi Volume", 0,0, getWidth(), 30, juce::Justification::centred, 1);

}

void clarinetPluginAudioProcessorEditor::resized()
{

//   midiVolumeSlider.setBounds (40, 30, 20, getHeight() - 60);
   const int leftMargin = 80;
   midiVolumeSlider.setBounds(leftMargin, 10, getWidth() - leftMargin - 20, 20);
   pressureSlider.setBounds(leftMargin, 40, getWidth() - leftMargin - 20, 20);
}
