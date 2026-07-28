#include "Reverb.h"

void Reverb::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    if (sampleRate < 8000) sampleRate = 44100.0;

    combFilters.clear();
    allpassFilters.clear();

    // Initialize comb filters with tuned delays
    for (int tuning : COMB_TUNINGS)
    {
        int delaySize = std::max(1, (int)((tuning * sampleRate) / 44100.0));
        combFilters.emplace_back();
        combFilters.back().prepare(delaySize);
    }

    // Initialize allpass filters
    for (int tuning : ALLPASS_TUNINGS)
    {
        int delaySize = std::max(1, (int)((tuning * sampleRate) / 44100.0));
        allpassFilters.emplace_back();
        allpassFilters.back().prepare(delaySize);
    }
}

void Reverb::processReverb(juce::AudioBuffer<float>& buffer, float roomSize, float width, float wet, float dry)
{
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();

    if (combFilters.empty() || allpassFilters.empty())
        return;  // Not prepared

    // Clamp parameters
    roomSize = std::max(0.0f, std::min(1.0f, roomSize));
    width = std::max(0.0f, std::min(1.0f, width));
    wet = std::max(0.0f, std::min(1.0f, wet));
    dry = std::max(0.0f, std::min(1.0f, dry));

    // Feedback amount based on room size
    float feedback = std::max(0.1f, std::min(0.99f, roomSize * 0.84f + 0.15f));

    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* channelData = buffer.getWritePointer(ch);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float input = channelData[sample];
            float damp = 0.2f;

            // Process through parallel comb filters
            float combOutput = 0.0f;
            for (size_t i = 0; i < combFilters.size(); ++i)
            {
                combOutput += combFilters[i].process(input, feedback);
            }
            combOutput *= 0.015f; // Gain compensation

            // Process through series allpass filters
            float allpassOutput = combOutput;
            for (auto& allpass : allpassFilters)
            {
                allpassOutput = allpass.process(allpassOutput);
            }

            // Mix wet and dry signals
            float wetSignal = allpassOutput;
            float output = (input * dry) + (wetSignal * wet);

            // Denormal protection
            if (std::isnan(output) || std::isinf(output))
                output = 0.0f;

            // Prevent clipping
            output = std::max(-1.0f, std::min(1.0f, output));
            channelData[sample] = output;
        }
    }
}

void Reverb::reset()
{
    for (auto& comb : combFilters)
        comb.reset();

    for (auto& allpass : allpassFilters)
        allpass.reset();
}
