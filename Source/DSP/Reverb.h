#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <vector>

class CombFilter
{
public:
    CombFilter() = default;

    void prepare(int size)
    {
        buffer.resize(size, 0.0f);
        bufferIndex = 0;
    }

    float process(float input, float feedback)
    {
        float output = buffer[bufferIndex];
        buffer[bufferIndex] = input + (output * feedback);
        bufferIndex = (bufferIndex + 1) % (int)buffer.size();
        return output;
    }

    void reset()
    {
        std::fill(buffer.begin(), buffer.end(), 0.0f);
        bufferIndex = 0;
    }

private:
    std::vector<float> buffer;
    int bufferIndex = 0;
};

class AllpassFilter
{
public:
    AllpassFilter() = default;

    void prepare(int size)
    {
        buffer.resize(size, 0.0f);
        bufferIndex = 0;
    }

    float process(float input)
    {
        float output = buffer[bufferIndex];
        buffer[bufferIndex] = input + (output * 0.5f);
        bufferIndex = (bufferIndex + 1) % (int)buffer.size();
        return output - input;
    }

    void reset()
    {
        std::fill(buffer.begin(), buffer.end(), 0.0f);
        bufferIndex = 0;
    }

private:
    std::vector<float> buffer;
    int bufferIndex = 0;
};

class Reverb
{
public:
    Reverb() = default;
    ~Reverb() = default;

    void prepare(double sampleRate, int samplesPerBlock);
    void processReverb(juce::AudioBuffer<float>& buffer, float roomSize, float width, float wet, float dry);
    void reset();

private:
    // Comb filter tunings (in samples at 44.1kHz)
    static constexpr int COMB_TUNINGS[] = {1116, 1188, 1277, 1356};
    static constexpr int ALLPASS_TUNINGS[] = {225, 556, 441, 341};

    std::vector<CombFilter> combFilters;
    std::vector<AllpassFilter> allpassFilters;

    double sampleRate = 44100.0;
    float lastRoomSize = 0.5f;
};
