/*
  ==============================================================================

    MSWidth.cpp
    Created: 14 Oct 2020 7:46:18pm
    Author:  patry

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MSWidth.h"
#include "Panorama.h"


//==============================================================================
MSWidth::MSWidth(Stereo_vstAudioProcessor& p):
processor(p)
{
 
    setSize(200, 300);


    sideSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    sideSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 50);
    mSideAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "WIDTH_SIDE", sideSlider);
    sideSlider.setValue(1.f);
   //text = sideSlider.getTextFromValue(sideSlider.getValue());

    addAndMakeVisible(sideSlider);


    midSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    midSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 50);
    mMidAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "WIDTH_MID", midSlider);
    midSlider.setValue(1.f);

    addAndMakeVisible(midSlider);


    widthSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    mwidthSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "WIDTH_MS", widthSlider);
    widthSlider.setValue(0.f);

    addAndMakeVisible(widthSlider);


  


}

MSWidth::~MSWidth()
{
}

void MSWidth::paint (Graphics& g)
{



    Rectangle<int> titleArea(0, 10, getWidth(), 20);


    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("M/S Width", titleArea, Justification::centredTop);


    Rectangle<float> area(25, 25, 200, 250);

    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 15.0f, 2.0f);

    g.setColour(Colours::white);

    g.drawText("Mid", 40, 130, 25, 20, Justification::centredLeft);


   // g.drawText(text, 30, 160, 45, 20, Justification::centredLeft);

   g.drawText("Side", 130, 130, 25, 20, Justification::centredLeft);

    g.drawText("+Mid Gain", 50, 40, 80, 20, Justification::centredTop);
    g.drawText("-Mid Gain", 50, 210, 80, 20, Justification::centredTop);

     


    g.drawText("+Side Gain", 140, 40, 80, 20, Justification::centredTop);
    g.drawText("-Side Gain", 140, 210, 80, 20, Justification::centredTop);

    g.drawText("M/S Width", 23, 255, 80, 20, Justification::centredTop);
}

void MSWidth::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);


    int sliderPosX = 60;
    int slidentPosY = 60;


    midSlider.setBounds(sliderPosX+10, slidentPosY , 40, 140);
    sideSlider.setBounds(sliderPosX*2+40, slidentPosY , 40, 140);
    widthSlider.setBounds(sliderPosX - 20, slidentPosY + 175, 180, 40);

}
void MSWidth::MidSideWidth(float* LeftSample, float* RightSample, float sideGainValue, float midGainValue, float widthValue)
{
   

    float midGain = midGainValue;
    float sideGain = sideGainValue;


        float mid = (*LeftSample + *RightSample);
        float side = (*LeftSample - *RightSample);

   
    float angle = (abs(widthValue)) * (MathConstants<float>::pi / 4.0);

    float newSideL = side * cos( MathConstants<float>::pi / 4.0 - angle) * Decibels::decibelsToGain(-3.0);
    float newSideR = side * sin(MathConstants<float>::pi / 4.0 + angle ) * Decibels::decibelsToGain(-3.0);
    float finalSide = newSideL + newSideR;

    float newMid = midGain * mid;
    float newSide = sideGain * finalSide;


   
   
        *LeftSample = newMid + newSide;
        *RightSample = newMid - newSide;
 
}

