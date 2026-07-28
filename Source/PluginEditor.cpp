#include <juce_gui_extra/juce_gui_extra.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

MantraAudioProcessorEditor::MantraAudioProcessorEditor(MantraAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(800, 600);

    // Input stage
    inputGainSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*inputGainSlider);
    inputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "inputGain", *inputGainSlider);

    inputGainLabel = std::make_unique<juce::Label>("", "Input Gain");
    addAndMakeVisible(*inputGainLabel);
    inputGainLabel->attachToComponent(inputGainSlider.get(), false);

    // Drive
    driveSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*driveSlider);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "drive", *driveSlider);

    driveLabel = std::make_unique<juce::Label>("", "Drive");
    addAndMakeVisible(*driveLabel);
    driveLabel->attachToComponent(driveSlider.get(), false);

    // Tone
    toneSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*toneSlider);
    toneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "tone", *toneSlider);

    toneLabel = std::make_unique<juce::Label>("", "Tone");
    addAndMakeVisible(*toneLabel);
    toneLabel->attachToComponent(toneSlider.get(), false);

    // Bass
    bassSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*bassSlider);
    bassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "bass", *bassSlider);

    bassLabel = std::make_unique<juce::Label>("", "Bass");
    addAndMakeVisible(*bassLabel);
    bassLabel->attachToComponent(bassSlider.get(), false);

    // Mid
    midSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*midSlider);
    midAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "mid", *midSlider);

    midLabel = std::make_unique<juce::Label>("", "Mid");
    addAndMakeVisible(*midLabel);
    midLabel->attachToComponent(midSlider.get(), false);

    // Treble
    trebleSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*trebleSlider);
    trebleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "treble", *trebleSlider);

    trebleLabel = std::make_unique<juce::Label>("", "Treble");
    addAndMakeVisible(*trebleLabel);
    trebleLabel->attachToComponent(trebleSlider.get(), false);

    // Presence
    presenceSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*presenceSlider);
    presenceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "presence", *presenceSlider);

    presenceLabel = std::make_unique<juce::Label>("", "Presence");
    addAndMakeVisible(*presenceLabel);
    presenceLabel->attachToComponent(presenceSlider.get(), false);

    // Compressor Threshold
    compThresholdSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*compThresholdSlider);
    compThresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "compThreshold", *compThresholdSlider);

    compThresholdLabel = std::make_unique<juce::Label>("", "Comp Thresh");
    addAndMakeVisible(*compThresholdLabel);
    compThresholdLabel->attachToComponent(compThresholdSlider.get(), false);

    // Compressor Ratio
    compRatioSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*compRatioSlider);
    compRatioAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "compRatio", *compRatioSlider);

    compRatioLabel = std::make_unique<juce::Label>("", "Comp Ratio");
    addAndMakeVisible(*compRatioLabel);
    compRatioLabel->attachToComponent(compRatioSlider.get(), false);

    // Output Gain
    outputGainSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryVerticalDrag, juce::Slider::TextBoxBelow);
    addAndMakeVisible(*outputGainSlider);
    outputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "outputGain", *outputGainSlider);

    outputGainLabel = std::make_unique<juce::Label>("", "Output Gain");
    addAndMakeVisible(*outputGainLabel);
    outputGainLabel->attachToComponent(outputGainSlider.get(), false);
}

MantraAudioProcessorEditor::~MantraAudioProcessorEditor()
{
}

void MantraAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(30, 30, 35));

    g.setColour(juce::Colours::white);
    g.setFont(24.0f);
    g.drawText("MANTRA", getLocalBounds().removeFromTop(40), juce::Justification::centred, true);

    // Section labels
    g.setFont(14.0f);
    g.setColour(juce::Colour::fromRGB(150, 150, 150));

    g.drawText("INPUT", juce::Rectangle<int>(10, 50, 180, 20), juce::Justification::centred);
    g.drawText("TONE", juce::Rectangle<int>(210, 50, 180, 20), juce::Justification::centred);
    g.drawText("EQ", juce::Rectangle<int>(410, 50, 180, 20), juce::Justification::centred);
    g.drawText("DYNAMICS", juce::Rectangle<int>(610, 50, 180, 20), juce::Justification::centred);
}

void MantraAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    bounds.removeFromTop(60);

    int sliderX = 20;
    int sliderY = 80;
    int sliderWidth = 80;
    int sliderHeight = 140;
    int spacing = 190;

    // Input section
    inputGainSlider->setBounds(sliderX, sliderY, sliderWidth, sliderHeight);
    driveSlider->setBounds(sliderX + spacing / 2, sliderY, sliderWidth, sliderHeight);

    // Tone section
    toneSlider->setBounds(sliderX + spacing, sliderY, sliderWidth, sliderHeight);

    // EQ section
    bassSlider->setBounds(sliderX + spacing * 2, sliderY, sliderWidth, sliderHeight);
    midSlider->setBounds(sliderX + spacing * 2 + spacing / 2, sliderY, sliderWidth, sliderHeight);
    trebleSlider->setBounds(sliderX + spacing * 3, sliderY, sliderWidth, sliderHeight);
    presenceSlider->setBounds(sliderX + spacing * 3 + spacing / 2, sliderY, sliderWidth, sliderHeight);

    // Dynamics section
    compThresholdSlider->setBounds(sliderX + spacing * 4, sliderY, sliderWidth, sliderHeight);
    compRatioSlider->setBounds(sliderX + spacing * 4 + spacing / 2, sliderY, sliderWidth, sliderHeight);

    // Output section
    outputGainSlider->setBounds(sliderX + spacing * 5, sliderY, sliderWidth, sliderHeight);
}
