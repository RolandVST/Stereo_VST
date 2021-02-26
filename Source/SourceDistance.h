/*
  ==============================================================================

    SourceDistance.h
    Created: 14 Oct 2020 1:37:56am
    Author:  patry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SourceDistance    : public Component
{
public:
    SourceDistance(Stereo_vstAudioProcessor&);
    ~SourceDistance();

    void paint (Graphics&) override;
    void resized() override;

private:

    Slider sourceDistance;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDistanceAttachment;
	
	Stereo_vstAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceDistance)
};
