/*
  ==============================================================================

    MeterDB.cpp
    Created: 28 Dec 2020 2:36:21pm
    Author:  trissy the sissy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MeterDB.h"

//==============================================================================
MeterDB::MeterDB(LrPeakVolumeMeterAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

MeterDB::~MeterDB()
{
}

void MeterDB::paint (Graphics& g)
{

    g.fillAll (Colours::black);   // clear the background
    

    float mH = getHeight();
    
    //total "DB" is -96
    String db;
    
    g.setFont(12.0f);
    
    
    //from 0 to -36
    
    for (int i = 0 ; i < 36/6; i ++)
    {
        g.setColour(Colours::grey);
        g.setFont(12.0f);
        
        
        //draw a small line at this point
        g.drawLine(0, getHeight()-mH + mH*0.5*i*6/36+0.2, getWidth(), getHeight()-mH + mH*0.5*i*6/36+0.2);
    
        
        //convert i *6 to a string
        db = String(i*6);
        //draw the number
        //total height of component minus the height of the meters brings us to the 0 (or now plus 6 point)
        //+meterheight times i times a ratio of the max height, minus 6 to account for 6db at top
        //(minus 6 because rescale to add +6dB)

        g.setColour(Colours::whitesmoke);
        g.drawText(db, 0, getHeight()-mH + mH*0.5*(i+1)*6/36+0.2, getWidth(), 5.0f, Justification::centredTop);

       // g.setFont(6.0f);
        //draw the db sub
        //g.drawText("dB", getWidth()*.6, getHeight()-mH + mH*i*6/96 - 2.5f, getWidth()/4, 5.0f, Justification::centred);
    }
    
    //from -96 to -36
    for(int i= 0 ; i<=(96-36)/6; i++)
    {
        
        g.drawLine(0, getHeight()/2 + mH*0.5*i*6/60+0.2, getWidth(), getHeight()/2 + mH*0.5*i*6/60+0.2);
      

        //convert i *6 to a string
        db = String(i*6+36);

        //draw the number
        //total height of component minus the height of the meters brings us to the 0 (or now plus 6 point)
        //+meterheight times i times a ratio of the max height, minus 6 to account for 6db at top
        //(minus 6 because rescale to add +6dB)
        g.setColour(Colours::whitesmoke);
        g.drawText(db, 0, getHeight()/2 + mH*0.5*(i+1)*6/60+0.2, getWidth(), 5.0f, Justification::centredTop);

        
        
    }
    
    g.setColour(Colours::grey);
    
    g.drawLine(0, 0, 0, getHeight());
    g.drawLine(getWidth(), 0, getWidth(), getHeight());
 
   
}

void MeterDB::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
