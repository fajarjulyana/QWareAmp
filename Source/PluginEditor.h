#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

// Background Component
class AmpBackground : public juce::Component
{
public:
    AmpBackground()
    {
        // Initialize background properties
        backgroundColour = juce::Colour(40, 40, 45);
        metalEffect = true;
        borderWidth = 10;
    }
    
    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat().reduced(borderWidth * 0.5f);
        
        // Draw metallic background
        if (metalEffect)
        {
            juce::ColourGradient gradient(
                juce::Colour(70, 72, 78), bounds.getX(), bounds.getY(),
                juce::Colour(40, 42, 48), bounds.getRight(), bounds.getBottom(),
                false);
            gradient.addColour(0.5, juce::Colour(50, 52, 58));
            g.setGradientFill(gradient);
            g.fillRoundedRectangle(bounds, 10.0f);
            
            // Add metallic highlights
            juce::Path highlight;
            highlight.addRoundedRectangle(bounds.reduced(borderWidth), 8.0f);
            g.setColour(juce::Colours::white.withAlpha(0.1f));
            g.strokePath(highlight, juce::PathStrokeType(1.0f));
        }
        else
        {
            // Simple solid background
            g.setColour(backgroundColour);
            g.fillRoundedRectangle(bounds, 10.0f);
        }
        
        // Draw border
        g.setColour(juce::Colours::black);
        g.drawRoundedRectangle(bounds, 10.0f, borderWidth);
        
        // Draw amp grille in bottom area
        auto grilleArea = bounds.removeFromBottom(bounds.getHeight() * 0.2f).reduced(bounds.getWidth() * 0.1f, 5.0f);
        drawAmpGrille(g, grilleArea);
        
        // Add amp logo/name
        g.setColour(juce::Colours::silver);
        g.setFont(juce::Font(28.0f, juce::Font::bold));
        g.drawText("ROCK AMP", bounds.removeFromTop(40.0f), juce::Justification::centred, false);
    }
    
private:
    void drawAmpGrille(juce::Graphics& g, juce::Rectangle<float> area)
    {
        g.setColour(juce::Colours::black);
        g.fillRoundedRectangle(area, 5.0f);
        
        g.setColour(juce::Colours::darkgrey.darker(0.7f));
        
        float lineSpacing = 4.0f;
        float startY = area.getY() + 2.0f;
        float endY = area.getBottom() - 2.0f;
        
        for (float x = area.getX() + 3.0f; x < area.getRight(); x += lineSpacing)
        {
            g.drawLine(x, startY, x, endY, 1.0f);
        }
    }
    
    juce::Colour backgroundColour;
    bool metalEffect;
    float borderWidth;
};

class GuitarAmpAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    GuitarAmpAudioProcessorEditor(GuitarAmpAudioProcessor&);
    ~GuitarAmpAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GuitarAmpAudioProcessor& audioProcessor;
    
    // Custom look and feel
    CustomLookAndFeel customLookAndFeel;
    
    // Background component
    AmpBackground background;
    
    // Sliders
    juce::Slider gainSlider;
    juce::Slider driveSlider;
    juce::Slider rangeSlider;
    juce::Slider blendSlider;
    juce::Slider volumeSlider;
    juce::ComboBox distortionTypeBox;
    
    // Labels
    juce::Label gainLabel;
    juce::Label driveLabel;
    juce::Label rangeLabel;
    juce::Label blendLabel;
    juce::Label volumeLabel;
    juce::Label distortionTypeLabel;
    
    // Parameter attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> distortionTypeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuitarAmpAudioProcessorEditor)
};