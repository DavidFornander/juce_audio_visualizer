#include "audioVISUAL/PluginEditor.h"
#include "audioVISUAL/PluginProcessor.h"


/**
 * @brief The implementation of the AudioPluginAudioProcessorEditor class.
 * 
 * This class represents the graphical user interface (GUI) for the audio plugin.
 * It inherits from the AudioProcessorEditor class and is responsible for painting
 * the GUI components and handling user interactions.
 */
namespace audio_plugin {

  /**
   * @brief Constructs an AudioPluginAudioProcessorEditor object.
   * 
   * This constructor initializes the AudioPluginAudioProcessorEditor object with
   * a reference to the AudioPluginAudioProcessor object. It also sets the initial
   * size of the editor.
   * 
   * @param p The reference to the AudioPluginAudioProcessor object.
   */
  AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p): AudioProcessorEditor(&p), processorRef(p) {
    juce::ignoreUnused(processorRef);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setResizable(true, true);
    setResizeLimits(300, 200, 4000, 4000);
    setSize(500, 500);

    // These define the parameters of our slider object
    midiVolume.setSliderStyle (juce::Slider::LinearBarVertical);
    midiVolume.setRange (0.0, 127.0, 1.0);
    midiVolume.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled (true, false, this);
    midiVolume.setTextValueSuffix (" Volume");
    midiVolume.setValue(1.0);

    bypassSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    bypassSlider.setRange (0.0, 1.0, 1.0);
    bypassSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    bypassSlider.setPopupDisplayEnabled (true, false, this);
    bypassSlider.setTextValueSuffix (" Bypass");
    bypassSlider.setValue(1.0);
 
 
    // This function adds the slider to the editor
    addAndMakeVisible (&midiVolume);
    addAndMakeVisible (&bypassSlider);


    midiVolume.addListener(this);
    bypassSlider.addListener(this);

    debug_msg_editor = "Editor";
    processorRef.debug_msg_processor = "Processor";
  }

  /**
   * @brief Destroys the AudioPluginAudioProcessorEditor object.
   * 
   * This destructor is responsible for cleaning up any resources used by the
   * AudioPluginAudioProcessorEditor object.
   */
  AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

  /**
   * @brief Paints the GUI components of the editor.
   * 
   * This function is called by the framework to paint the GUI components of the
   * editor. It fills the background with a solid color and draws a text message
   * on the screen.
   * 
   * @param g The Graphics object used for painting.
   */
  void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a
    // solid colour)
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText((juce::String) debug_msg_editor, getLocalBounds(), juce::Justification::centredTop, 1);
    g.drawFittedText("Midi Volume 3", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText((juce::String) processorRef.debug_msg_processor, getLocalBounds(), juce::Justification::centredBottom, 1);
  }

  void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    if (slider == &midiVolume) {
      processorRef.noteOnVel = midiVolume.getValue();
    }
  }

  /**
   * @brief Called when the editor is resized.
   * 
   * This function is called by the framework when the editor is resized. It is
   * responsible for laying out the positions of any subcomponents in the editor.
   */
  void AudioPluginAudioProcessorEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
  

    int midiVolumeHeigt = getHeight() - 60;
    int midiVolumeWidth = 20;
    int midiVolumeX = 40;
    int midiVolumeY = 30;
    midiVolume.setBounds (midiVolumeX, midiVolumeY, midiVolumeWidth, midiVolumeHeigt);

    int bypassSliderHeight = getHeight() - 60;
    int bypassSliderWidth = 20;
    int bypassSliderX = getWidth() - (40 + bypassSliderWidth);
    int bypassSliderY = 30;
    bypassSlider.setBounds (bypassSliderX, bypassSliderY, bypassSliderWidth, bypassSliderHeight);
  }

} // namespace audio_plugin
