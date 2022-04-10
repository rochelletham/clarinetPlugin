/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace std;
//==============================================================================
/**
 dsp and MapUI are faust classes.
 -MapUI* fUI is used to control the parameters of the faust dsp
 -dsp fDSP will contain audio DSP/the callback itself
 we declare them as empty classes for now so we can use them
*/
class dsp;
class MapUI;

class clarinetPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    clarinetPluginAudioProcessor();
    ~clarinetPluginAudioProcessor() override;

    //==============================================================================
    /**
     -instantiate faust dsp object (fDSP) and initalize with given sampleRate
     -instantiate the faust UI (fUI) to be able to control dsp parameters
     -bound fUI and fDSP together using buildUserInterface
     -allocate memory for stereo output

     @param sampleRate
     @param samplesPerBlock
     */
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

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
//   void setPressure(float pressure);
//   void setBreathGain(float breathGain);
//   void setBreathCutoff(float breathCutoff);
   void setVibratoFreq(float vibratoFreq); // TODO: will need to rename this..
   void setVibratoGain(float vibratoGain);
   void setTubeLength(float tubeLength);
   void setReedStiffness(float reedStiffness);
   void setBellOpening(float bellOpening);
   void setOutGain(float outGain);
//   void setGate(bool gate);

//  float getPressure();
//  float getBreathGain();
//  float getBreathCutoff();
  float getVibratoFreq();
  float getVibratoGain();
//  float getTubeLength();
  float getReedStiffness();
  float getBellOpening();
  float getOutGain();

private:
   // wrapped as unique ptrs so when it is time to delete them, we don't
   // need to do anything additionally. (new/delete called under the hood)
//   unique_ptr<MapUI> fUI;
//   unique_ptr<dsp> fDSP;
   MapUI* fUI;
   dsp* fDSP;
   // stores our stereo output
   float** outputs;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (clarinetPluginAudioProcessor)

};
