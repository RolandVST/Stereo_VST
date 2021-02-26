/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "StereoWidth.h"
#include "Panorama.h"
#include "SourceDistance.h"
#include "Phase.h"
#include "MSWidth.h"




//==============================================================================
Stereo_vstAudioProcessor::Stereo_vstAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
            #if ! JucePlugin_IsMidiEffect
            #if ! JucePlugin_IsSynth
                  .withInput("Input", AudioChannelSet::stereo(), true)
            #endif
                     .withOutput("Output", AudioChannelSet::stereo(), true)
            #endif
            ), mAPVTS(*this, nullptr, "PARAMETERS", createParameters()),
    lowPassPan1(dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 1.f)), highPassPan1(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000.0f, 1.f)),
    lowPassPan2(dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 1.f)), highPassPan2(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000.0f, 1.f)),
    lowPass1(dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 1.f)), highPass1(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000.0f, 1.f)),
    lowPass2(dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 1.f)), highPass2(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000.0f, 1.f)),
    lowPass3(dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 1.f)), highPass3(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000.0f, 1.f)),
    lowPass4(dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 1.f)), highPass4(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000.0f, 1.f)),
    lowPass5(dsp::IIR::Coefficients<float>::makeLowPass(44100, 2000.0f, 1.f)), highPass5(dsp::IIR::Coefficients<float>::makeHighPass(44100, 2000.0f, 1.f))
#endif
{
}



Stereo_vstAudioProcessor::~Stereo_vstAudioProcessor()
{
}

//==============================================================================


const String Stereo_vstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Stereo_vstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Stereo_vstAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Stereo_vstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Stereo_vstAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Stereo_vstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Stereo_vstAudioProcessor::setCurrentProgram (int index)
{
}

const String Stereo_vstAudioProcessor::getProgramName (int index)
{
    return {};
}

void Stereo_vstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Stereo_vstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) //initialization and reset of modules and filters
{

    
    lastSampleRate = sampleRate;
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();

    // initialization 
  
    fxReverb.setSampleRate(lastSampleRate);
	
    lowPass1.prepare(spec);
    highPass1.prepare(spec);
    lowPass2.prepare(spec);
    highPass2.prepare(spec);
    lowPass3.prepare(spec);
    highPass3.prepare(spec);
    lowPass4.prepare(spec);
    highPass4.prepare(spec);
    lowPass5.prepare(spec);
    highPass5.prepare(spec);
    gain.prepare(spec);

    lowPassPan1.prepare(spec);
    highPassPan1.prepare(spec);
    lowPassPan2.prepare(spec);
    highPassPan2.prepare(spec);

    delay.prepare(spec);
    delay_2.prepare(spec);
    delay_3.prepare(spec);
    delay_4.prepare(spec);

    linear.prepare(spec);
    linear_2.prepare(spec);
    linear_3.prepare(spec);
    linear_4.prepare(spec);
    mixer.prepare(spec);

	// reset

    for (auto& volume : delayFeedbackVolume)
        volume.reset(spec.sampleRate, 0.05);

    for (auto& volume_1 : delayFeedbackVolume_2)
        volume_1.reset(spec.sampleRate, 0.05);

    for (auto& volume_2 : delayFeedbackVolume_3)
        volume_2.reset(spec.sampleRate, 0.05);

    for (auto& volume_3 : delayFeedbackVolume_4)
        volume_3.reset(spec.sampleRate, 0.05);

    gain.reset();
    linear.reset();
    linear_2.reset();
    linear_3.reset();
    linear_4.reset();
    std::fill(lastDelayOutput_1.begin(), lastDelayOutput_1.end(), 0.0f);
    std::fill(lastDelayOutput_2.begin(), lastDelayOutput_2.end(), 0.0f);
    std::fill(lastDelayOutput_3.begin(), lastDelayOutput_3.end(), 0.0f);
    std::fill(lastDelayOutput_4.begin(), lastDelayOutput_4.end(), 0.0f);

    lowPassPan1.reset();
    highPassPan1.reset();
    lowPassPan2.reset();
    highPassPan2.reset();

    lowPass1.reset();
    highPass1.reset();
    lowPass2.reset();
    highPass2.reset();
    lowPass3.reset();
    highPass3.reset();
    lowPass4.reset();
    highPass4.reset();
    lowPass5.reset();
    highPass5.reset();


}

void Stereo_vstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Stereo_vstAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void Stereo_vstAudioProcessor::process(dsp::ProcessContextNonReplacing<float> context)
{ 
   
}

