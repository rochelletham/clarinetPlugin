/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "ClarinetPhysModMidi.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace std;
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
   
}

clarinetPluginAudioProcessor::~clarinetPluginAudioProcessor()
{
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
//   fDSP = new mydsp();
//   fDSP->init(sampleRate);
//   fUI = new MapUI();
//   fDSP->buildUserInterface(fUI);
//   outputs = new float*[2];
//   for (int channel = 0; channel < 2; ++channel) {
//      outputs[channel] = new float[samplesPerBlock];
//   }
   //   fDSP = make_unique<dsp>();
   //   fUI = make_unique<MapUI>();

   fDSP = new mydsp();
   fDSP->init(sampleRate);
   fUI = new MapUI();
   // TODO: no viable conversion from unique_ptr<MapUI> to UI *
   fDSP->buildUserInterface(fUI);
   outputs = new float*[2];
   for (int channel = 0; channel < 2; ++channel) {
      outputs[channel] = new float[samplesPerBlock];
   }

}

void clarinetPluginAudioProcessor::releaseResources()
{
   delete fDSP;
   delete fUI;
   for (int channel = 0; channel < 2; ++channel) {
      delete[] outputs[channel];
   }
   delete [] outputs;
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
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

   // compute one audio block of size buffer.getNumSamples and store in outputs
   fDSP->compute(buffer.getNumSamples(), NULL, outputs);

   for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
      for (int i = 0; i < buffer.getNumSamples(); i++) {
         // link outputs to the audio output of processBlock
         *buffer.getWritePointer(channel,i) = outputs[channel][i];
      }
   }
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
}

//========================faust set parameter functions=============================
//void clarinetPluginAudioProcessor::setPressure(float pressure) {
//   fUI->setParamValue("/clarinet/blower/pressure", pressure);
//}
//void clarinetPluginAudioProcessor::setBreathGain(float breathGain) {
//   fUI->setParamValue("/clarinet/blower/breathGain", breathGain);
//}
//void clarinetPluginAudioProcessor::setBreathCutoff(float breathCutoff) {
//   fUI->setParamValue("/clarinet/blower/breathCutoff", breathCutoff);
//}

void clarinetPluginAudioProcessor::setVibratoFreq(float vibratoFreq) {
   fUI->setParamValue("/clarinet/otherParams/vibratoFreq", vibratoFreq);
}
void clarinetPluginAudioProcessor::setVibratoGain(float vibratoGain) {
   fUI->setParamValue("/clarinet/otherParams/vibratoGain", vibratoGain);
}

//void clarinetPluginAudioProcessor::setTubeLength(float tubeLength) {
//   fUI->setParamValue("/clarinet/clarinetModel/tubeLength", tubeLength);
//}
void clarinetPluginAudioProcessor::setReedStiffness(float reedStiffness) {
   fUI->setParamValue("/clarinet/otherParams/reedStiffness", reedStiffness);
}
void clarinetPluginAudioProcessor::setBellOpening(float bellOpening) {
   fUI->setParamValue("/clarinet/otherParams/bellOpening", bellOpening);
}
void clarinetPluginAudioProcessor::setOutGain(float outGain) {
   fUI->setParamValue("/clarinet/otherParams/outGain", outGain);
}

//void clarinetPluginAudioProcessor::setGate(bool gate)
//{
//    if(gate) {
//        fUI->setParamValue("/clarinet/gate",1);
//    } else {
//        fUI->setParamValue("/clarinet/gate",0);
//    }
//}

//========================faust get parameter functions=============================
//float clarinetPluginAudioProcessor::getPressure() {
//   return fUI->getParamValue("/clarinet/blower/pressure");
//}
//float clarinetPluginAudioProcessor::getBreathGain() {
//   return fUI->getParamValue("/clarinet/blower/breathGain");
//}
//float clarinetPluginAudioProcessor::getBreathCutoff() {
//   return fUI->getParamValue("/clarinet/blower/breathCutoff");
//}
float clarinetPluginAudioProcessor::getVibratoFreq() {
   return fUI->getParamValue("/clarinet/blower/vibratoFreq");
}
float clarinetPluginAudioProcessor::getVibratoGain() {
   return fUI->getParamValue("/clarinet/blower/vibratoGain");
}
//float clarinetPluginAudioProcessor::getTubeLength() {
//   return fUI->getParamValue("/clarinet/clarinetModel/tubeLength");
//}
float clarinetPluginAudioProcessor::getReedStiffness() {
   return fUI->getParamValue("/clarinet/otherParams/reedStiffness");
}
float clarinetPluginAudioProcessor::getBellOpening() {
   return fUI->getParamValue("/clarinet/otherParams/bellOpening");
}
float clarinetPluginAudioProcessor::getOutGain() {
   return fUI->getParamValue("/clarinet/otherParams/outGain");
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new clarinetPluginAudioProcessor();
}
