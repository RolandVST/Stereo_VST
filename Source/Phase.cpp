/*
  ==============================================================================

    Phase.cpp
    Created: 14 Oct 2020 2:45:50am
    Author:  patry

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Phase.h"

//==============================================================================
Phase::Phase(Stereo_vstAudioProcessor& p) :
    processor(p)
{

    setSize(250, 300);

    phaseL.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    phaseL.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 30);
    phaseL.setRange(-180.0f, 180.0f, 0.10f);
    phaseL.setValue(0.f);
  //  addAndMakeVisible(&phaseL);

    phaseR.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    phaseR.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 30);
    phaseR.setRange(-180.0f, 180.0f, 0.10f);
    phaseR.setValue(0.f);
  //  addAndMakeVisible(&phaseR);

  
    phaseButtonAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
        (processor.mAPVTS, "BUTTON", phaseButton);
    
    addAndMakeVisible(&phaseButton);




    invertMenu.addItem("Normal Polarity",1);
    invertMenu.addItem("Invert Polarity Both", 2);
    invertMenu.addItem("Invert Polarity L", 3);
    invertMenu.addItem("Inver Polarity R", 4);
    invertMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&invertMenu);
    invertMenu.setTextWhenNothingSelected("Invert Polarity Menu");

    invertAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>
        (processor.mAPVTS, "INVERT_MENU", invertMenu);

}

    Phase::~Phase()
    {
    }

    void Phase::invert(float* leftBuffer, float* rightBuffer, float numMenu)
    {
        if (numMenu == 1)
        {
            *leftBuffer = *leftBuffer;
            *rightBuffer = *rightBuffer;
        }
        if (numMenu == 2)
        {
            *leftBuffer = *leftBuffer* (-1);
            *rightBuffer = *rightBuffer * (-1);
        }
        if (numMenu == 3)
        {
            *leftBuffer = *leftBuffer * (-1);
            *rightBuffer = *rightBuffer;
        }
        if (numMenu == 4)
        {
            *rightBuffer = *rightBuffer * (-1);
            *leftBuffer = *leftBuffer;
        }
     
    }

void Phase::mono(float* leftBuffer, float* rightBuffer, float click)
    {
    if (click == 0)
    {
        *leftBuffer = *leftBuffer;
        *rightBuffer = *rightBuffer;
    }
    else
    {
        float mono_signal = (*leftBuffer + *rightBuffer) / 2;
        *leftBuffer = mono_signal;
        *rightBuffer = mono_signal;
    }

    } 
    

void Phase::paint (Graphics& g)
{
   
    Rectangle<int> titleArea(0, 10, getWidth(), 20);


    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Phase", titleArea, Justification::centredTop);


    Rectangle<float> area(25, 25,200, 250);

    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 15.0f, 2.0f);
    g.setColour(Colours::white);
    //g.drawText("Move Phase L [deg]", 40, 135, 120, 20, Justification::centredLeft);
    g.drawText("Mono Button", 90, 80, 180, 20, Justification::centredLeft);

}

void Phase::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);

    
    int sliderPosX = 30;
    int slidentPosY = 80;
    int buttonPosX = 30;
    int ButtonPosY = 30; 

    phaseButton.setBounds(sliderPosX+80, slidentPosY, 80, 80);
    invertMenu.setBounds(buttonPosX, ButtonPosY, 190, 25);



     
  
  
}
