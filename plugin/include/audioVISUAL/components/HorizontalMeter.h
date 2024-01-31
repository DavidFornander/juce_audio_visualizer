#pragma once

#include <JuceHeader.h>

namespace Gui{
  class HorizontalMeter : public juce::Component
  {
  private:
    float level = -60.0f;
  public:
    void paint(juce::Graphics &g) override{
      auto bounds = getLocalBounds().toFloat();
      g.setColour(juce::Colours::white.withBrightness(0.5f));
      g.fillRoundedRectangle(bounds, 5.0f);
      g.drawRect(getLocalBounds());
      g.fillRect(getLocalBounds().toFloat().withTrimmedTop(level));

      jmap(level, -60.0f, +6.0f, 0.0f, static_cast<float>(getWidth()));
    }
    
    void setLevel(const float newLevel){
      level = newLevel;
      repaint();
    }
    
  };
  
  HorizontalMeter::HorizontalMeter(/* args */)
  {
  }
  
  HorizontalMeter::~HorizontalMeter()
  {
  }
  
}