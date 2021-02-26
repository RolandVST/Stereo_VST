/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Panorama.h"

//==============================================================================
Stereo_vstAudioProcessorEditor::Stereo_vstAudioProcessorEditor (Stereo_vstAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), WidthGui(p), PanoramaGui(p), SourceDistanceGui(p), MSWidthGui(p), PhaseGui(p)
{
   
   setSize(800, 600);
   addAndMakeVisible(&PhaseGui);
   addAndMakeVisible(&MSWidthGui);
   addAndMakeVisible(&SourceDistanceGui);
   addAndMakeVisible(&WidthGui); 
   addAndMakeVisible(&PanoramaGui);
    
}
 
Stereo_vstAudioProcessorEditor::~Stereo_vstAudioProcessorEditor()
{
}




//==============================================================================
void Stereo_vstAudioProcessorEditor::paint (Graphics& g)
{
   Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(Colours::black);

}

void Stereo_vstAudioProcessorEditor::resized()
{
   
   Rectangle<int> area = getLocalBounds();
   PhaseGui.setBounds(area.removeFromLeft(250).removeFromTop(300));
   MSWidthGui.setBounds(area.removeFromLeft(250).removeFromTop(300));
   SourceDistanceGui.setBounds(area.removeFromLeft(250).removeFromTop(300));
   WidthGui.setBounds(0, 300, 550, 300);
   PanoramaGui.setBounds(531, 300,250, 300);


}



