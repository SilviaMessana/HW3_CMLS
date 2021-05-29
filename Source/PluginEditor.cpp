/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistorionEffectAudioProcessorEditor::DistorionEffectAudioProcessorEditor (DistorionEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{


    //KNOBS/LABELS

    //OUTPUT

    addAndMakeVisible(outputKnob = new juce::Slider("Output"));
    outputKnob->setLookAndFeel(&myLookAndFeelV3);
    outputKnob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    outputKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    audioProcessor.getStateScopedPointer()->addParameterListener("output", this);
   



    addAndMakeVisible(outputLabel = new juce::Label("outputLabel"));
    outputLabel->setText("OUTPUT", juce::NotificationType::dontSendNotification);
    outputLabel->setJustificationType(juce::Justification::centred);
    outputLabel->setFont(juce::Font(20.0f, juce::Font::bold));
    outputLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));


    //DETUNE

    addAndMakeVisible(detuneKnob = new juce::Slider("Detune"));
    detuneKnob->setLookAndFeel(&myLookAndFeelV2);
    detuneKnob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    detuneKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    audioProcessor.getStateScopedPointer()->addParameterListener("detune", this);


    addAndMakeVisible(detuneLabel = new juce::Label("detuneLabel"));
    detuneLabel->setText("DETUNE", juce::NotificationType::dontSendNotification);
    detuneLabel->setJustificationType(juce::Justification::centred);
    detuneLabel->setFont(juce::Font(16.0f, juce::Font::bold));
    detuneLabel->setFont(juce::Font(20.0f, juce::Font::bold));
    detuneLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));


    //BLEND

    addAndMakeVisible(blendKnob = new juce::Slider("Blend"));
    blendKnob->setLookAndFeel(&myLookAndFeelV2);
    blendKnob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    blendKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    audioProcessor.getStateScopedPointer()->addParameterListener("blend", this);

    addAndMakeVisible(blendLabel = new juce::Label("blendLabel"));
    blendLabel->setText("BLEND", juce::NotificationType::dontSendNotification);
    blendLabel->setJustificationType(juce::Justification::centred);
    blendLabel->setFont(juce::Font(16.0f, juce::Font::bold));
    blendLabel->setFont(juce::Font(20.0f, juce::Font::bold));
    blendLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));

    //REVERB

    addAndMakeVisible(reverbKnob = new juce::Slider("Reverb"));
    reverbKnob->setLookAndFeel(&myLookAndFeelV2);
    reverbKnob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    reverbKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    audioProcessor.getStateScopedPointer()->addParameterListener("reverb", this);


    addAndMakeVisible(reverbLabel = new juce::Label("reverbLabel"));
    reverbLabel->setText("REVERB", juce::NotificationType::dontSendNotification);
    reverbLabel->setJustificationType(juce::Justification::centred);
    reverbLabel->setFont(juce::Font(16.0f, juce::Font::bold));
    reverbLabel->setFont(juce::Font(20.0f, juce::Font::bold));
    reverbLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));


    //VOICE1 

    addAndMakeVisible(voice1_secLabel = new juce::Label("voice1_secLabel"));
    voice1_secLabel->setText("VOICE 1", juce::NotificationType::dontSendNotification);
    voice1_secLabel->setJustificationType(juce::Justification::centred);
    voice1_secLabel->setFont(juce::Font(16.0f, juce::Font::bold));
    voice1_secLabel->setFont(juce::Font(20.0f, juce::Font::bold));
    voice1_secLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));


    addAndMakeVisible(voice1Knob = new juce::Slider("Voice 1"));
    voice1Knob->setLookAndFeel(&myLookAndFeelV1);
    voice1Knob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    voice1Knob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    audioProcessor.getStateScopedPointer()->addParameterListener("voice1", this);


    addAndMakeVisible(voice1Label = new juce::Label("voice1Label"));
    voice1Label->setText("OCTAVE", juce::NotificationType::dontSendNotification);
    voice1Label->setJustificationType(juce::Justification::centred);
    voice1Label->setFont(juce::Font(16.0f, juce::Font::bold));
    voice1Label->setFont(juce::Font(20.0f, juce::Font::bold));
    voice1Label->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));


    //VOLUME VOICE1 

     addAndMakeVisible(vol_v1Knob = new juce::Slider(" Volume Voice 1"));
     vol_v1Knob->setLookAndFeel(&myLookAndFeelV1);
     vol_v1Knob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
     vol_v1Knob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
     audioProcessor.getStateScopedPointer()->addParameterListener("vol_v1", this);

     addAndMakeVisible(voice1_volLabel = new juce::Label("voice1_volLabel"));
     voice1_volLabel->setText("VOLUME", juce::NotificationType::dontSendNotification);
     voice1_volLabel->setJustificationType(juce::Justification::centred);
     voice1_volLabel->setFont(juce::Font(16.0f, juce::Font::bold));
     voice1_volLabel->setFont(juce::Font(20.0f, juce::Font::bold));
     voice1_volLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));



    //VOICE2

     addAndMakeVisible(voice2_secLabel = new juce::Label("voice2_secLabel"));
     voice2_secLabel->setText("VOICE 2", juce::NotificationType::dontSendNotification);
     voice2_secLabel->setJustificationType(juce::Justification::centred);
     voice2_secLabel->setFont(juce::Font(16.0f, juce::Font::bold));
     voice2_secLabel->setFont(juce::Font(20.0f, juce::Font::bold));
     voice2_secLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));

     addAndMakeVisible(voice2Knob = new juce::Slider("Voice 2"));
     voice2Knob->setLookAndFeel(&myLookAndFeelV1);
     voice2Knob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
     voice2Knob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
     audioProcessor.getStateScopedPointer()->addParameterListener("voice2", this);

     addAndMakeVisible(voice2Label = new juce::Label("voice2Label"));
     voice2Label->setText("OCTAVE", juce::NotificationType::dontSendNotification);
     voice2Label->setJustificationType(juce::Justification::centred);
     voice2Label->setFont(juce::Font(16.0f, juce::Font::bold));
     voice2Label->setFont(juce::Font(20.0f, juce::Font::bold));
     voice2Label->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));

     

     //VOLUME VOICE2

     addAndMakeVisible(vol_v2Knob = new juce::Slider("Volume Voice 2"));
     vol_v2Knob->setLookAndFeel(&myLookAndFeelV1);
     vol_v2Knob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
     vol_v2Knob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
     audioProcessor.getStateScopedPointer()->addParameterListener("vol_v2", this);

     addAndMakeVisible(voice2_volLabel = new juce::Label("voice2_volLabel"));
     voice2_volLabel->setText("VOLUME", juce::NotificationType::dontSendNotification);
     voice2_volLabel->setJustificationType(juce::Justification::centred);
     voice2_volLabel->setFont(juce::Font(16.0f, juce::Font::bold));
     voice2_volLabel->setFont(juce::Font(20.0f, juce::Font::bold));
     voice2_volLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));

     



     //VOICE3 

     addAndMakeVisible(voice3_secLabel = new juce::Label("voice3_secLabel"));
     voice3_secLabel->setText("VOICE 3", juce::NotificationType::dontSendNotification);
     voice3_secLabel->setJustificationType(juce::Justification::centred);
     voice3_secLabel->setFont(juce::Font(16.0f, juce::Font::bold));
     voice3_secLabel->setFont(juce::Font(20.0f, juce::Font::bold));
     voice3_secLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));


     addAndMakeVisible(voice3Knob = new juce::Slider("Voice 3"));
     voice3Knob->setLookAndFeel(&myLookAndFeelV1);
     voice3Knob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
     voice3Knob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
     audioProcessor.getStateScopedPointer()->addParameterListener("voice3", this);

     addAndMakeVisible(voice3Label = new juce::Label("voice3Label"));
     voice3Label->setText("OCTAVE", juce::NotificationType::dontSendNotification);
     voice3Label->setJustificationType(juce::Justification::centred);
     voice3Label->setFont(juce::Font(16.0f, juce::Font::bold));
     voice3Label->setFont(juce::Font(20.0f, juce::Font::bold));
     voice3Label->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));

     
     //VOICE3 

     addAndMakeVisible(vol_v3Knob = new juce::Slider("Volume Voice 3"));
     vol_v3Knob->setLookAndFeel(&myLookAndFeelV1);
     vol_v3Knob->setSliderStyle(juce::Slider::RotaryVerticalDrag);
     vol_v3Knob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
     audioProcessor.getStateScopedPointer()->addParameterListener("vol_v3", this);

     addAndMakeVisible(voice3_volLabel = new juce::Label("voice3_volLabel"));
     voice3_volLabel->setText("VOLUME", juce::NotificationType::dontSendNotification);
     voice3_volLabel->setJustificationType(juce::Justification::centred);
     voice3_volLabel->setFont(juce::Font(16.0f, juce::Font::bold));
     voice3_volLabel->setFont(juce::Font(20.0f, juce::Font::bold));
     voice3_volLabel->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));

     


   
    //KNOB ATTACHMENTS

    outputAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "output", *outputKnob);
    blendAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);
    detuneAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "detune", *detuneKnob);
    reverbAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "reverb", *reverbKnob);
    voice1Attach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "voice1", *voice1Knob);
    voice2Attach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "voice2", *voice2Knob);
    voice3Attach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "voice3", *voice3Knob);
    vol_v1Attach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "vol_v1", *vol_v1Knob);
    vol_v2Attach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "vol_v2", *vol_v2Knob);
    vol_v3Attach = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "vol_v3", *vol_v3Knob);


   
    setSize (661, 615);
}

