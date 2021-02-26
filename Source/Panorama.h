/*
  ==============================================================================

    Panorama.h
    Created: 13 Oct 2020 10:31:45pm
    Author:  patry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Panorama    : public Component
{
public:
    Panorama(Stereo_vstAudioProcessor&);
    ~Panorama();

    void paint (Graphics&) override;
    void resized() override;
    static void Panning(float* leftSample, float* rightSample, float value) ;

private:
    Stereo_vstAudioProcessor& processor;
    Slider panoramaMin;
    Slider panoramaMax;
    Slider panorama; 
    Slider q_slider;

    

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mPanoramaAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mPanoramaFreqMinAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mPanoramaFreqMaxAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mQ_sliderAttachment;
public:
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Panorama)
};
