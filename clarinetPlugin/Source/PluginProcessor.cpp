/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FaustSynth.h"
#include "dsp-faust/DspFaust.h"

//==============================================================================
clarinetPluginAudioProcessor::clarinetPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
   // indicates that we want to start the Faust audio engine
   dspFaust.start();
}

clarinetPluginAudioProcessor::~clarinetPluginAudioProcessor()
{
   dspFaust.stop();
}

//==============================================================================
const juce::String clarinetPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool clarinetPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool clarinetPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool clarinetPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double clarinetPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int clarinetPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int clarinetPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void clarinetPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String clarinetPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void clarinetPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void clarinetPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
//   dspFaust = new DspFaust();
//   faustUI = new MapUI();
//   dspFaust->buildUserInterface(faustUI);
//   outputs = new float* [2];
//   for (int channel = 0; channel < 2; ++channel) {
//      outputs[channel] = new float[samplesPerBlock];
//   }
}


void clarinetPluginAudioProcessor::releaseResources()
{
//   if (dspFaust != NULL) {
//      delete dspFaust;
//      dspFaust = NULL;
//   }
//   if (faustUI != NULL) {
//      delete faustUI;
//      faustUI = NULL;
//   }
//   if (outputs != NULL) {
//      for (int channel = 0; channel < 2; ++channel) {
//         delete[] outputs[channel];
//         outputs[channel] = NULL;
//      }
//      delete[] outputs;
//   }
   std::cout << "released resources" <<std::endl;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool clarinetPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void clarinetPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
//    juce::ScopedNoDenormals noDenormals;
//    auto totalNumInputChannels  = getTotalNumInputChannels();
//    auto totalNumOutputChannels = getTotalNumOutputChannels();
//
////   dspFaust->compute((int) buffer.getNumSamples(), NULL, outputs);
//
//    // plugin's audio processing handled here
//    // Make sure to reset the state if inner loop is processing
//    // the samples and the outer loop is handling the channels
//   // process every channel of data
//   for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
//      // for every channel, we need to use the buffer audio data
//      for (int i = 0; i < buffer.getNumSamples(); ++i) {
//         *buffer.getWritePointer(channel,i) = outputs[channel][i];
//      }
//   }
}

//==============================================================================
bool clarinetPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* clarinetPluginAudioProcessor::createEditor()
{
   return new clarinetPluginAudioProcessorEditor (*this);
}

//==============================================================================
void clarinetPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void clarinetPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
//   fUI->setParamValue("cutoff",cutoff);
}
//========================faust parameter functions=============================
void clarinetPluginAudioProcessor::setPressure(float pressure) {
   dspFaust.setParamValue("/clarinet/blower/pressure", pressure);
}
void clarinetPluginAudioProcessor::setBreathGain(float breathGain) {
   dspFaust.setParamValue("/clarinet/blower/breathGain", breathGain);
}
void clarinetPluginAudioProcessor::setBreathCutoff(float breathCutoff) {
   dspFaust.setParamValue("/clarinet/blower/breathCutoff", breathCutoff);
}
//void setVibratoFreq(float vibratoFreq) {
//   dspFaust->setParamValue("/clarinet/blower/pressure", pressure);
//}
//void setVibratoGain(float vibratoGain);
//void setTubeLength(float tubeLength);
//void setReedStiffness(float reedStiffness);
//void setBellOpening(float bellOpening);
//void setOutGain(float outGain);
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new clarinetPluginAudioProcessor();
}
