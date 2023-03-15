/*
  ==============================================================================

    MeterR.h
    Created: 27 Dec 2020 9:59:44pm
    Author:  trissy the sissy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class MeterR    : public Component
{
public:
    MeterR(LrPeakVolumeMeterAudioProcessor&);
    ~MeterR();

    void paint (Graphics&) override;
    void resized() override;
    bool hasPeakedR = false;
    float peak=0;
private:
    int blockHeight;
    
    
    
    LrPeakVolumeMeterAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterR)
};
