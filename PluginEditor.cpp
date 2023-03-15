/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LrPeakVolumeMeterAudioProcessorEditor::LrPeakVolumeMeterAudioProcessorEditor (LrPeakVolumeMeterAudioProcessor& p)
    : AudioProcessorEditor (&p), meterL(p), meterR(p), meterDB(p), processor (p)
{
    //timer speed
    startTimer(5);
    
    //for mouse clicks
    addMouseListener(this, true);
    
    setSize (350, 650);
}

LrPeakVolumeMeterAudioProcessorEditor::~LrPeakVolumeMeterAudioProcessorEditor()
{
}

//==============================================================================
void LrPeakVolumeMeterAudioProcessorEditor::paint (Graphics& g)
{

    //background
    g.fillAll (Colours::black.withAlpha(0.5f));
    
    //headings
    g.setColour(Colours::white);
    g.drawText("L", 0, 0, getWidth()/6, getHeight()*.1, Justification::centred);

    g.drawText("R", getWidth()/6, 0, getWidth()/6, getHeight()*.1, Justification::centred);
    
    g.drawText("DB", getWidth()*2/6, 0, getWidth()/6, getHeight()*.1, Justification::centred);
    
    //loudness types
    g.drawText("AvgOf", getWidth()*4/8, 0, getWidth()/6, getHeight()*.1, Justification::centred);
    
    g.drawText("DB", getWidth()*5/8, 0, getWidth()/6, getHeight()*.1, Justification::centred);
    
    g.drawText("RAW", getWidth()*6/8, 0, getWidth()/6, getHeight()*.1, Justification::centred);
    
    g.drawText("K14", getWidth()*7/8, 0, getWidth()/6, getHeight()*.1, Justification::centred);
    
    
    //=================================STATS============================================================
    
    //instantaneous values======================================================================================
    g.drawText("0s", getWidth()*4/8, getHeight()*0.1, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //gain
    float l = round( processor.loudness * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(l), getWidth()*6/8, getHeight()*0.1, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //db
    l = Decibels::gainToDecibels(processor.loudness);
    l = round( (l+3) * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(l), getWidth()*5/8, getHeight()*0.1, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //k14 value
    l = l + 14;
    g.drawText(String(l), getWidth()*7/8, getHeight()*0.1, getWidth()*1/8, getHeight()*.05, Justification::centred);
    //============================================================================================================
    
    //avg in the last 3 seconds?====================================================================================
    g.drawText("3s", getWidth()*4/8, getHeight()*0.2, getWidth()*1/8, getHeight()*.05, Justification::centred);
    //gain
    float avg3 = round( processor.getLoudness3s() * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(avg3), getWidth()*6/8, getHeight()*0.2, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //db
    avg3 = Decibels::gainToDecibels(processor.getLoudness3s());
    avg3 = round( (avg3+3) * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(avg3), getWidth()*5/8, getHeight()*.2, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //k14 value
    avg3 = avg3 + 14;
    g.drawText(String(avg3), getWidth()*7/8, getHeight()*.2, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //============================================================================================================
    
    //avg in the last 10 seconds?==================================================================================
    g.drawText("10s", getWidth()*4/8, getHeight()*0.3, getWidth()*1/8, getHeight()*.05, Justification::centred);
    //gain
    float avg10 = round( processor.getLoudness10s() * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(avg10), getWidth()*6/8, getHeight()*0.3, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //db
    avg10 = Decibels::gainToDecibels(processor.getLoudness10s());
    avg10 = round( (avg10+3) * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(avg10), getWidth()*5/8, getHeight()*.3, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //k14 value
    avg10 = avg10 + 14;
    g.drawText(String(avg10), getWidth()*7/8, getHeight()*.3, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    
    //============================================================================================================
    
    //avg of all time===============================================================================================
    g.drawText("0>|", getWidth()*4/8, getHeight()*0.4, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //gain
    float lavg = round( processor.getLoudnessTotal() * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(lavg), getWidth()*6/8, getHeight()*0.4, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //db
    lavg = Decibels::gainToDecibels(processor.getLoudnessTotal());
    lavg = round( (lavg+3) * 100.0 ) / 100.0; // 2 decimal places
    g.drawText(String(lavg), getWidth()*5/8, getHeight()*.4, getWidth()*1/8, getHeight()*.05, Justification::centred);
    
    //k14 value
    lavg = lavg + 14;
    g.drawText(String(lavg), getWidth()*7/8, getHeight()*.4, getWidth()*1/8, getHeight()*.05, Justification::centred);
    //============================================================================================================
    
    //===================PEAK COUNTER ======================================================================
    
    g.drawText("Peaktimes::", getWidth()*4/8, getHeight()*0.5, getWidth()*4/8, getHeight()*.05, Justification::centred);
    
    
    
    //if a meter has peaked
    //    if(meterR.hasPeakedR || meterL.hasPeakedL)
        if(processor.peakR>1.0 || processor.peakL>1.0)
    {
        //note the time from the processor
        float t = processor.timeC;
        t = processor.samplePos/ processor.thisSampleRate;

        
        
        t = ceil(t * 100.0) / 100.0;
        
        
        int minute = ((int)t % 3600) / 60;  // Minute component
        int seconds = (int)t % 60;          // Second component
        
        String time = (String)minute + " : " + (String)seconds;
        
        
        //add it to our array of peaktimes
        peakTimes.push_back(time);
        
        
    }

    
    for(int i =0;i<peakTimes.size();i++)
    {
        int x =0;
        if(i>=9) x=1;
        if(i>=18) x=2;
        if(i>=27) x=3;
        if(i>= 36) x = 4;
        
       
        //draw our array of peaktimes
        g.drawText(peakTimes[i],getWidth()*(4+x)/8, getHeight()*0.55 + getHeight()*0.05*(i%9), getWidth()*1/8, getHeight()*.05, Justification::centred);
        
        
    }

    
    //set plug in to resizable
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(20, 50, 500, 1000);
    
    addAndMakeVisible(meterL);
    addAndMakeVisible(meterR);
    addAndMakeVisible(meterDB);
}

void LrPeakVolumeMeterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    meterL.setBounds(0, getHeight()*.1, getWidth()/6, getHeight()*.9);
    
    meterR.setBounds(getWidth()/6, getHeight()*.1, getWidth()/6, getHeight()*.9);
    
    meterDB.setBounds(getWidth()*2/6, getHeight()*.1, getWidth()/6, getHeight()*.9);
    
   
    
}
void LrPeakVolumeMeterAudioProcessorEditor::timerCallback()
{
    repaint();
    
    
}

void LrPeakVolumeMeterAudioProcessorEditor::mouseDown(const MouseEvent &event)
{
    //reset all avgs
    processor.loudnessAVG = 0;
    //processor.loudnessValues.clear();
    //std::fill_n(processor.loudnessValues, 1000000000, 0);
    //don't need to reinitiate count because values are stored at the start anyways
    processor.lCount = 0;
    
    meterL.repaint();
    meterL.hasPeakedL = false;
    meterL.peak = 0.0;
    meterR.repaint();
    meterR.hasPeakedR = false;
    meterR.peak = 0.0;
    
    processor.maxPeakR = processor.maxPeakL =0;
    
    processor.timeC = 0.0f;

    peakTimes.clear();
   
}

