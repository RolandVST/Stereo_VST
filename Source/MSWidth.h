/*
  ==============================================================================

    MSWidth.h
    Created: 14 Oct 2020 7:46:18pm
    Author:  patry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Panorama.h"
//==============================================================================
/*
*/
class MSWidth    : public Component
{
public:
    MSWidth(Stereo_vstAudioProcessor&);
    ~MSWidth();

    void paint (Graphics&) override;
    void resized() override;

    static void MidSideWidth(float* LeftSample, float* RightSample, float sideGainValue, float midGainValue, float widthValue);

private:

    Slider sideSlider;
    Slider midSlider;
    
    Slider widthSlider;
    String text;
 
 
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mSideAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mMidAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mwidthSliderAttachment;
	
	Stereo_vstAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MSWidth)
};
