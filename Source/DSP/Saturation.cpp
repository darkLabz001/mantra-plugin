#include "Saturation.h"

void Saturation::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;
}

void Saturation::processSaturation(juce::AudioBuffer<float>& buffer, float drive, float tone)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* channelData = buffer.getWritePointer(ch);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Apply waveshaper with drive
            float processedSample = waveshaper(channelData[sample], drive);

            // Tone control - simple low-pass filter simulation
            processedSample = softClip(processedSample);

            channelData[sample] = processedSample;
        }
    }
}

float Saturation::softClip(float input)
{
    // Soft clipping using tanh for smooth saturation
    if (input > 1.0f)
        return std::tanh(input);
    else if (input < -1.0f)
        return std::tanh(input);
    else
        return input;
}

float Saturation::waveshaper(float input, float drive)
{
    // Apply gain based on drive
    float driven = input * (1.0f + drive * 10.0f);

    // Hard clipping
    driven = std::max(-1.0f, std::min(1.0f, driven));

    // Additional soft clipping for smoothness
    return std::tanh(driven * 1.5f);
}
