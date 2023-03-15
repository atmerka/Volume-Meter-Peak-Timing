/*
  ==============================================================================

    MeterDB.h
    Created: 28 Dec 2020 2:36:21pm
    Author:  trissy the sissy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class MeterDB    : public Component
{
public:
    MeterDB(LrPeakVolumeMeterAudioProcessor&);
    ~MeterDB();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    
    LrPeakVolumeMeterAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterDB)
};
