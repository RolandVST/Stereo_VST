  /*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <cmath>
#include <stdlib.h>



//==============================================================================
/**
*/
class Stereo_vstAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Stereo_vstAudioProcessor();
    ~Stereo_vstAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override
    {
#if JucePlugin_ProducesMidiOutput
        return true;
#else
        return false;
#endif
    }
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    
   void process(dsp::ProcessContextNonReplacing<float> context);

   void process(dsp::ProcessContextReplacing<float> context);


    void updateFilter();
 
    
    AudioProcessorValueTreeState mAPVTS;

    void setParameters();

   
private:
    AudioBuffer<float> copy_to_panorama_bandPass;
    AudioBuffer<float> copy_to_panorama_lowPass;
    AudioBuffer<float> copy_to_panorama_highPass;
    AudioBuffer<float> out_from_panorama;

    AudioBuffer<float> buffer_bandPass_1;
    AudioBuffer<float> buffer_bandPass_2;
    AudioBuffer<float> buffer_bandPass_3;
    AudioBuffer<float> buffer_bandPass_4;

    AudioBuffer<float> buffer_lowPass; //resztki bez procesingu
    AudioBuffer<float> buffer_highPass; // resztki

    AudioBuffer<float> out_from_stereo_width;
    AudioProcessorValueTreeState::ParameterLayout createParameters();
 
    //nowe wersje filtrow

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPass1;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPass1;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPass2;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPass2;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPass3;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPass3;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPass4;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPass4;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPass5;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPass5;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPass6;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPass6;

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPassPan1;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPassPan1;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPassPan2;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highPassPan2;




   
    Reverb fxReverb;
    Reverb::Parameters reverbParameters;
    dsp::Gain<float> gain;

    static constexpr auto effectDelaySamples = 192000;

    dsp::DelayLine<float> delay{ effectDelaySamples };
    dsp::DelayLine<float, dsp::DelayLineInterpolationTypes::Linear> linear{ effectDelaySamples };
    dsp::DryWetMixer<float> mixer;

    std::array<float, 2> delayValue_1{ {} };
    std::array<float, 2> lastDelayOutput_1;
    std::array<LinearSmoothedValue<float>, 2> delayFeedbackVolume;



    dsp::DelayLine<float> delay_2{ effectDelaySamples };
    dsp::DelayLine<float, dsp::DelayLineInterpolationTypes::Linear> linear_2{ effectDelaySamples };
    std::array<float, 2> delayValue_2{ {} };
    std::array<float, 2> lastDelayOutput_2;
    std::array<LinearSmoothedValue<float>, 2> delayFeedbackVolume_2;

    dsp::DelayLine<float> delay_3{ effectDelaySamples };
    dsp::DelayLine<float, dsp::DelayLineInterpolationTypes::Linear> linear_3{ effectDelaySamples };
    std::array<float, 2> delayValue_3{ {} };
    std::array<float, 2> lastDelayOutput_3;
    std::array<LinearSmoothedValue<float>, 2> delayFeedbackVolume_3;

    dsp::DelayLine<float> delay_4{ effectDelaySamples };
    dsp::DelayLine<float, dsp::DelayLineInterpolationTypes::Linear> linear_4{ effectDelaySamples };
    std::array<float, 2> delayValue_4{ {} };
    std::array<float, 2> lastDelayOutput_4;
    std::array<LinearSmoothedValue<float>, 2> delayFeedbackVolume_4;


 
private:
    float lastSampleRate;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Stereo_vstAudioProcessor)
};
