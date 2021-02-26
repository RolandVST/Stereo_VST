/*
  ==============================================================================

    Phase.h
    Created: 14 Oct 2020 2:45:50am
    Author:  patry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Phase    : public Component
{
public:
    Phase(Stereo_vstAudioProcessor&);
    ~Phase();

    void paint (Graphics&) override;
    void resized() override;

   static void invert(float* leftBuffer, float* rightBuffer, float numMenu);

   static void moving(float* leftBuffer, float* rightBuffer);
   static void mono(float* leftBuffer, float* rightBuffer, float click);

private:

    enum class Clicked
    {
        Yes,
        Not
    };

    Clicked clicked{Clicked::Not};

    Slider phaseL;
    Slider phaseR;

    ToggleButton phaseButton;
    

    ComboBox invertMenu;

    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> invertAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> phaseButtonAttachment;

Stereo_vstAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Phase)
};
