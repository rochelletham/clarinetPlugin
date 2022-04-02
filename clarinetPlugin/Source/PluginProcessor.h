/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "dsp-faust/DspFaust.h"
#include "FaustSynth.h"
//==============================================================================
/**
* faust classes
**/
class DspFaust;
class MapUI;
class audio;

class clarinetPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
   clarinetPluginAudioProcessor();
    ~clarinetPluginAudioProcessor() override;

    //==============================================================================
   /**
    Callback function that tells the source to prepare for playing.
    @param samplesPerBlockExpected   the number of samples that the source will be
                                     expected to supply each time its
                                     getNextAudioBlock() method is called.
    @param sampleRate   the sample rate that the output will be used at
    */
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
   /**
    When playback stops, free up any spare memory, etc.
    */
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

   /**
    default JUCE plug-in copies the input buffer in the output buffer.
    leave this function empty. 
    **/
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //===========faust parameter functions==============================
   /* **0**: `/clarinet/blower/pressure`
   * **1**: `/clarinet/blower/breathGain`
   * **2**: `/clarinet/blower/breathCutoff`
   * **3**: `/clarinet/blower/vibratoFreq`
   * **4**: `/clarinet/blower/vibratoGain`
   * **5**: `/clarinet/clarinetModel/tubeLength`
   * **6**: `/clarinet/clarinetModel/reedStiffness`
   * **7**: `/clarinet/clarinetModel/bellOpening`
   * **8**: `/clarinet/clarinetModel/outGain`
    **/
    void setPressure(float pressure);
    void setBreathGain(float breathGain);
    void setBreathCutoff(float breathCutoff);
    void setVibratoFreq(float vibratoFreq); // TODO: will need to rename this..
    void setVibratoGain(float vibratoGain);
    void setTubeLength(float tubeLength);
    void setReedStiffness(float reedStiffness);
    void setBellOpening(float bellOpening);
    void setOutGain(float outGain);

   float getPressure();
   float getBreathGain();
   float getBreathCutoff();
   float getVibratoFreq();
   float getVibratoGain();
   float getTubeLength();
   float getReedStiffness();
   float getBellOpening();
   float getOutGain();

private:
   MapUI* faustUI;      // controls faust dsp parameters
   DspFaust dspFaust;  // contains audio/DSP callback for clarinet API
   float** outputs;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (clarinetPluginAudioProcessor)
};