void Stereo_vstAudioProcessor::process(dsp::ProcessContextReplacing<float> context)
{
}


void Stereo_vstAudioProcessor::updateFilter()
{
         float freq_value_min = mAPVTS.getRawParameterValue("PANORAMA_freq_min") -> load();
         float freq_value_max = mAPVTS.getRawParameterValue("PANORAMA_freq_max")->load();
       
         float q = 1.0f;
         *lowPassPan1.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, freq_value_max, q);
         *highPassPan1.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, freq_value_min, q);
         *lowPassPan2.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, freq_value_min , q);
         *highPassPan2.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, freq_value_max , q);

          float band1 = mAPVTS.getRawParameterValue("BAND_1")->load();
          float band2 = mAPVTS.getRawParameterValue("BAND_2")->load();
          float band3 = mAPVTS.getRawParameterValue("BAND_3")->load();
          float band4 = mAPVTS.getRawParameterValue("BAND_4")->load();
          float band5 = mAPVTS.getRawParameterValue("BAND_5")->load();
          

          
         *lowPass1.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, band1, q);

         //band1
         *highPass1.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, band1, q); // 
          *lowPass2.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, band2, q);

		 //band2
         *highPass2.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, band2, q);  
         *lowPass3.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, band3, q);

		//band3
        *highPass3.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, band3, q);
        *lowPass4.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, band4, q);


        //band4
        *highPass4.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, band4, q);
        *lowPass5.state = *dsp::IIR::Coefficients<float> ::makeLowPass(lastSampleRate, band5, q);

        //band 5
        *highPass5.state = *dsp::IIR::Coefficients<float> ::makeHighPass(lastSampleRate, band5, q);
   
}



void Stereo_vstAudioProcessor::setParameters()
{

   
    reverbParameters.wetLevel = mAPVTS.getRawParameterValue("DISTANCE")->load() /10.f;
    reverbParameters.dryLevel = 0.5f- mAPVTS.getRawParameterValue("DISTANCE")->load() / 10.f;
    reverbParameters.width = 0.1f;
    reverbParameters.roomSize = 0.3f;
    reverbParameters.damping = 0.7f;
    fxReverb.setParameters(reverbParameters);
}




