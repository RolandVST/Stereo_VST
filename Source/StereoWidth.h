/*
  ==============================================================================

    StereoWidth.h
    Created: 13 Oct 2020 10:32:09pm
    Author:  patry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class StereoWidth    : public Component
{
public:
    StereoWidth(Stereo_vstAudioProcessor&);
    ~StereoWidth();

    void paint (Graphics&) override;
    void resized() override;

private:
    //group stereo width slider

    Slider band1Slider;
    Slider band2Slider;
    Slider band3Slider;
    Slider band4Slider; // Bass protect slider




    Slider freqBand1Low;
    Slider freqBand1High;

    Slider freqBand2Low;
    Slider freqBand2High;

    Slider freqBand3Low;
    Slider freqBand3High;

    Slider freqBand4Low;
    Slider freqBand4High;

    Slider dry_wet;
   
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mWidthAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mWidth2Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mWidth3Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mWidth4Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mBand1Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mBand2Attachment;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mBand3Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mBand4Attachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mBand5Attachment;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mLow1ttachment;


    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> dryWetAttachment;
    Stereo_vstAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoWidth)
};
