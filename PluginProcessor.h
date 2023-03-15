/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class LrPeakVolumeMeterAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    LrPeakVolumeMeterAudioProcessor();
    ~LrPeakVolumeMeterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    //variables
    float averageL;
    float averageR;
    
    float peakL;
    float peakR;
    
    float val;
    float valPos;
    
    float loudness;
    //one thousand seconds of loudness information
    float loudnessValues[44100*1000];
    int lCount =0;
    float sum = 0;
    float loudnessAVG =0;
    
    float loudnessValues2x[44100*1000*2];
    float loudnessValues4x[44100*1000*4];

    
    //functions
    float getPeak();
    float getLoudness3s();
    float getLoudness10s();
    
    float getLoudnessTotal();
    void updateMaxPeak(float,float);
    
    float maxPeakL=0;
    float maxPeakR=0;
    
    float getTruePeak();
    
    //peak times
    float timeC=0;
    
    double position;
    int64 samplePos;
    float thisSampleRate=0;
private:
    
    //for playtime
    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo hostInfo;
    
    float thisBufferSize = 0;
    
    void updateLoudness(float loudness);
    void oversamplex2(float *lvalues, float *lvalues2, int count);
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LrPeakVolumeMeterAudioProcessor)
};
