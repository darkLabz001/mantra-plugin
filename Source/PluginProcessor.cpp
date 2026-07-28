#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

MantraAudioProcessor::MantraAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

MantraAudioProcessor::~MantraAudioProcessor()
{
}

void MantraAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    saturation.prepare(sampleRate, samplesPerBlock);
    eq.prepare(sampleRate, samplesPerBlock);
    compressor.prepare(sampleRate, samplesPerBlock);
}

void MantraAudioProcessor::releaseResources()
{
}

bool MantraAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void MantraAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Get parameter values from APVTS
    float inputGain = apvts.getRawParameterValue("inputGain")->load();
    float drive = apvts.getRawParameterValue("drive")->load();
    float tone = apvts.getRawParameterValue("tone")->load();
    float bassEQ = apvts.getRawParameterValue("bass")->load();
    float midEQ = apvts.getRawParameterValue("mid")->load();
    float trebleEQ = apvts.getRawParameterValue("treble")->load();
    float presence = apvts.getRawParameterValue("presence")->load();
    float compThreshold = apvts.getRawParameterValue("compThreshold")->load();
    float compRatio = apvts.getRawParameterValue("compRatio")->load();
    float outputGain = apvts.getRawParameterValue("outputGain")->load();

    // Apply input gain
    buffer.applyGain(inputGain);

    // Apply saturation/distortion
    saturation.processSaturation(buffer, drive, tone);

    // Apply compressor
    compressor.processCompression(buffer, compThreshold, compRatio);

    // Apply EQ
    eq.processEQ(buffer, bassEQ, midEQ, trebleEQ, presence);

    // Apply output gain
    buffer.applyGain(outputGain);
}

juce::AudioProcessorEditor* MantraAudioProcessor::createEditor()
{
    return new MantraAudioProcessorEditor(*this);
}

void MantraAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.state.toXmlString();
    destData.append(state.toRawUTF8(), state.getNumBytesAsUTF8());
}

void MantraAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto xmlString = juce::String::fromUTF8((const char*)data, sizeInBytes);
    auto xmlElement = std::unique_ptr<juce::XmlElement>(juce::XmlDocument::parse(xmlString));
    if (xmlElement != nullptr)
        apvts.state = juce::ValueTree::fromXml(*xmlElement);
}

juce::AudioProcessorValueTreeState::ParameterLayout MantraAudioProcessor::createParameterLayout()
{
    using Parameter = juce::AudioProcessorValueTreeState::Parameter;
    std::vector<std::unique_ptr<Parameter>> params;

    // Input stage
    params.push_back(std::make_unique<Parameter>(
        "inputGain", "Input Gain", "",
        juce::NormalisableRange<float>(0.0f, 4.0f, 0.01f), 1.0f,
        [](float value) { return juce::String(juce::Decibels::gainToDecibels(value), 1); },
        [](const juce::String& text) { return juce::Decibels::decibelsToGain(text.getFloatValue()); }
    ));

    // Drive/Saturation
    params.push_back(std::make_unique<Parameter>(
        "drive", "Drive", "",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f, nullptr, nullptr
    ));

    // Tone control
    params.push_back(std::make_unique<Parameter>(
        "tone", "Tone", "",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f, nullptr, nullptr
    ));

    // EQ controls
    params.push_back(std::make_unique<Parameter>(
        "bass", "Bass", "",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f,
        [](float value) { return juce::String(value, 1) + " dB"; },
        [](const juce::String& text) { return text.getFloatValue(); }
    ));

    params.push_back(std::make_unique<Parameter>(
        "mid", "Mid", "",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f,
        [](float value) { return juce::String(value, 1) + " dB"; },
        [](const juce::String& text) { return text.getFloatValue(); }
    ));

    params.push_back(std::make_unique<Parameter>(
        "treble", "Treble", "",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f,
        [](float value) { return juce::String(value, 1) + " dB"; },
        [](const juce::String& text) { return text.getFloatValue(); }
    ));

    params.push_back(std::make_unique<Parameter>(
        "presence", "Presence", "",
        juce::NormalisableRange<float>(-12.0f, 12.0f, 0.1f), 0.0f,
        [](float value) { return juce::String(value, 1) + " dB"; },
        [](const juce::String& text) { return text.getFloatValue(); }
    ));

    // Compressor
    params.push_back(std::make_unique<Parameter>(
        "compThreshold", "Compressor Threshold", "",
        juce::NormalisableRange<float>(-60.0f, 0.0f, 0.1f), -24.0f,
        [](float value) { return juce::String(value, 1) + " dB"; },
        [](const juce::String& text) { return text.getFloatValue(); }
    ));

    params.push_back(std::make_unique<Parameter>(
        "compRatio", "Compressor Ratio", "",
        juce::NormalisableRange<float>(1.0f, 16.0f, 0.1f), 4.0f,
        [](float value) { return juce::String(value, 1) + ":1"; },
        [](const juce::String& text) { return text.getFloatValue(); }
    ));

    // Output stage
    params.push_back(std::make_unique<Parameter>(
        "outputGain", "Output Gain", "",
        juce::NormalisableRange<float>(0.0f, 4.0f, 0.01f), 1.0f,
        [](float value) { return juce::String(juce::Decibels::gainToDecibels(value), 1); },
        [](const juce::String& text) { return juce::Decibels::decibelsToGain(text.getFloatValue()); }
    ));

    return { params.begin(), params.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MantraAudioProcessor();
}
