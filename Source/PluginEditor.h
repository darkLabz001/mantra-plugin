#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

class MantraAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MantraAudioProcessorEditor(MantraAudioProcessor&);
    ~MantraAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    MantraAudioProcessor& audioProcessor;

    std::unique_ptr<juce::Slider> inputGainSlider, driveSlider, toneSlider;
    std::unique_ptr<juce::Slider> bassSlider, midSlider, trebleSlider, presenceSlider;
    std::unique_ptr<juce::Slider> compThresholdSlider, compRatioSlider;
    std::unique_ptr<juce::Slider> outputGainSlider;

    std::unique_ptr<juce::Label> inputGainLabel, driveLabel, toneLabel;
    std::unique_ptr<juce::Label> bassLabel, midLabel, trebleLabel, presenceLabel;
    std::unique_ptr<juce::Label> compThresholdLabel, compRatioLabel;
    std::unique_ptr<juce::Label> outputGainLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trebleAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> presenceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> compThresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> compRatioAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MantraAudioProcessorEditor)
};
