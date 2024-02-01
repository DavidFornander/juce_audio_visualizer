#include "audioVISUAL/PluginEditor.h"
#include "audioVISUAL/PluginProcessor.h"

/**
 * @brief Implementation of the AudioPluginAudioProcessor class.
 * 
 * This class represents the audio processor for the audio plugin.
 * It handles audio processing, MIDI handling, parameter management, and GUI creation.
 */
namespace audio_plugin {
  
  /**
   * @brief Constructor for the AudioPluginAudioProcessor class.
   * 
   * Initializes the audio processor with the appropriate audio channel configuration.
   */
  AudioPluginAudioProcessor::AudioPluginAudioProcessor(): AudioProcessor(BusesProperties()
  #if !JucePlugin_IsMidiEffect
  #if !JucePlugin_IsSynth
                .withInput("Input", juce::AudioChannelSet::stereo(), true)
  #endif
                .withOutput("Output", juce::AudioChannelSet::stereo(), true)
  #endif
        ) {
  }

  /**
   * @brief Destructor for the AudioPluginAudioProcessor class.
   */
  AudioPluginAudioProcessor::~AudioPluginAudioProcessor() {}

  /**
   * @brief Gets the name of the audio plugin.
   * 
   * @return The name of the audio plugin.
   */
  const juce::String AudioPluginAudioProcessor::getName() const {
    return JucePlugin_Name;
  }

  /**
   * @brief Checks if the audio plugin accepts MIDI input.
   * 
   * @return True if the audio plugin accepts MIDI input, false otherwise.
   */
  bool AudioPluginAudioProcessor::acceptsMidi() const {
  #if JucePlugin_WantsMidiInput
    return true;
  #else
    return false;
  #endif
  }

  /**
   * @brief Checks if the audio plugin produces MIDI output.
   * 
   * @return True if the audio plugin produces MIDI output, false otherwise.
   */
  bool AudioPluginAudioProcessor::producesMidi() const {
  #if JucePlugin_ProducesMidiOutput
    return true;
  #else
    return false;
  #endif
  }

  /**
   * @brief Checks if the audio plugin is a MIDI effect.
   * 
   * @return True if the audio plugin is a MIDI effect, false otherwise.
   */
  bool AudioPluginAudioProcessor::isMidiEffect() const {
  #if JucePlugin_IsMidiEffect
    return true;
  #else
    return false;
  #endif
  }

  /**
   * @brief Gets the tail length of the audio plugin in seconds.
   * 
   * @return The tail length of the audio plugin in seconds.
   */
  double AudioPluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

  /**
   * @brief Gets the number of programs supported by the audio plugin.
   * 
   * @return The number of programs supported by the audio plugin.
   */
  int AudioPluginAudioProcessor::getNumPrograms() {
    return 1; // NB: some hosts don't cope very well if you tell them there are 0
              // programs, so this should be at least 1, even if you're not really
              // implementing programs.
  }

  /**
   * @brief Gets the index of the current program.
   * 
   * @return The index of the current program.
   */
  int AudioPluginAudioProcessor::getCurrentProgram() { return 0; }

  /**
   * @brief Sets the current program index.
   * 
   * @param index The index of the program to set as the current program.
   */
  void AudioPluginAudioProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
  }

  /**
   * @brief Gets the name of the program at the specified index.
   * 
   * @param index The index of the program.
   * @return The name of the program at the specified index.
   */
  const juce::String AudioPluginAudioProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
  }

  /**
   * @brief Changes the name of the program at the specified index.
   * 
   * @param index The index of the program.
   * @param newName The new name for the program.
   */
  void AudioPluginAudioProcessor::changeProgramName(int index,
                                                    const juce::String &newName) {
    juce::ignoreUnused(index, newName);
  }

  /**
   * @brief Prepares the audio processor for playback.
   * 
   * @param sampleRate The sample rate of the audio.
   * @param samplesPerBlock The number of samples per block.
   */
  void AudioPluginAudioProcessor::prepareToPlay(double sampleRate,
                                                int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(sampleRate, samplesPerBlock);
  }

  /**
   * @brief Releases any resources used by the audio processor.
   */
  void AudioPluginAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
  }

  /**
   * @brief Checks if the specified bus layout is supported by the audio processor.
   * 
   * @param layouts The bus layout to check.
   * @return True if the bus layout is supported, false otherwise.
   */
  bool AudioPluginAudioProcessor::isBusesLayoutSupported(
      const BusesLayout &layouts) const {
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
      return false;

      // This checks if the input layout matches the output layout
  #if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
      return false;
  #endif

    return true;
  #endif
  }

  /**
   * @brief Processes an audio block.
   * 
   * @param buffer The audio buffer to process.
   * @param midiMessages The MIDI messages to process.
   */
  void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
/*     juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
      buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
      auto *channelData = buffer.getWritePointer(channel);
      juce::ignoreUnused(channelData);
      // ..do something to the data...
    } */
    

    
    // DEBUG
    debug_msg_counter++;
    debug_msg_processor1 = "noteOnVel: " + (std::to_string(noteOnVel));
    debug_msg_processor2 = "Bypass: " + (std::to_string(bypass));

    if((juce::uint8) bypass == 0.0f){
      buffer.clear();
 
      juce::MidiBuffer processedMidi;
  
      for (const auto metadata : midiMessages){
          auto message = metadata.getMessage();
          const auto time = metadata.samplePosition;
  
          if (message.isNoteOn()){
              message = juce::MidiMessage::noteOn (message.getChannel(),
                                                  message.getNoteNumber(),
                                                  (juce::uint8) noteOnVel);
          }
          processedMidi.addEvent (message, time);
      }
      midiMessages.swapWith (processedMidi);
      }
  }

  /**
   * @brief Checks if the audio processor has an editor.
   * 
   * @return True if the audio processor has an editor, false otherwise.
   */
  bool AudioPluginAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
  }

  /**
   * @brief Creates an editor for the audio processor.
   * 
   * @return A pointer to the created editor.
   */
  juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
    return new AudioPluginAudioProcessorEditor(*this);
  }

  /**
   * @brief Gets the state information of the audio processor.
   * 
   * @param destData The memory block to store the state information.
   */
  void AudioPluginAudioProcessor::getStateInformation(
      juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused(destData);
  }

  /**
   * @brief Sets the state information of the audio processor.
   * 
   * @param data The data containing the state information.
   * @param sizeInBytes The size of the data in bytes.
   */
  void AudioPluginAudioProcessor::setStateInformation(const void *data,
                                                      int sizeInBytes) {
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
    juce::ignoreUnused(data, sizeInBytes);
  }
} // namespace audio_plugin

// This creates new instances of the plugin.
// This function definition must be in the global namespace.
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
  return new audio_plugin::AudioPluginAudioProcessor();
}
