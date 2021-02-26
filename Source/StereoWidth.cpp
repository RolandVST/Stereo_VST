/*
  ==============================================================================

    StereoWidth.cpp
    Created: 13 Oct 2020 10:32:09pm
    Author:  patry

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StereoWidth.h"

//==============================================================================
StereoWidth::StereoWidth(Stereo_vstAudioProcessor& p) :
processor (p)
{
    setSize(400, 300);
    
    band1Slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    band1Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mWidthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "WIDTH", band1Slider);
    band1Slider.setValue(0.0f);
   
    addAndMakeVisible(band1Slider);
    //band1
    freqBand1Low.setSliderStyle(Slider::SliderStyle::Rotary);
    freqBand1Low.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mBand1Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "BAND_1", freqBand1Low);
    freqBand1Low.setValue(250.f);

    addAndMakeVisible(freqBand1Low);


    band2Slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    band2Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 25, 20);
    mWidth2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "WIDTH_2", band2Slider);
    band2Slider.setValue(0.f);
    
    addAndMakeVisible(band2Slider);


    freqBand2Low.setSliderStyle(Slider::SliderStyle::Rotary);
    freqBand2Low.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mBand2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
    (processor.mAPVTS, "BAND_2", freqBand2Low);
    freqBand2Low.setValue(800.1f);

    addAndMakeVisible(freqBand2Low);


    band3Slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    band3Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 25, 20);
    mWidth3Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "WIDTH_3", band3Slider);
    band3Slider.setValue(0.f);
    
    addAndMakeVisible(band3Slider);

    freqBand3Low.setSliderStyle(Slider::SliderStyle::Rotary);
    freqBand3Low.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mBand3Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "BAND_3", freqBand3Low);
    freqBand3Low.setValue(4000.f);

    addAndMakeVisible(freqBand3Low);

 


    band4Slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    band4Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    mWidth4Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "WIDTH_4", band4Slider);
    band4Slider.setValue(0.f);
    
    addAndMakeVisible(band4Slider);

    freqBand4Low.setSliderStyle(Slider::SliderStyle::Rotary);
    freqBand4Low.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    mBand4Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "BAND_4", freqBand4Low);
    freqBand4Low.setValue(8000.f);

    addAndMakeVisible(freqBand4Low);

    freqBand4High.setSliderStyle(Slider::SliderStyle::Rotary);
    freqBand4High.setTextBoxStyle(Slider::TextBoxBelow, true, 55, 20);
    mBand5Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "BAND_5", freqBand4High);
  
    freqBand4High.setValue(20000.f);
    addAndMakeVisible(freqBand4High);


    dry_wet.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    dry_wet.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
    dryWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "DRY_WET", dry_wet);
    dry_wet.setValue(0.0);
    addAndMakeVisible(dry_wet);

    
}

StereoWidth::~StereoWidth()
{
}







void StereoWidth::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
   
    Rectangle<int> titleArea(0, 10, getWidth(), 20);


    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Stereo Width", titleArea, Justification::centredTop);


    Rectangle<float> area(25, 25, 500, 250);

    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 15.0f, 2.0f);

    g.setColour(Colours::white);
    g.drawText("Band 1", 88, 35, 80, 50, Justification::centredTop);
    g.drawText("Band 2", 198, 35, 80, 50, Justification::centredTop);
    g.drawText("Band 3", 302, 35, 80, 20, Justification::centredTop);
    g.drawText("Band 4", 410, 35, 80, 20, Justification::centredTop);

    g.setColour(Colours::lightgrey);
    g.setFont(10.0f);
    g.drawText("Freq[Hz]", 38, 150, 80, 20, Justification::centredLeft);
 //   g.drawText("Max Freq[Hz]", 35, 180, 80, 20, Justification::centredLeft);
    g.drawText("Freq[Hz]", 145, 150, 80, 20, Justification::centredLeft);
  //  g.drawText("Max Freq[Hz]", 140, 180, 80, 20, Justification::centredLeft);
    g.drawText("Freq[Hz]", 255, 150, 80, 20, Justification::centredLeft);
    //g.drawText("Max Freq[Hz]", 250, 180, 80, 20, Justification::centredLeft);
    g.drawText("Freq[Hz]", 365, 150, 80, 20, Justification::centredLeft);
    g.drawText("Freq[Hz]", 473, 150, 80, 20, Justification::centredLeft);


    g.drawText("Wide", 75, 60, 30, 20, Justification::centredTop);
    g.drawText("Narrow", 70, 200, 35, 20, Justification::centredTop);

    g.drawText("Wide", 180, 60, 30, 20, Justification::centredTop);
    g.drawText("Narrow", 177, 200, 35, 20, Justification::centredTop);

    g.drawText("Wide", 290, 60, 30, 20, Justification::centredTop);
    g.drawText("Narrow", 287, 200, 35, 20, Justification::centredTop);

    g.drawText("Wide", 400, 60, 30, 20, Justification::centredTop);
    g.drawText("Narrow", 395, 200, 35, 20, Justification::centredTop);



    g.drawText("Dry/Wet Mixer", 40, 230, 65, 20, Justification::centredLeft);

}

void StereoWidth::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
     
    int sliderWidth = 35;
    int sliderPosX = 110;
    int sliderHeight = 160;
    int slidentPosY = 60;
    int moveX = 90;


    freqBand1Low.setBounds(sliderPosX - moveX, slidentPosY + 10 , 80, 80);
   // freqBand1High.setBounds(sliderPosX - moveX, slidentPosY + 130, 80, 80);
    band1Slider.setBounds(sliderPosX-5, slidentPosY, sliderWidth, sliderHeight);


    freqBand2Low.setBounds(sliderPosX *2 - moveX, slidentPosY + 10, 80, 80);
 //   freqBand2High.setBounds(sliderPosX *2 - moveX, slidentPosY + 130, 80, 80);
    band2Slider.setBounds(sliderPosX * 2-5 , slidentPosY , sliderWidth, sliderHeight);

    freqBand3Low.setBounds(sliderPosX * 3 - moveX, slidentPosY + 10, 80, 80);
 //   freqBand3High.setBounds(sliderPosX * 3 - moveX, slidentPosY + 130, 80, 80);
    band3Slider.setBounds(sliderPosX * 3-5, slidentPosY , sliderWidth, sliderHeight);

    freqBand4Low.setBounds(sliderPosX * 4 - moveX, slidentPosY + 10, 80, 80);
    freqBand4High.setBounds(sliderPosX * 5 - moveX -6, slidentPosY + 10, 80, 80);
    band4Slider.setBounds(sliderPosX * 4 -10 , slidentPosY , sliderWidth, sliderHeight);

    dry_wet.setBounds(100, 230, 380, 30);

}
