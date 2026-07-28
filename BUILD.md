# Mantra Plugin - Build Instructions

A full-featured guitar amp modeling VST3 plugin built with JUCE and C++17.

## Features

- **Input Stage**: Gain control for signal shaping
- **Saturation/Drive**: Waveshaper-based distortion with tone control
- **EQ Section**: 4-band parametric EQ
  - Bass (100 Hz low shelf)
  - Mid (1 kHz peaking)
  - Treble (8 kHz high shelf)
  - Presence (3 kHz peaking)
- **Dynamics**: Compressor with adjustable threshold and ratio
- **Output Stage**: Output gain for final level control

## Requirements

- CMake 3.22+
- C++17 compatible compiler (GCC, Clang, or MSVC)
- On Linux: ALSA development libraries
  ```bash
  sudo apt-get install libasound2-dev
  ```

## Building on Linux

### 1. Clone and navigate to project
```bash
cd mantra_plugin
```

### 2. Create build directory
```bash
mkdir build && cd build
```

### 3. Configure CMake
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

### 4. Build
```bash
cmake --build . --config Release -j$(nproc)
```

### 5. Find the built plugin
The VST3 plugin will be in:
```
build/MantraPlugin_artefacts/Release/VST3/Mantra.vst3
```

The standalone app will be in:
```
build/MantraPlugin_artefacts/Release/Standalone/Mantra
```

## Installation

### VST3 Plugin
Copy the VST3 to your DAW's plugin directory:

**Linux:**
```bash
cp -r build/MantraPlugin_artefacts/Release/VST3/Mantra.vst3 ~/.vst3/
```

### Standalone
Run the standalone directly:
```bash
./build/MantraPlugin_artefacts/Release/Standalone/Mantra
```

## Usage

1. Load the plugin in your DAW
2. Adjust input gain to drive the saturation stage
3. Use Drive to control distortion intensity
4. Use Tone to shape the distortion character
5. Use EQ controls to shape the frequency response
6. Use Compressor to tame dynamics
7. Adjust output gain to compensate for level changes

## Parameters

| Parameter | Range | Default |
|-----------|-------|---------|
| Input Gain | 0 dB to +12 dB | 0 dB |
| Drive | 0 to 1 | 0 |
| Tone | 0 to 1 | 0.5 |
| Bass | -12 dB to +12 dB | 0 dB |
| Mid | -12 dB to +12 dB | 0 dB |
| Treble | -12 dB to +12 dB | 0 dB |
| Presence | -12 dB to +12 dB | 0 dB |
| Comp Threshold | -60 dB to 0 dB | -24 dB |
| Comp Ratio | 1:1 to 16:1 | 4:1 |
| Output Gain | 0 dB to +12 dB | 0 dB |

## Troubleshooting

### CMake not finding JUCE
The CMakeLists.txt will automatically download JUCE. If this fails:
1. Check internet connection
2. Manually download JUCE from https://github.com/juce-framework/JUCE
3. Set `-DCMAKE_PREFIX_PATH` to the JUCE directory

### Plugin not loading in DAW
- Ensure the plugin is in the correct directory for your DAW
- Rescan plugins in your DAW
- Check DAW logs for error messages

### Build fails with C++ errors
- Ensure you have a C++17 compatible compiler
- Update your compiler: `sudo apt-get install build-essential`

## Audio Processing Chain

1. **Input Gain** → amplifies signal into saturation stage
2. **Saturation** → waveshaper applies distortion based on drive
3. **Tone Control** → soft clipping shapes the character
4. **Compressor** → dynamic range processing
5. **EQ** → frequency shaping with 4-band parametric EQ
6. **Output Gain** → final level adjustment

## Development

To modify parameters or DSP algorithms:
- Edit `Source/PluginProcessor.cpp` for parameter definitions
- Edit `Source/DSP/Saturation.cpp` for distortion algorithms
- Edit `Source/DSP/EQ.cpp` for EQ characteristics
- Edit `Source/DSP/Compressor.cpp` for compression behavior
- Edit `Source/PluginEditor.cpp` to change the UI layout

## License

This is an educational project demonstrating JUCE plugin development.