void Stereo_vstAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    //sekcja buforów

   
    setParameters();
   fxReverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());


       // kopiowanie aktualnego stanu buffera  do bufferow pomocnicznych
    copy_to_panorama_bandPass.setSize(2, buffer.getNumSamples());
    copy_to_panorama_bandPass.copyFrom(0, 0, buffer.getReadPointer(0), buffer.getNumSamples());
    copy_to_panorama_bandPass.copyFrom(1, 0, buffer.getReadPointer(1), buffer.getNumSamples());

    copy_to_panorama_lowPass.setSize(2, buffer.getNumSamples());
    copy_to_panorama_lowPass.copyFrom(0, 0, buffer.getReadPointer(0), buffer.getNumSamples());
    copy_to_panorama_lowPass.copyFrom(1, 0, buffer.getReadPointer(1), buffer.getNumSamples());

    copy_to_panorama_highPass.setSize(2, buffer.getNumSamples());
    copy_to_panorama_highPass.copyFrom(0, 0, buffer.getReadPointer(0), buffer.getNumSamples());
    copy_to_panorama_highPass.copyFrom(1, 0, buffer.getReadPointer(1), buffer.getNumSamples());

    out_from_panorama.setSize(2, buffer.getNumSamples());
    out_from_panorama.copyFrom(0, 0, buffer.getReadPointer(0), buffer.getNumSamples());
    out_from_panorama.copyFrom(1, 0, buffer.getReadPointer(1), buffer.getNumSamples());


    dsp::AudioBlock<float> block_raw(buffer);
    dsp::AudioBlock<float> block_out(copy_to_panorama_bandPass);
    dsp::AudioBlock<float> block_out_low(copy_to_panorama_lowPass);
    dsp::AudioBlock<float> block_out_high(copy_to_panorama_highPass);

    

    updateFilter();
    lowPassPan1.process(dsp::ProcessContextNonReplacing<float>(block_raw, block_out));
    highPassPan1.process(dsp::ProcessContextReplacing<float>(block_out));
    lowPassPan2.process(dsp::ProcessContextNonReplacing<float>(block_raw, block_out_low));
    highPassPan2.process(dsp::ProcessContextNonReplacing<float>(block_raw, block_out_high));
    

    float* left = copy_to_panorama_bandPass.getWritePointer(0);
    float* right = copy_to_panorama_bandPass.getWritePointer(1);

    const float* left_low = copy_to_panorama_lowPass.getReadPointer(0);
    const float* right_low = copy_to_panorama_lowPass.getReadPointer(1);

    const float* left_high = copy_to_panorama_highPass.getReadPointer(0);
    const float* right_high = copy_to_panorama_highPass.getReadPointer(1);

    float* out_l = out_from_panorama.getWritePointer(0);
    float* out_r = out_from_panorama.getWritePointer(1);
  


    for (int sample = 0 ; sample < buffer.getNumSamples(); ++sample)
    {
    float panorama_val = mAPVTS.getRawParameterValue("PANORAMA")->load();
    Panorama::Panning(&left[sample], &right[sample], panorama_val);
    out_l[sample] = left[sample] + left_high[sample] + left_low[sample];
    out_r[sample] = right[sample] + right_high[sample] + right_low[sample];
    }
 

    // kopiowanie obecnego stanu buffera do buferow pomcnicych do stereo width
    buffer_bandPass_1.setSize(2, out_from_panorama.getNumSamples());
    buffer_bandPass_1.copyFrom(0, 0, out_from_panorama.getReadPointer(0), out_from_panorama.getNumSamples());
    buffer_bandPass_1.copyFrom(1, 0, out_from_panorama.getReadPointer(1), out_from_panorama.getNumSamples());

    buffer_bandPass_2.setSize(2, out_from_panorama.getNumSamples());
    buffer_bandPass_2.copyFrom(0, 0, out_from_panorama.getReadPointer(0), out_from_panorama.getNumSamples());
    buffer_bandPass_2.copyFrom(1, 0, out_from_panorama.getReadPointer(1), out_from_panorama.getNumSamples());

    buffer_bandPass_3.setSize(2, out_from_panorama.getNumSamples());
    buffer_bandPass_3.copyFrom(0, 0, out_from_panorama.getReadPointer(0), out_from_panorama.getNumSamples());
    buffer_bandPass_3.copyFrom(1, 0, out_from_panorama.getReadPointer(1), out_from_panorama.getNumSamples());

    buffer_bandPass_4.setSize(2, out_from_panorama.getNumSamples());
    buffer_bandPass_4.copyFrom(0, 0, out_from_panorama.getReadPointer(0), out_from_panorama.getNumSamples());
    buffer_bandPass_4.copyFrom(1, 0, out_from_panorama.getReadPointer(1), out_from_panorama.getNumSamples());

    buffer_lowPass.setSize(2, out_from_panorama.getNumSamples());
    buffer_lowPass.copyFrom(0, 0, out_from_panorama.getReadPointer(0), out_from_panorama.getNumSamples());
    buffer_lowPass.copyFrom(1, 0, out_from_panorama.getReadPointer(1), out_from_panorama.getNumSamples());

    buffer_highPass.setSize(2, out_from_panorama.getNumSamples());
    buffer_highPass.copyFrom(0, 0, out_from_panorama.getReadPointer(0), out_from_panorama.getNumSamples());
    buffer_highPass.copyFrom(1, 0, out_from_panorama.getReadPointer(1), out_from_panorama.getNumSamples());

    out_from_stereo_width.setSize(2, out_from_panorama.getNumSamples());

    
