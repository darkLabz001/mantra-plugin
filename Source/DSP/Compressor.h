#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

class Compressor
{
public:
    Compressor() = default;
    ~Compressor() = default;

    void prepare(double sampleRate, int samplesPerBlock);
    void processCompression(juce::AudioBuffer<float>& buffer, float threshold, float ratio);

private:
    double sampleRate = 44100.0;
    float lastEnvelope = 0.0f;

    static constexpr float ATTACK_TIME = 0.005f;   // 5ms
    static constexpr float RELEASE_TIME = 0.1f;    // 100ms

    float calculateEnvelope(float input, float& lastEnv);
};
