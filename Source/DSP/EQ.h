#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

class EQ
{
public:
    EQ() = default;
    ~EQ() = default;

    void prepare(double sampleRate, int samplesPerBlock);
    void processEQ(juce::AudioBuffer<float>& buffer, float bass, float mid, float treble, float presence);

private:
    double sampleRate = 44100.0;

    juce::dsp::ProcessorChain<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Filter<float>,
                             juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Filter<float>> eqChain;

    void updateEQ(float bass, float mid, float treble, float presence);
};
