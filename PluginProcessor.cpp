/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LrPeakVolumeMeterAudioProcessor::LrPeakVolumeMeterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

LrPeakVolumeMeterAudioProcessor::~LrPeakVolumeMeterAudioProcessor()
{
}

//==============================================================================
const String LrPeakVolumeMeterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LrPeakVolumeMeterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LrPeakVolumeMeterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LrPeakVolumeMeterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LrPeakVolumeMeterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LrPeakVolumeMeterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LrPeakVolumeMeterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LrPeakVolumeMeterAudioProcessor::setCurrentProgram (int index)
{
}

const String LrPeakVolumeMeterAudioProcessor::getProgramName (int index)
{
    return {};
}

void LrPeakVolumeMeterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void LrPeakVolumeMeterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    thisBufferSize = samplesPerBlock;
    thisSampleRate = sampleRate;
}

void LrPeakVolumeMeterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LrPeakVolumeMeterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LrPeakVolumeMeterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //get playhead
    playHead = this->getPlayHead();
    if (playHead != nullptr)
    {
        playHead->getCurrentPosition (hostInfo);
//        temp = hostInfo.bpm;
//        isPlaying = hostInfo.isPlaying;
//        position = hostInfo.ppqPosition;
        samplePos = hostInfo.timeInSamples;
    }

    //clear buffer
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //alter buffer
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //auto* channelData = buffer.getWritePointer (channel);

        for(int i  = 0; i < buffer.getNumSamples(); i++)
        {
            
           
        }
    }
    //peak for drawing
    peakL = buffer.getMagnitude(0, 0, buffer.getNumSamples());
    peakR = buffer.getMagnitude(1, 0, buffer.getNumSamples());
    
    //update peak data
    updateMaxPeak(peakL,peakR);
    
    //avg for drawing
    averageL = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    averageR = buffer.getRMSLevel(1, 0, buffer.getNumSamples());
    
    //loudness is average of LR loudness
    loudness = (averageL+averageR)/2;
   
    //add value to loudness array
    updateLoudness(loudness);
    
    //count time
//    timeC = timeC + 2048.0f/44100.0f;
    timeC = timeC + thisBufferSize/thisSampleRate;
}

//==============================================================================
bool LrPeakVolumeMeterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* LrPeakVolumeMeterAudioProcessor::createEditor()
{
    return new LrPeakVolumeMeterAudioProcessorEditor (*this);
}

//==============================================================================
void LrPeakVolumeMeterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LrPeakVolumeMeterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void LrPeakVolumeMeterAudioProcessor::updateLoudness(float loudness)
{
    //if there is not silence
    if(loudness > 0)
    {
        //store loudness
        //add loudnessvalue to array
        loudnessValues[lCount] = loudness;
        
        //add to count
        lCount++;
    }
}

void LrPeakVolumeMeterAudioProcessor::updateMaxPeak(float l, float r)
{
    if(l >maxPeakL)
    {
        maxPeakL = l;
    }
    if(r > maxPeakR)
    {
        maxPeakR =r;
    }
    
}

float LrPeakVolumeMeterAudioProcessor::getLoudnessTotal()
{
    float sum = 0;
    //calculate average
    //for all the loudness values
    for(int i=0;i<lCount;i++)
    {
        //add them together
        //increase sum
        sum = sum + loudnessValues[i];
    }
    
    loudnessAVG = sum/lCount;
    //loudnessAVG =loudnessValues[lCount] ;
    
    return loudnessAVG;
}


float LrPeakVolumeMeterAudioProcessor::getLoudness3s()
{
    
    float sum = 0;
    //calculate average
    //for the loudness values of the last 3 seconds
    //3 seconds is samplerate times 3/buffersize (taking loudness sample each buffer)
    //so lCount minus sampleRate*3
    int sSamp = 0;
    if(lCount>thisSampleRate*3/thisBufferSize)
    {
         sSamp =lCount-thisSampleRate*3/thisBufferSize;
        
    }
    
    //for the values between 3 seconds ago and now
    for(int i=sSamp;i<lCount;i++)
    {
        //add them together
        //increase sum
        sum = sum + loudnessValues[i];
    }
    
    
    return  sum/(lCount-sSamp);
    
}

float LrPeakVolumeMeterAudioProcessor::getLoudness10s()
{
    float sum = 0;
    //calculate average
    //for the loudness values of the last 3 seconds
    //3 seconds is samplerate times 3
    //so lCount minus sampleRate*3
    int sSamp = 0;
    if(lCount>thisSampleRate*10/thisBufferSize)
    {
        sSamp =lCount-thisSampleRate*10/thisBufferSize;
        
    }
    
    //for the values between 10 seconds ago and now
    for(int i=sSamp;i<lCount;i++)
    {
        //add them together
        //increase sum
        sum = sum + loudnessValues[i];
    }
    
    
    return  sum/(lCount-sSamp);
    
}


float LrPeakVolumeMeterAudioProcessor::getPeak()
{
//    float p=0;
//    for(int i=0;i<lCount;i++)
//    {
//        if(loudnessValues[i]>p)
//        {
//            p = loudnessValues[i];
//        }
//    }
//    return p;
    
    if(maxPeakR>maxPeakL)
    {
        return maxPeakR;
    }
    else
    {
        return maxPeakL;
    }
    
}

float LrPeakVolumeMeterAudioProcessor::getTruePeak()
{
    oversamplex2(loudnessValues, loudnessValues2x, lCount);
    oversamplex2(loudnessValues2x, loudnessValues4x, lCount*2);
    
    bool lessThan = false;
    
    int c1=0;
    int c2=0;
    
    for(int i=0;i < lCount*4;i++)
    {
        //if we have 10 samples above 0.99 in a row then add to count
        if(loudnessValues4x[i]>0.99)
        {
            c1++;
        }
        if(c1==10)
        {
            //c2++;
            c1=0;
        }
        
        if(loudnessValues4x[i]>0.95 && lessThan)
        {
            c2++;
        }
        
        //if we have a sample jump from 0.5 to above 0.9 report it
        if(loudnessValues4x[i] <0.95)
        {
            lessThan =  true;
        }
        
    }
    return c2;
}

void LrPeakVolumeMeterAudioProcessor::oversamplex2(float *lvalues, float *lvalue2, int count)
{
    for(int i=0;i < count;i++)
    {
        lvalue2[(i*2)-1] = lvalues[i];
        
        lvalue2[2*i] = (lvalues[i] + lvalues[i+1])/2;
    }
    
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LrPeakVolumeMeterAudioProcessor();
}
