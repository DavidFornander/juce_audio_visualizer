#pragma once

#include "PluginProcessor.h"

#include "components/HorizontalMeter.h"


namespace audio_plugin {
  class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                          public juce::Timer,
                                          private juce::Slider::Listener{
  public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
    ~AudioPluginAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;
    void timerCallback() override;

  private:
    void sliderValueChanged(juce::Slider *slider) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor &processorRef;

    // Create a slider, called midi Volume
    juce::Slider midiVolume;

    juce::Slider bypassSlider;

    juce::String debug_msg_editor;

    // HorizontalMeter meter
    // HorizontalMeter meter: horizontalMeterL, horizontalMeterR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
  };
} // namespace audio_plugin
