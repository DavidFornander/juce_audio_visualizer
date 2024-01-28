cmake_minimum_required(VERSION 3.12)

project(MyJUCEProject)

# Set the JUCE module path
set(JUCE_MODULE_PATH /path/to/JUCE/modules)

# Add the JUCE module path to the module search path
list(APPEND CMAKE_MODULE_PATH ${JUCE_MODULE_PATH}/juce_cmake)

# Find the JUCE library
find_package(JUCE REQUIRED COMPONENTS juce_audio_basics juce_audio_devices juce_audio_formats juce_audio_processors juce_audio_utils)

# Add your source files
set(SOURCES
  Source/Main.cpp
  Source/MyAudioProcessor.cpp
  Source/MyAudioProcessor.h
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against the JUCE library
target_link_libraries(${PROJECT_NAME} PRIVATE juce::juce_audio_basics juce::juce_audio_devices juce::juce_audio_formats juce::juce_audio_processors juce::juce_audio_utils)
