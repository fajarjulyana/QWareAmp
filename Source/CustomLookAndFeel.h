/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 27 Apr 2025 3:35:10am
    Author:  fajarjulyana

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        // Load knob image if needed (commented out until you add your own image)
        // knobImage = juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);
    }
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                          const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        // This is where we'll draw our custom knob
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centerX = (float)x + (float)width * 0.5f;
        auto centerY = (float)y + (float)height * 0.5f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // Fill background
        auto knobBounds = juce::Rectangle<float>(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f);
        
        // Outer ring
        g.setColour(juce::Colours::darkgrey.darker(0.2f));
        g.fillEllipse(knobBounds);
        
        // Inner knob with gradient
        juce::ColourGradient gradient(juce::Colours::grey.darker(0.2f), centerX, centerY - radius * 0.4f,
                                     juce::Colours::black, centerX, centerY + radius * 0.8f, false);
        g.setGradientFill(gradient);
        g.fillEllipse(knobBounds.reduced(radius * 0.25f));
        
        // Highlight
        g.setColour(juce::Colours::white.withAlpha(0.5f));
        auto highlightBounds = knobBounds.reduced(radius * 0.4f);
        g.fillEllipse(highlightBounds.withY(highlightBounds.getY() - radius * 0.2f).reduced(radius * 0.4f));
        
        // Draw pointer
        juce::Path p;
        auto pointerLength = radius * 0.7f;
        auto pointerThickness = 2.0f;
        
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centerX, centerY));
        
        g.setColour(juce::Colours::white);
        g.fillPath(p);
        
        // Draw text label - slider name on top
        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        auto textBounds = juce::Rectangle<float>(x, y + height - 15, width, 15);
        g.drawText(slider.getName(), textBounds, juce::Justification::centred, false);
        
        // Draw value text below knob
        g.setFont(11.0f);
        g.drawText(slider.getTextFromValue(slider.getValue()), knobBounds.withY(centerY + radius * 0.6f).withHeight(20.0f),
                  juce::Justification::centred, false);
    }
    
private:
    juce::Image knobImage;
};