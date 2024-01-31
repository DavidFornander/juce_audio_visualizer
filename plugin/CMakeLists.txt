cmake_minimum_required(VERSION 3.22)

project(audioVISUAL VERSION 0.0.1)

juce_add_plugin(${PROJECT_NAME}
  #COMPANY_NAME "AudioVISUAL98979"
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT TRUE
  NEEDS_MIDI_OUTPUT TRUE
  PLUGIN_MANUFACTURER_CODE AVIS
  PLUGIN_CODE A699
  FORMATS AU VST3 Standalone
  PRODUCT_NAME "AudioVISUAL0"
  COPY_PLUGIN_AFTER_BUILD TRUE
)

target_sources(${PROJECT_NAME}
  PRIVATE
    source/PluginProcessor.cpp
    source/PluginEditor.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    include
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE
    juce::juce_audio_utils
  PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    JUCE_WEB_BROWSE=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_SILENCE_XCODE_15_LINKER_WARNING=1
    
)

target_link_options(${PROJECT_NAME}
  PRIVATE
    -Wl,-weak_reference_mismatches,weak
)

if(MSVC)
target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
)
endif()