DistorionEffectAudioProcessorEditor::~DistorionEffectAudioProcessorEditor()
{
}

//==============================================================================
void DistorionEffectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawImageAt(juce::ImageCache::getFromMemory(BinaryData::sfondo_png, BinaryData::sfondo_pngSize), 0, 0);
}

void DistorionEffectAudioProcessorEditor::resized()
{

    //BOUNDS

    outputKnob->setBounds(((getWidth() / 5) * 2.5)- 75, (getHeight() / 2) -300, 130, 130);
    reverbKnob->setBounds(((getWidth() / 5) * 4.10) - (100 / 2), (getHeight() / 2)-120, 125, 125);
    detuneKnob->setBounds(((getWidth() / 5) * 0.75) - (100 / 2), (getHeight() / 2)-120, 125, 125);
    blendKnob->setBounds(((getWidth() / 5) * 2.5) - 75, (getHeight() / 2) - 120, 125, 125);
    voice1Knob->setBounds(((getWidth() / 5) * 3) - 250, (getHeight() / 2) + 75, 100, 100);
    voice2Knob->setBounds(((getWidth() / 5) * 4) - 250, (getHeight() / 2) + 75, 100, 100);
    voice3Knob->setBounds(((getWidth() / 5) * 5) - 250, (getHeight() / 2) + 75, 100, 100);
    vol_v1Knob->setBounds(((getWidth() / 5) * 3) - 250, (getHeight() / 2) + 175, 100, 100);
    vol_v2Knob->setBounds(((getWidth() / 5) * 4) - 250, (getHeight() / 2) + 175, 100, 100);
    vol_v3Knob->setBounds(((getWidth() / 5) * 5) - 250, (getHeight() / 2) + 175, 100, 100);


    outputLabel->setBounds(((getWidth() / 5) * 2.5) - 50, (getHeight() / 2) - 180, 80, 50);
    reverbLabel->setBounds(((getWidth() / 5) * 4.10) - (60 / 2), (getHeight() / 2) - 15 , 80, 50);
    detuneLabel->setBounds(((getWidth() / 5) * 0.75) - (60 / 2), (getHeight() / 2) - 15, 80, 50);
    blendLabel->setBounds(((getWidth() / 5) * 2.5) - 50, (getHeight() / 2) - 15, 80, 50);
    voice1_secLabel->setBounds(((getWidth() / 5) * 3) - 240, (getHeight() / 2) + 50, 80, 50);
    voice2_secLabel->setBounds(((getWidth() / 5) * 4) - 240, (getHeight() / 2) + 50, 80, 50);
    voice3_secLabel->setBounds(((getWidth() / 5) * 5) - 240, (getHeight() / 2) + 50, 80, 50);
    voice1Label->setBounds(((getWidth() / 5) * 3) - 240, (getHeight() / 2) + 150, 80, 50);
    voice2Label->setBounds(((getWidth() / 5) * 4) - 240, (getHeight() / 2) + 150, 80, 50);
    voice3Label->setBounds(((getWidth() / 5) * 5) - 240, (getHeight() / 2) + 150, 80, 50);
    voice1_volLabel->setBounds(((getWidth() / 5) * 3) - 240, (getHeight() / 2) + 250, 80, 50);
    voice2_volLabel->setBounds(((getWidth() / 5) * 4) - 240, (getHeight() / 2) + 250, 80, 50);
    voice3_volLabel->setBounds(((getWidth() / 5) * 5) - 240, (getHeight() / 2) + 250, 80, 50);
}



//4) SEND OSC MESSAGES WHEN SLIDER CHARACTERIZED BY "PARAMETERID" CHANGES
void DistorionEffectAudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
{

    //Input volume
    if (parameterID == "output") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }

    //Blend
    if (parameterID == "blend") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }


    //Detune
    if (parameterID == "detune") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }

    //Reverb
    if (parameterID == "reverb") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }


    //First Voice

    //Pitch
    if (parameterID == "voice1") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }

    //Volume
    if (parameterID == "vol_v1") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }


    //Second Voice

    //Pitch
    if (parameterID == "voice2") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }

    //Volume
    if (parameterID == "vol_v2") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }


    //Third Voice

    //Pitch
    if (parameterID == "voice3") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }

    //Volume
    if (parameterID == "vol_v3") {
        audioProcessor.sendOscInput(parameterID, newValue);
    }


}









