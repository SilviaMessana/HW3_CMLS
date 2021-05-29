/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "myLookAndFeel.h"
#include "PluginProcessor.h"



//==============================================================================
/**
*/
class DistorionEffectAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::AudioProcessorValueTreeState::Listener
{
public:
    DistorionEffectAudioProcessorEditor (DistorionEffectAudioProcessor&);
    ~DistorionEffectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //4) function that send slider values through osc when sliders change 
    

private:
    
    //KNOBS DECLARATION
    
    juce::ScopedPointer<juce::Slider> outputKnob;
    juce::ScopedPointer<juce::Slider> detuneKnob;
    juce::ScopedPointer<juce::Slider> blendKnob;
    juce::ScopedPointer<juce::Slider> reverbKnob;
    juce::ScopedPointer<juce::Slider> voice1Knob;
    juce::ScopedPointer<juce::Slider> voice2Knob;
    juce::ScopedPointer<juce::Slider> voice3Knob;
    juce::ScopedPointer<juce::Slider> vol_v1Knob;
    juce::ScopedPointer<juce::Slider> vol_v2Knob;
    juce::ScopedPointer<juce::Slider> vol_v3Knob;

    //SLIDER ATTACHMENT DECLARATION

    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> detuneAttach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> reverbAttach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> voice1Attach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> voice2Attach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> voice3Attach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> vol_v1Attach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> vol_v2Attach;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> vol_v3Attach;


    //LABELS DECLARATION
    juce::ScopedPointer<juce::Label> outputLabel;
    juce::ScopedPointer<juce::Label> detuneLabel;
    juce::ScopedPointer<juce::Label> blendLabel;
    juce::ScopedPointer<juce::Label> reverbLabel;
    juce::ScopedPointer<juce::Label> voice1Label;
    juce::ScopedPointer<juce::Label> voice2Label;
    juce::ScopedPointer<juce::Label> voice3Label;
    juce::ScopedPointer<juce::Label> voice1_volLabel;
    juce::ScopedPointer<juce::Label> voice2_volLabel;
    juce::ScopedPointer<juce::Label> voice3_volLabel;

    juce::ScopedPointer<juce::Label> voice1_secLabel;
    juce::ScopedPointer<juce::Label> voice2_secLabel;
    juce::ScopedPointer<juce::Label> voice3_secLabel;


    //LOOK AND FEEL

    myLookAndFeelV1 myLookAndFeelV1;
    myLookAndFeelV2 myLookAndFeelV2;
    myLookAndFeelV3 myLookAndFeelV3;

    //PROCESSOR PRIVATE ATTRIBUTE
    DistorionEffectAudioProcessor& audioProcessor;


     
    //FUNCTION CALLED EVERYTIME A KNOB VALUE IS CHANGED
    void parameterChanged(const juce::String& parameterID,   float 	newValue ) override; 



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistorionEffectAudioProcessorEditor)
};