// audioblocki 

    dsp::AudioBlock<float> block_in(out_from_panorama);

    dsp::AudioBlock<float> block_lowPass(buffer_lowPass);
    dsp::AudioBlock<float> block_highPass(buffer_highPass);

    dsp::AudioBlock<float> block_band_1(buffer_bandPass_1); 

    dsp::AudioBlock<float> block_band_2(buffer_bandPass_2);


    dsp::AudioBlock<float> block_band_3(buffer_bandPass_3);


    dsp::AudioBlock<float> block_band_4(buffer_bandPass_4);

    dsp::AudioBlock<float> block_out_stereo(out_from_stereo_width);


    //filtrowanie do szerokosci
    //bass bez deleya
    gain.setGainDecibels(0);
    lowPass1.process(dsp::ProcessContextNonReplacing<float>(block_in, block_lowPass));
    //band1
    lowPass2.process(dsp::ProcessContextNonReplacing<float>(block_in, block_band_1));
    highPass1.process(dsp::ProcessContextReplacing<float>(block_band_1));
    //band2
    lowPass3.process(dsp::ProcessContextNonReplacing<float>(block_in, block_band_2));
    highPass2.process(dsp::ProcessContextReplacing<float>(block_band_2));
    //band3
    lowPass4.process(dsp::ProcessContextNonReplacing<float>(block_in, block_band_3));
    highPass3.process(dsp::ProcessContextReplacing<float>(block_band_3));
    gain.process(dsp::ProcessContextReplacing<float>(block_band_3));
    //band4
    lowPass5.process(dsp::ProcessContextNonReplacing<float>(block_in, block_band_4));
    highPass4.process(dsp::ProcessContextReplacing<float>(block_band_4));
    //reszta
    highPass5.process(dsp::ProcessContextNonReplacing<float>(block_in, block_highPass));

    float* leftBuffer = buffer.getWritePointer(0);
    float* rightBuffer = buffer.getWritePointer(1);

    const float* left_lowPass = buffer_lowPass.getReadPointer(0);
    const float* right_lowPass = buffer_lowPass.getReadPointer(1);

    float* left_band_1 = buffer_bandPass_1.getWritePointer(0);
    float* right_band_1 = buffer_bandPass_1.getWritePointer(1);
    
    float* left_band_2 = buffer_bandPass_2.getWritePointer(0);
    float* right_band_2 = buffer_bandPass_2.getWritePointer(1);

    float* left_band_3 = buffer_bandPass_3.getWritePointer(0);
    float* right_band_3 = buffer_bandPass_3.getWritePointer(1);
        
    float* left_band_4 = buffer_bandPass_4.getWritePointer(0);
    float* right_band_4 = buffer_bandPass_4.getWritePointer(1);

    const float* left_highPass = buffer_highPass.getReadPointer(0);
    const float* right_highPass = buffer_highPass.getReadPointer(1);

    float* out_l2 = out_from_stereo_width.getWritePointer(0);
    float* out_r2 = out_from_stereo_width.getWritePointer(1);
   



  //przetwarzanie
           for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
           {
               //sekcja delaya         
               float delay_1 = mAPVTS.getRawParameterValue("WIDTH")->load();
               auto input_1 = left_band_1[sample] -lastDelayOutput_1[0];
               auto delayAmount_1 = delay_1 / 1000.0 * getSampleRate();

               linear.pushSample(int(0), input_1);
               linear.setDelay((float)delayAmount_1);
               left_band_1[sample]= linear.popSample((int)0);
               lastDelayOutput_1[0] = left_band_1[sample] * delayFeedbackVolume[0].getNextValue();

               /// ////
               float delay_2 = mAPVTS.getRawParameterValue("WIDTH_2")->load();
               auto input_2 = left_band_2[sample] -lastDelayOutput_2[0];
               auto delayAmount_2 = delay_2 / 1000.0 * getSampleRate();

               linear_2.pushSample(int(0), input_2);
               linear_2.setDelay((float)delayAmount_2);
               left_band_2[sample] = linear_2.popSample((int)0);
               lastDelayOutput_2[0] = left_band_2[sample] * delayFeedbackVolume_2[0].getNextValue();

               /// ///
               float delay_3 = mAPVTS.getRawParameterValue("WIDTH_3")->load();
               auto input_3 = left_band_3[sample]-lastDelayOutput_3[0];
               auto delayAmount_3 = delay_3 / 1000.0 * getSampleRate();

               linear_3.pushSample(int(0), input_3);
               linear_3.setDelay((float)delayAmount_3);
               left_band_3[sample] = linear_3.popSample((int)0);
               lastDelayOutput_3[0] = left_band_3[sample] * delayFeedbackVolume_3[0].getNextValue();

               /// ///
               float delay_4 = mAPVTS.getRawParameterValue("WIDTH_4")->load();
               auto input_4 = left_band_4[sample]- lastDelayOutput_4[0];
               auto delayAmount_4 = delay_4 / 1000.0 * getSampleRate();

               linear_4.pushSample(int(0), input_4);
               linear_4.setDelay((float)delayAmount_4);
               left_band_4[sample] = linear_4.popSample((int)0);
               lastDelayOutput_4[0] = left_band_4[sample] * delayFeedbackVolume_4[0].getNextValue();
  

                 out_l2[sample] = left_lowPass[sample] + left_band_1[sample] + left_band_2[sample] + left_band_3[sample] + left_band_4[sample] + left_highPass[sample];
                 out_r2[sample] = right_lowPass[sample] + right_band_1[sample] + right_band_2[sample] + right_band_3[sample] + right_band_4[sample] + right_highPass[sample];
           }

            mixer.pushDrySamples(block_in);
            float dry_wet_val = mAPVTS.getRawParameterValue("DRY_WET")->load();
            mixer.setWetMixProportion(dry_wet_val/100);
            mixer.mixWetSamples(block_out_stereo);
           for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
           {
               float side_val = mAPVTS.getRawParameterValue("WIDTH_SIDE")->load();
               float mid_val = mAPVTS.getRawParameterValue("WIDTH_MID")->load();
               float width_val = mAPVTS.getRawParameterValue("WIDTH_MS")->load();
               
               MSWidth::MidSideWidth(&out_l2[sample], &out_r2[sample], side_val, mid_val, width_val);
               float numMenu = mAPVTS.getRawParameterValue("INVERT_MENU")->load();
               Phase::invert(&out_l2[sample], &out_r2[sample], numMenu);
               float click = mAPVTS.getRawParameterValue("BUTTON")->load();
               Phase::mono(&out_l2[sample], &out_r2[sample], click);

               leftBuffer[sample] = out_l2[sample];
               rightBuffer[sample] = out_r2[sample];
           }


}


