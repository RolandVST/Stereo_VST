/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "StereoWidth.h"
#include "Panorama.h"
#include "SourceDistance.h"
#include "MSWidth.h"
#include "Phase.h"

//==============================================================================
/**
*/
class Stereo_vstAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Stereo_vstAudioProcessorEditor (Stereo_vstAudioProcessor&);
    ~Stereo_vstAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;






private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Stereo_vstAudioProcessor& processor;

    Phase PhaseGui;
    MSWidth MSWidthGui;
    StereoWidth WidthGui;
    Panorama PanoramaGui;
    SourceDistance SourceDistanceGui;
    

   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Stereo_vstAudioProcessorEditor)
};
