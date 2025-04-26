#pragma once

#include <JuceHeader.h>

// Jika Anda memilih untuk menggunakan gambar kustom untuk knob
class KnobImageLoader
{
public:
    // Ini adalah contoh cara membuat binary resources
    // 1. Tambahkan gambar knob ke folder Anda (misalnya knob.png)
    // 2. Di Projucer, tambahkan gambar ke dalam "Binary Resources"
    // 3. Rebuild project
    // 4. Kemudian gunakan kode di bawah untuk memuat gambar
    
    static juce::Image loadKnobImage()
    {
        // Ganti dengan file resource Anda
        // return juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);
        
        // Atau buat gambar knob secara programatis
        juce::Image knobImage(juce::Image::ARGB, 128, 128, true);
        juce::Graphics g(knobImage);
        
        // Background lingkaran
        g.setColour(juce::Colour(60, 60, 60));
        g.fillEllipse(0, 0, 128, 128);
        
        // Edge logam
        g.setColour(juce::Colours::silver);
        g.drawEllipse(2, 2, 124, 124, 2);
        
        // Refleksi cahaya
        juce::ColourGradient reflection(juce::Colours::white.withAlpha(0.3f), 30, 30,
                                       juce::Colours::transparentWhite, 90, 90, true);
        g.setGradientFill(reflection);
        g.fillEllipse(15, 15, 60, 60);
        
        // Indikator posisi
        g.setColour(juce::Colours::white);
        g.fillRect(60, 20, 8, 40);
        
        return knobImage;
    }
};