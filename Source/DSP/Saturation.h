#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>

class Saturation
{
public:
    Saturation() = default;
    ~Saturation() = default;

    void prepare(double sampleRate, int samplesPerBlock);
    void processSaturation(juce::AudioBuffer<float>& buffer, float drive, float tone);

private:
    double sampleRate = 44100.0;

    float softClip(float input);
    float waveshaper(float input, float drive);
};
