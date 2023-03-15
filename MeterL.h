/*
  ==============================================================================

    MeterL.h
    Created: 27 Dec 2020 9:59:36pm
    Author:  trissy the sissy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class MeterL    : public Component
{
public:
    MeterL(LrPeakVolumeMeterAudioProcessor&);
    ~MeterL();

    void paint (Graphics&) override;
    void resized() override;

    //peakvariables
    bool hasPeakedL = false;
    float peak=0;
private:
    
    //height of meter
    int blockHeight;


    
    LrPeakVolumeMeterAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterL)
};
