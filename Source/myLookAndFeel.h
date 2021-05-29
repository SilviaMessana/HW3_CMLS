/*
  ==============================================================================

    myLookAndFeel.h
    Created: 16 Apr 2021 5:41:46pm
    Author:  franc

  ==============================================================================
*/


#pragma once
#include <JuceHeader.h>

//==============================================================================
class myLookAndFeelV1 : public juce::LookAndFeel_V4
{
public:
    myLookAndFeelV1();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image img1;

};

//==============================================================================
class myLookAndFeelV2 : public juce::LookAndFeel_V4
{

public:
    myLookAndFeelV2();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image img2;

};

//==============================================================================


//==============================================================================
class myLookAndFeelV3 : public juce::LookAndFeel_V4
{

public:
    myLookAndFeelV3();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:

    juce::Image img3;

};

//==============================================================================

