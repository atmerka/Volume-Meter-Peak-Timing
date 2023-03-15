/*
  ==============================================================================

    MeterR.cpp
    Created: 27 Dec 2020 9:59:44pm
    Author:  trissy the sissy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MeterR.h"

//==============================================================================
MeterR::MeterR(LrPeakVolumeMeterAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MeterR::~MeterR()
{
}

void MeterR::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);
    
    
    //========RMS METER============
    g.setColour(Colours::palevioletred);
    
    //convert average to dB
    float avgInDb = Decibels::gainToDecibels(processor.averageR);
    //rescale for possible values above 0
    //add 3 db to match other meters
    avgInDb = avgInDb-6+3;
    
    //bottom half up to -36
    //top half after that
    
    if(avgInDb<-36)
    {
        float ratio1 = 1+ ((avgInDb +36)/60);
        
        blockHeight = ratio1*getHeight()/2;
        
    }
    else
    {
        g.setColour(Colours::lightcyan);
        float ratio2 = 1+ ((avgInDb)/36);
        
        blockHeight = ratio2 * getHeight()/2 + getHeight()/2;
    }
    
//    //get this as a ratio of it's value to max db
//    //i think -144.5 is silence (+6 for above 0db)
//    float dbRatio = 1+(avgInDb/96);
//    //times the ratio by max height
//    blockHeight = dbRatio*getHeight();
    //draw rect at right height
    if(avgInDb>-18) g.setColour(Colours::lawngreen);
    if(processor.peakR>1.0) g.setColour(Colours::orangered);
    g.fillRect(0, getHeight(), getWidth(), -blockHeight);

    //==========PEAK METER==========
    g.setColour(Colours::lightgrey);
    
    if(processor.peakR>1.0)
    {
        hasPeakedR = true;
    }
    //convert peak to DB
    float peakInDb = Decibels::gainToDecibels(processor.peakR);
    //if the dB value were to be above 0 we would not see it
    //add plus 6db of headroom by getting the value minus 6
    peakInDb = peakInDb-6;
    
    
    float peakHeight = 0;
    if(peakInDb<-36)
    {
        float ratio1 = 1+ ((peakInDb +36)/60);
        
        peakHeight  = ratio1*getHeight()/2;
        
    }
    else
    {
        float ratio2 = 1+ ((peakInDb)/36);
        
        peakHeight = ratio2 * getHeight()/2 + getHeight()/2;
    }
//
//    //get this as a ratio of it's value to max db
//    float pDbRatio;
//    pDbRatio = 1+(peakInDb/96);
//    //times ratio by max height
//    float peakHeight = pDbRatio *getHeight();
    //draw line at this height
    g.drawLine(0, getHeight()-peakHeight, getWidth(), getHeight()-peakHeight);
    
    
    
    //============PEAK HOLD ===============
    //peak to hold red
    if(hasPeakedR)
    {
        g.setColour(Colours::red);
    }
    else
    {
        g.setColour(Colours::grey);
    }
    
    if(processor.peakR>peak)
    {
        peak = processor.peakR;
    }
    float peakdb = Decibels::gainToDecibels(peak);
    peakdb = ceil(peakdb * 100.0) / 100.0;
    g.drawText((String) peakdb, 0, 0, getWidth(), getHeight()*0.1, Justification::centred);
    
    //draw outline
    g.drawRect(0, 0, getWidth(), getHeight());
    
    //draw peak line
    g.setColour(Colours::mediumvioletred);
    g.drawLine(0, getHeight()*6/36/2, getWidth(), getHeight()*6/36/2);
   
}

void MeterR::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
