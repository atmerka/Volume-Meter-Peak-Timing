/*
  ==============================================================================

    MeterL.cpp
    Created: 27 Dec 2020 9:59:36pm
    Author:  trissy the sissy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MeterL.h"

//==============================================================================
MeterL::MeterL(LrPeakVolumeMeterAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MeterL::~MeterL()
{
}

void MeterL::paint (Graphics& g)
{
    //fill all black
    g.fillAll (Colours::black);
    
    
    //==========RMS METER==========
    //set rms meter level
    g.setColour(Colours::lightcyan);
   
    
    //convert average to dB
    float avgInDb = Decibels::gainToDecibels(processor.averageL);
    //rescale for possible values above 0
    avgInDb = avgInDb-6+3;
    //half the blocks
    if(avgInDb<-36)
    {
        float ratio1 = 1+ ((avgInDb +36)/60);
        
        blockHeight = ratio1*getHeight()/2;
        
    }
    else
    {
        g.setColour(Colours::lightblue);
        float ratio2 = 1+ ((avgInDb)/36);
        
        blockHeight = ratio2 * getHeight()/2 + getHeight()/2;
    }
   
//    //get this as a ratio of it's value to max db
//    float dbRatio = 1+(avgInDb/96);
//    //times the ratio by max height
//    blockHeight = dbRatio*getHeight();
    //draw rectangle of the right height
    
    if(avgInDb>-18) g.setColour(Colours::lawngreen);
    if(processor.peakL>1.0){g.setColour(Colours::orangered);}
    g.fillRect(0, getHeight(), getWidth(), -blockHeight);
    
    //==========PEAK METER==========
    g.setColour(Colours::lightgrey);
    
    if(processor.peakL>1.0)
    {
        hasPeakedL = true;
    }
    //convert peak to DB
    float peakInDb = Decibels::gainToDecibels(processor.peakL);
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
//    float pDbRatio = 1+(peakInDb/96);
//    //times ratio by max height
//    float peakHeight = pDbRatio *getHeight();
    //draw line at this height
    g.drawLine(0, getHeight()-peakHeight, getWidth(), getHeight()-peakHeight);
    
    
    //============ PEAK HOLD ===========
    if(hasPeakedL)
    {
        g.setColour(Colours::red);

        
    }
    else
    {
        g.setColour(Colours::grey);
        
    }
    if(processor.peakL>peak)
    {
        peak = processor.peakL;
    }
    float peakdb = Decibels::gainToDecibels(peak);
    peakdb = ceil(peakdb * 100.0) / 100.0;
    g.drawText((String) peakdb, 0, 0, getWidth(), getHeight()*0.1, Justification::centred);
    
    g.drawRect(0, 0, getWidth(), getHeight());
    
   g.setColour(Colours::mediumvioletred);
    
    //draw peak line
    g.drawLine(0, getHeight()*6/36/2, getWidth(), getHeight()*6/36/2);
    

   
}

void MeterL::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
