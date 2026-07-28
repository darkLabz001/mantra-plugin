cmake_minimum_required(VERSION 3.22)
project(MantraPlugin VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(JUCE_BUILD_EXTRAS OFF)
set(JUCE_BUILD_EXAMPLES OFF)

# Disable GUI extras to avoid GTK dependency
set(JUCE_MODULES_TO_SKIP juce_gui_extra)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 7.0.9
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(MantraPlugin
    PRODUCT_NAME "Mantra"
    COMPANY_NAME "Neural DSP Clone"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Mntr
    PLUGIN_CODE Mntr
    FORMATS VST3
    VST3_CATEGORIES "Fx" "Distortion"
)

target_sources(MantraPlugin
    PRIVATE
        Source/PluginProcessor.cpp
        Source/DSP/Saturation.cpp
        Source/DSP/EQ.cpp
        Source/DSP/Compressor.cpp
        Source/DSP/Reverb.cpp
)

target_include_directories(MantraPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source)

target_compile_features(MantraPlugin PRIVATE cxx_std_17)

target_link_libraries(MantraPlugin
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_core
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
)
