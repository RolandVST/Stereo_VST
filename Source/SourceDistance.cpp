/*
  ==============================================================================

    SourceDistance.cpp
    Created: 14 Oct 2020 1:37:56am
    Author:  patry

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SourceDistance.h"

//==============================================================================
SourceDistance::SourceDistance(Stereo_vstAudioProcessor& p):
processor(p)
{
    setSize(200, 300);


    sourceDistance.setSliderStyle(Slider::SliderStyle::Rotary);
    sourceDistance.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    mDistanceAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
        (processor.mAPVTS, "DISTANCE", sourceDistance);
    sourceDistance.setValue(0.f);

    addAndMakeVisible(sourceDistance);


}

SourceDistance::~SourceDistance()
{
}

void SourceDistance::paint (Graphics& g)
{

    Rectangle<int> titleArea(0, 10, getWidth(), 20);


    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Source Distance", titleArea, Justification::centredTop);


    Rectangle<float> area(25, 25, 200, 250);

    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 15.0f, 2.0f);
    g.setColour(Colours::white);
    g.drawText("Near", 80, 210, 40, 20, Justification::centredLeft);
    g.drawText("Far", 120, 210, 40, 20, Justification::centredRight);



}

void SourceDistance::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);

  
    int sliderPosX = 45;
    int slidentPosY = 70;


    sourceDistance.setBounds(sliderPosX , slidentPosY , 160, 160);

}
