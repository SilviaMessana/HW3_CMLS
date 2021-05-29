/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistorionEffectAudioProcessor::DistorionEffectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    //STATE INITIALIZATION
    state = new juce::AudioProcessorValueTreeState(*this, nullptr);


    //STATE PARAMETERS

    state->createAndAddParameter("output", "Output", "Output", juce::NormalisableRange<float>(0.001f, 1.0f, 0.0001), 1.0f, nullptr, nullptr); 
    

    state->createAndAddParameter("detune", "Detune", "Detune", juce::NormalisableRange<float>(0.97f, 1.03f, 0.001), 1.0f, nullptr, nullptr);


    state->createAndAddParameter("reverb", "Reverb", "Reverb", juce::NormalisableRange<float>(0.01f, 1.0f, 0.0001), 0.0f, nullptr, nullptr);
  


    state->createAndAddParameter("blend", "Blend", "Blend", juce::NormalisableRange<float>(0.01f, 1.0f, 0.0001), 0.5f, nullptr, nullptr);



    state->createAndAddParameter("voice1", "Voice1", "Voice1", juce::NormalisableRange<float>(-2.0f, +2.0f, 1.0), 0.0f, nullptr, nullptr);



    state->createAndAddParameter("voice2", "Voice2", "Voice2", juce::NormalisableRange<float>(-2.0f, +2.0f, 1.0), 0.0f, nullptr, nullptr);



    state->createAndAddParameter("voice3", "Voice3", "Voice3", juce::NormalisableRange<float>(-2.0f, +2.0f, 1.0), 0.0f, nullptr, nullptr);



    state->createAndAddParameter("vol_v1", "Volume_Voice1", "Volume_Voice1", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001), 0.0f, nullptr, nullptr);



    state->createAndAddParameter("vol_v2", "Volume_Voice2", "Volume_Voice2", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001), 0.0f, nullptr, nullptr);



    state->createAndAddParameter("vol_v3", "Volume_Voice3", "Volume_Voice3", juce::NormalisableRange<float>(0.0f, 1.0f, 0.001), 0.0f, nullptr, nullptr);



    //VALUE TREES


    state->state = juce::ValueTree("output");
    state->state = juce::ValueTree("detune");
    state->state = juce::ValueTree("blend");
    state->state = juce::ValueTree("reverb");
    state->state = juce::ValueTree("voice1");
    state->state = juce::ValueTree("voice2");
    state->state = juce::ValueTree("voice3");
    state->state = juce::ValueTree("vol_v1");
    state->state = juce::ValueTree("vol_v2");
    state->state = juce::ValueTree("vol_v3");

    //2) SETTING UP CONNECTION 
    sender.connect("127.0.0.1", 57120); 

}

DistorionEffectAudioProcessor::~DistorionEffectAudioProcessor()
{
}

//==============================================================================
const juce::String DistorionEffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistorionEffectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool DistorionEffectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool DistorionEffectAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double DistorionEffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistorionEffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistorionEffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistorionEffectAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String DistorionEffectAudioProcessor::getProgramName(int index)
{
    return {};
}

void DistorionEffectAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void DistorionEffectAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{

    //SET INITIAL VALUES
    (state->getParameter("output"))->setValue(0.5f);
    (state->getParameter("detune"))->setValue(0.5f);
    (state->getParameter("blend"))->setValue(0.5f);
    (state->getParameter("reverb"))->setValue(0.0f);
    (state->getParameter("voice1"))->setValue(0.5f);
    (state->getParameter("voice2"))->setValue(0.5f);
    (state->getParameter("voice3"))->setValue(0.5f);
    (state->getParameter("vol_v1"))->setValue(0.0f);
    (state->getParameter("vol_v2"))->setValue(0.0f);
    (state->getParameter("vol_v3"))->setValue(0.0f);

}

void DistorionEffectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistorionFxAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void DistorionEffectAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());


}

//==============================================================================
bool DistorionEffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistorionEffectAudioProcessor::createEditor()
{
    return new DistorionEffectAudioProcessorEditor(*this);

}



void DistorionEffectAudioProcessor::sendOscInput(const juce::String& parameterID,  float val)
{
    //SEND OSC MESSAGE TO "/" + PARAMETER ID OSC METHOD
    juce::String parameter = "/" + parameterID;
    sender.send(parameter, val); 
}




juce::AudioProcessorValueTreeState& DistorionEffectAudioProcessor::getState() {

    
    return *state;

}

//3) 
juce::ScopedPointer<juce::AudioProcessorValueTreeState>& DistorionEffectAudioProcessor::getStateScopedPointer()
{
    return state; 
}

//==============================================================================
void DistorionEffectAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);



}

void DistorionEffectAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);

    if (tree.isValid()) {

        state->state = tree;

    }

}






//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistorionEffectAudioProcessor();
}