//==============================================================================



bool Stereo_vstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Stereo_vstAudioProcessor::createEditor()
{
	
    return new Stereo_vstAudioProcessorEditor (*this);
	
}

//==============================================================================
void Stereo_vstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = mAPVTS.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Stereo_vstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
     
    if (xmlState.get() != nullptr)
       if (xmlState->hasTagName(mAPVTS.state.getType()))
            mAPVTS.replaceState(juce::ValueTree::fromXml(*xmlState));
}


AudioProcessorValueTreeState::ParameterLayout Stereo_vstAudioProcessor::createParameters()
{
    AudioProcessorValueTreeState::ParameterLayout layout;


    layout.add(std::make_unique<AudioParameterFloat>("PANORAMA", "Panorama", -100.0f, 100.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>("PANORAMA_freq_min", "Panorama_freq_min", 5.0f, 20000.f, 1.0f));
    layout.add(std::make_unique<AudioParameterFloat>("PANORAMA_freq_max", "Panorama_freq_max", 5.0f, 20000.f, 1.0f));
    layout.add(std::make_unique<AudioParameterFloat>("Q_SLIDER", "Q_slider", 0.025f, 2.f, 0.025f));

    layout.add(std::make_unique<AudioParameterFloat>("WIDTH_SIDE", "Width_Side", 0.1f, 2.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>("WIDTH_MID", "Width_Mid", 0.1f, 2.0f, 0.1f));

    layout.add(std::make_unique<AudioParameterFloat>("WIDTH_MS", "Width_MS", 0.0f, 1.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>("DISTANCE", "Distance", 0.0f, 1.0f, 0.05f));


    layout.add(std::make_unique<AudioParameterFloat>("WIDTH", "Width", 0.0f, 30.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>("WIDTH_2", "Width_2", 0.0f, 30.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>("WIDTH_3", "Width_3", 0.0f, 30.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>("WIDTH_4", "Width_4", 0.0f, 30.0f, 0.1f));
    layout.add(std::make_unique<AudioParameterFloat>("BAND_1", "Band_1", 5.f, 250.0f, 0.5f));
    layout.add(std::make_unique<AudioParameterFloat>("BAND_2", "Band_2", 250.f, 800.0f, 0.5f));
    layout.add(std::make_unique<AudioParameterFloat>("BAND_3", "Band_3", 800.f, 4000.0f, 0.5f));
    layout.add(std::make_unique<AudioParameterFloat>("BAND_4", "Band_4", 4000.f, 8000.0f, 0.5f));
    layout.add(std::make_unique<AudioParameterFloat>("BAND_5", "Band_5", 8000.f, 20000.0f, 0.5f));

    layout.add(std::make_unique<AudioParameterFloat>("INVERT_MENU", "Invert_menu", 1.0f, 4.0f, 1.0f));
    layout.add(std::make_unique<AudioParameterFloat>("BUTTON", "Button", 0.f, 1.f, 0.f));

    layout.add(std::make_unique<AudioParameterFloat>("DRY_WET", "Dry_wet", 0.0f, 100.0f, 1.0f));

    return layout;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Stereo_vstAudioProcessor();
}
