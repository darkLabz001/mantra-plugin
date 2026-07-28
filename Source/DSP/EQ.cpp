#include "EQ.h"

void EQ::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;

    eqChain.prepare(spec);
}

void EQ::processEQ(juce::AudioBuffer<float>& buffer, float bass, float mid, float treble, float presence)
{
    updateEQ(bass, mid, treble, presence);

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    eqChain.process(context);
}

void EQ::updateEQ(float bass, float mid, float treble, float presence)
{
    // Bass - Low shelf around 100 Hz
    auto& bassFilter = eqChain.get<0>();
    auto bassCoeffs = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 100.0f, 0.707f,
                                                                        juce::Decibels::decibelsToGain(bass));
    *bassFilter.coefficients = *bassCoeffs;

    // Mid - Simple first-order shelving (substitute for peaking)
    auto& midFilter = eqChain.get<1>();
    auto midCoeffs = juce::dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 1000.0f, 0.707f,
                                                                       juce::Decibels::decibelsToGain(mid));
    *midFilter.coefficients = *midCoeffs;

    // Treble - High shelf around 8 kHz
    auto& trebleFilter = eqChain.get<2>();
    auto trebleCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 8000.0f, 0.707f,
                                                                           juce::Decibels::decibelsToGain(treble));
    *trebleFilter.coefficients = *trebleCoeffs;

    // Presence - High shelf around 3 kHz
    auto& presenceFilter = eqChain.get<3>();
    auto presenceCoeffs = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 3000.0f, 0.707f,
                                                                             juce::Decibels::decibelsToGain(presence));
    *presenceFilter.coefficients = *presenceCoeffs;
}
