/*
  ==============================================================================

    Panorama.cpp
    Created: 13 Oct 2020 10:31:45pm
    Author:  patry

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Panorama.h"
#include "PluginProcessor.h"

//==============================================================================
Panorama::Panorama(Stereo_vstAudioProcessor& p) :
processor (p)
{

  
    setSize(300, 300);

   


    panoramaMin.setSliderStyle(Slider::SliderStyle::Rotary);
    panoramaMin.setTextBoxStyle(Slider::TextBoxBelow, true, 55, 18);
    mPanoramaFreqMinAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "PANORAMA_freq_min", panoramaMin);
    panoramaMin.setValue(5.f);

    addAndMakeVisible(panoramaMin);

    panoramaMax.setSliderStyle(Slider::SliderStyle::Rotary);
    panoramaMax.setTextBoxStyle(Slider::TextBoxBelow, true, 55, 18);
    mPanoramaFreqMaxAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "PANORAMA_freq_max", panoramaMax);
    panoramaMax.setValue(25000.f);

    addAndMakeVisible(panoramaMax);


    panorama.setSliderStyle(Slider::SliderStyle::Rotary);
    panorama.setTextBoxStyle(Slider::TextBoxBelow, true, 50.0, 20);
    mPanoramaAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "PANORAMA", panorama);
    panorama.setValue(0.f);
     

    addAndMakeVisible(panorama);


    q_slider.setSliderStyle(Slider::SliderStyle::Rotary);
    q_slider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 18);
    mQ_sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "Q_SLIDER", q_slider);
    q_slider.setValue(0.025f);


   // addAndMakeVisible(q_slider);

}


Panorama::~Panorama()
{
}

void Panorama::paint (Graphics& g) 
{
    
    Rectangle<int> titleArea(0, 10, getWidth(), 20);


    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Panorama", titleArea, Justification::centredTop);
    g.drawText("L", 88, 250, 30, 20, Justification::centredLeft);
    g.drawText("R", 160, 250, 30, 20, Justification::centredRight);
 





    Rectangle<float> area(25, 25, 200, 250);

    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 15.0f, 2.0f);

    g.setColour(Colours::white);
    g.drawText("Range of Freq[Hz]", 25, 32, 140, 20, Justification::centredTop);
    g.drawText("Freq Min", 30, 120, 50, 20, Justification::centredLeft);
    g.drawText("Freq Max", 85, 120, 55, 20, Justification::centredRight);
   


    
}

void Panorama::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);



    int sliderPosX = 70;
    int slidentPosY = 120;


    panorama.setBounds(sliderPosX, slidentPosY+10, 140, 140);
    panoramaMin.setBounds(sliderPosX-55, slidentPosY-80, 80, 80);
    panoramaMax.setBounds(sliderPosX, slidentPosY-80, 80, 80);
    q_slider.setBounds(sliderPosX+55, slidentPosY - 80, 80, 80);
}



void Panorama::Panning(float* leftSample, float* rightSample, float value)
{

    float angle = (value + 100.0) / 200.0 * (MathConstants<float>::pi / 2.0);

    *leftSample = *leftSample * cos(angle) * Decibels::decibelsToGain(-3.0);
    *rightSample = *rightSample * sin(angle) * Decibels::decibelsToGain(-3.0);
}

