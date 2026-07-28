# 🎸 Mantra - VST3 Guitar Amp Modeling Plugin

A full-featured guitar amp simulator plugin built with **JUCE** and **C++17**.

## Features

- **Input Gain** - Drive signal into saturation stage
- **Saturation/Drive** - Waveshaper-based distortion with smooth clipping
- **Tone Control** - Shape the character of the distortion
- **4-Band Parametric EQ**
  - Bass (100 Hz low shelf)
  - Mid (1 kHz shelving)
  - Treble (8 kHz high shelf)
  - Presence (3 kHz shelving)
- **Dynamic Compressor** - Adjustable threshold and compression ratio
- **Reverb** - Room simulation with size, width, and wet/dry controls
- **Output Gain** - Final level adjustment

## Audio Processing Chain

```
Input → Input Gain → Saturation → Compressor → EQ → Reverb → Output Gain → Output
```

## Building

### Requirements
- CMake 3.22+
- C++17 compatible compiler (GCC, Clang, MSVC)
- JUCE framework (automatically downloaded by CMake)

### Linux Build
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

The compiled VST3 plugin will be at:
```
build/MantraPlugin_artefacts/Release/VST3/Mantra.vst3
```

### Installation
Copy the plugin to your DAW's VST3 directory:
```bash
# Linux
cp -r build/MantraPlugin_artefacts/Release/VST3/Mantra.vst3 ~/.vst3/
```

## Usage

1. **Install the plugin** in your DAW's VST3 folder
2. **Scan for plugins** in your DAW
3. **Load Mantra** on an audio track
4. **Adjust parameters** using your DAW's plugin interface

### Recommended Settings

**Light Distortion (Clean with Reverb):**
- Input Gain: 1.2x
- Drive: 0.3
- Tone: 0.5
- Bass: +2 dB
- Treble: +3 dB
- Reverb Room: 0.4, Wet: 0.25
- Output Gain: 0.9x

**Medium Distortion (Rock):**
- Input Gain: 1.5x
- Drive: 0.6
- Tone: 0.5
- Bass: +4 dB
- Mid: +2 dB
- Treble: +5 dB
- Presence: +3 dB
- Comp Threshold: -20 dB
- Reverb Room: 0.5, Wet: 0.3
- Output Gain: 0.8x

**Heavy Distortion (Metal):**
- Input Gain: 2.0x
- Drive: 0.9
- Tone: 0.7
- Bass: +8 dB
- Treble: +8 dB
- Comp Ratio: 6:1
- Reverb Room: 0.3, Wet: 0.2
- Output Gain: 0.5x

**Ambient/Spacey:**
- Input Gain: 0.8x
- Drive: 0.2
- Bass: +2 dB
- Treble: +4 dB
- Reverb Room: 0.9, Width: 1.0, Wet: 0.6, Dry: 0.4
- Output Gain: 0.7x

## DSP Algorithms

### Saturation
- Waveshaper with drive-dependent gain
- Soft clipping using hyperbolic tangent (tanh)
- Smooth saturation curve without harsh aliasing

### EQ
- Biquad IIR filters for each band
- Shelving filters for bass and treble
- Smooth frequency response

### Compressor
- Peak envelope detection with attack/release
- Adjustable compression ratio
- Smooth gain reduction

### Reverb
- Schroeder reverberator using parallel comb and series allpass filters
- Room Size: Simulates different room acoustics
- Width: Controls stereo image (0 = mono, 1 = full stereo)
- Wet/Dry Mix: Blend between reverb and dry signal
- Natural room reflections without harsh aliasing

## Parameters

| Parameter | Range | Default |
|-----------|-------|---------|
| Input Gain | 0 - 4x | 1x (0 dB) |
| Drive | 0 - 1 | 0 |
| Tone | 0 - 1 | 0.5 |
| Bass | -12 - +12 dB | 0 dB |
| Mid | -12 - +12 dB | 0 dB |
| Treble | -12 - +12 dB | 0 dB |
| Presence | -12 - +12 dB | 0 dB |
| Comp Threshold | -60 - 0 dB | -24 dB |
| Comp Ratio | 1:1 - 16:1 | 4:1 |
| Reverb Room Size | 0 - 1 | 0.5 |
| Reverb Width | 0 - 1 | 1.0 |
| Reverb Wet | 0 - 1 | 0.3 |
| Reverb Dry | 0 - 1 | 0.7 |
| Output Gain | 0 - 4x | 1x (0 dB) |

## Technical Details

- **Architecture**: VST3 plugin
- **Sample Rate**: 44.1 kHz to 192 kHz
- **Latency**: < 1 sample
- **Channels**: Stereo in/out
- **CPU Usage**: ~2-5% (single core at 44.1 kHz)

## Testing

Run the included DSP test suite:
```bash
python3 ../test_mantra_dsp.py
```

This verifies:
- Saturation algorithm
- EQ frequency shaping
- Compressor dynamics
- Full signal chain
- Numerical stability

## Project Structure

```
.
├── CMakeLists.txt           # Build configuration
├── BUILD.md                 # Detailed build instructions
├── README.md                # This file
├── Source/
│   ├── PluginProcessor.h/cpp    # Audio processing engine
│   ├── PluginEditor.h/cpp       # Plugin UI (minimal)
│   └── DSP/
│       ├── Saturation.h/cpp     # Distortion algorithms
│       ├── EQ.h/cpp             # Parametric EQ
│       └── Compressor.h/cpp     # Dynamic range control
```

## DAW Compatibility

Tested with VST3-compatible DAWs:
- Reaper
- Studio One
- Bitwig Studio
- Cubase 12+
- FL Studio 21+
- Logic Pro (via wrapper)

## License

Educational/Commercial use

## Credits

Built with [JUCE](https://github.com/juce-framework/JUCE) - The best C++ framework for audio plugin development.

---

**Enjoy your new guitar amp simulator! 🎸**
