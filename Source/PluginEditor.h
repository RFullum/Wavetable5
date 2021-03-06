/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OtherLookAndFeel.h"
#include "OscVisual.h"
#include "FilterVisual.h"
#include "OutMeter.h"
#include "TitleHeader.h"

//==============================================================================
/**
*/
class DirtyLittleBassSynthAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    DirtyLittleBassSynthAudioProcessorEditor (DirtyLittleBassSynthAudioProcessor&);
    ~DirtyLittleBassSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    OtherLookAndFeel dialLookAndFeel;
    OtherLookAndFeel dryWetLookAndFeel;
    
    
    /// Sets up slider: Takes reference to a slider, the style of the slider, and the color of the fill
    void sliderSetup(Slider& sliderInstance, Slider::SliderStyle style, Colour& sliderFillColor,
                     Colour& sliderThumbColor, bool showTextBox);
    
    /// Sets up Label: Takes label reference, and the text
    void sliderLabelSetup(Label& labelInstance, String labelText, Colour& c, float fontSize);
    
    /// ComboBox setup
    void comboBoxSetup(ComboBox& boxInstance, StringArray boxItems);
    
    // Header area
    TitleHeader titleHeader;
    TitleFooter titleFooter;

    // Wavetable Drawing
    OscVisual oscVisual;
    OscVisual subOscVisual;
    OscVisual lfoVisual;
    
    Rectangle<int> oscVisualSpace;
    
    // Filter Drawing
    FilterVisual filterVisual;
    
    //Slider testSlider1;
    //Slider testSlider2;
    //Slider testSlider3;
    
    // Osc Section
    Slider oscMorphSlider;
    Slider subMorphSlider;
    Slider subGainSlider;
    Slider pitchBendRangeSlider;
    ComboBox subOctave;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> oscMorphSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> subMorphSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> subGainSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pitchBendRangeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> subOctaveAttachment;
    
    Label oscMorphLabel;
    Label oscMorphLabel2;
    Label subMorphLabel;
    Label subMorphLabel2;
    Label subGainLabel;
    Label pitchBendRangeLabel;
    
    // Osc ADSR Section
    Slider oscAttackSlider;
    Slider oscDecaySlider;
    Slider oscSustainSlider;
    Slider oscReleaseSlider;
    Slider portaSlider;
    Slider foldbackSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> oscAttackSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> oscDecaySliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> oscSustainSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> oscReleaseSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> portaSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> foldbackSliderAttachment;
    
    Label oscAttackLabel;
    Label oscDecayLabel;
    Label oscSustainLabel;
    Label oscReleaseLabel;
    Label portaLabel;
    Label foldbackLabel;
    
    // Modifiers Section
    Slider ringToneSlider;
    Slider ringPitchSlider;
    Slider ringDryWetSlider;
    Slider frqShftPitchSlider;
    Slider frqShftDryWetSlider;
    Slider sHPitchSlider;
    Slider sHDryWetSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ringToneSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ringPitchSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ringDryWetSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> frqShftPitchSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> frqShftDryWetSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sHPitchSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sHDryWetSliderAttachment;
    
    Label ringLabel;
    Label frqShftLabel;
    Label sHLabel;
    Label toneLabel;
    Label pitchLabel;
    Label dryWetLabel;
    
    // Filter Section
    Slider cutoffSlider;
    Slider resSlider;
    ComboBox filterType;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    
    Label cutoffLabel;
    Label resLabel;
    
    // Filter ADSR Section
    Slider fltAttackSlider;
    Slider fltDecaySlider;
    Slider fltSustainSlider;
    Slider fltReleaseSlider;
    Slider adsrToCutoffSlider;
    Slider adsrToResSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fltAttackSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fltDecaySliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fltSustainSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> fltReleaseSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> adsrToCutoffSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> adsrToResSliderAttachment;
    
    Label fltAttackLabel;
    Label fltDecayLabel;
    Label fltSustainLabel;
    Label fltReleaseLabel;
    Label adsrToCutoffLabel;
    Label adsrToResLabel;
    
    
    // Filter LFO Section
    Slider lfoShapeSlider;
    Slider lfoFreqSlider;
    Slider lfoAmountSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoShapeSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoFreqSliderAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoAmountSliderAttachment;
    
    Label lfoShapeLabel;
    Label lfoFreqLabel;
    Label lfoAmountLabel;
    
    // Main Out Section
    Slider masterGainSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterGainSliderAttachment;
    
    Label masterGainLabel;
    
    OutMeter outMeter;
    
    
    // Colors
    Colour onyx;
    Colour lightSlateGray;
    Colour magicMint;
    Colour fieryRose;
    Colour orangePeel;
    Colour textColor;
    
    
    // Subsections
    Rectangle<float> headerAreaInner;       // Header
    Rectangle<float> mainOutAreaInner;      // Main Out
    Rectangle<float> oscSectionInner;       // Oscillators
    Rectangle<float> mainOscSectionInner;   // Main Oscillator
    Rectangle<float> subOscSectionInner;    // Sub Oscillator
    Rectangle<float> oscADSRSectionInner;   // ADSR
    Rectangle<float> oscADSRSlidersInner;   // ADSR
    Rectangle<float> adsrRotaryInner;       // Porta/Foldback
    Rectangle<float> modSectionInner;       // Modifiers
    Rectangle<float> ringModSectionInner;   // Ring Mod
    Rectangle<float> frqShftSectionInner;   // Freq Shift
    Rectangle<float> sAndHSectionInner;     // S&H
    Rectangle<float> bottomSectionInner;    // Entire Bottom
    Rectangle<float> filterSectionInner;    // Filter
    Rectangle<float> fltADSRSectionInner;   // Filter ADSR
    Rectangle<float> lfoSectionInner;       // LFO
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DirtyLittleBassSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirtyLittleBassSynthAudioProcessorEditor)
};
