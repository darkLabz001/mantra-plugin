#include "Compressor.h"

void Compressor::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    lastEnvelope = 0.0f;
}

void Compressor::processCompression(juce::AudioBuffer<float>& buffer, float threshold, float ratio)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    // Convert parameters from dB to linear
    float thresholdLinear = juce::Decibels::decibelsToGain(threshold);

    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* channelData = buffer.getWritePointer(ch);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Get input level
            float input = std::abs(channelData[sample]);

            // Calculate envelope (peak detector)
            float envelope = calculateEnvelope(input, lastEnvelope);

            // Calculate gain reduction
            float gainReduction = 1.0f;
            if (envelope > thresholdLinear)
            {
                float dbOverThreshold = juce::Decibels::gainToDecibels(envelope / thresholdLinear);
                float dbReduction = dbOverThreshold * (1.0f - 1.0f / ratio);
                gainReduction = juce::Decibels::decibelsToGain(-dbReduction);
            }

            // Apply gain reduction
            channelData[sample] *= gainReduction;
        }
    }
}

float Compressor::calculateEnvelope(float input, float& lastEnv)
{
    float attackCoeff = std::exp(-1.0f / (ATTACK_TIME * sampleRate));
    float releaseCoeff = std::exp(-1.0f / (RELEASE_TIME * sampleRate));

    float coeff = (input > lastEnv) ? attackCoeff : releaseCoeff;
    lastEnv = input + coeff * (lastEnv - input);

    return lastEnv;
}
