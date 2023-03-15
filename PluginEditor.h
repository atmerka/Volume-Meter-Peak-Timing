/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MeterL.h"
#include "MeterR.h"
#include "MeterDB.h"

//==============================================================================
/**
*/
class LrPeakVolumeMeterAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    LrPeakVolumeMeterAudioProcessorEditor (LrPeakVolumeMeterAudioProcessor&);
    ~LrPeakVolumeMeterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    
private:
    //define left right meters and metering dB
    MeterL meterL;
    MeterR meterR;
    MeterDB meterDB;
    
    //to store the times that audio has peaked
    std::vector<String> peakTimes;
    
    
    void mouseDown(const MouseEvent &event) override;
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LrPeakVolumeMeterAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LrPeakVolumeMeterAudioProcessorEditor)
};
