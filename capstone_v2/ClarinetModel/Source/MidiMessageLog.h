//==============================================================================
/// @file MidiMessageLog.h
/// Defines a class that lists all the MIDI messages that arrive in the app.

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//==============================================================================

/// A class that displays a log of incoming midi messages. This inherits from
/// ListBox (a GUI component), ListBoxModel, a class that defines the
/// structure and content of what is displayed inside the ListBox, and AsyncUpdater,
/// a class that asynchronously responds to a triggering event.
struct MidiMessageLog : public juce::ListBox, private juce::ListBoxModel, private juce::AsyncUpdater {

  /// Constructor.  Since our class is both a ListBox and ListBoxMode it needs
  /// to pass itself as the ListBoxModel to 'setModel()'.  The constructor should
  /// also set the background color of the ListBox to black. See: ListBox.
  MidiMessageLog() ;

  ~MidiMessageLog() ;

  //==============================================================================
  /// ListBoxModel overrides.

  /// Thss method must return the number of lines in the log. Each MIDI message
  /// received by our app will be printed on its own line in the ListBox.
   // return length of array
  int getNumRows() override ;
  
  /// This method is given a row number, graphics context, width and height of the
  ///  line and should print a single midi message row (line) in the list box. Your
  ///  method should perform the following actions:
  /// * Set the drawing color to white.
  /// * Set the font size to 15.
  /// * Draw the midi message's text within a rectangle that is positioned four
  /// pixels in from the left margin and using Justification::centredLeft. See
  /// Graphics::drawText().
   void paintListBoxItem (int row, juce::Graphics& g, int width, int height, bool) override ;

  //==============================================================================
  // AsyncUpdater methods.

  /// This method respond when triggerAsyncUpdate() is called. Your method should
  /// perform the following actions:
  /// * Call updateContent(). See below.
  /// * Call scrollToEnsureRowIsOnScreen to make sure the newest row is visible.
  /// * Call repaint() to trigger a repaint.
  void handleAsyncUpdate() override ;

  //==============================================================================
  // MidiMessageLog methods.
  
  /// Adds a string representation of a MIDI message to the component.
  /// Your method should perform the following actions:
  /// * Convert the message to a string using midiMessageString() and add it to
  /// the messageLog.
  /// * Call triggerAsyncUpdate() to update the message log.
   void addMidiMessage (const juce::MidiMessage& message) ;

  /// Clears the current contents of the log and calls triggerAsyncUpdate().
  void clear() ;

  /// Returns the string representation of a MidiMessage that is printed in
  /// the messageLog. Your method should handle all channel messages:
  /// NoteOn, NoteOff, ChannelMessage, ProgramChange, PitchWheel, AfterTouch,
  /// ChannelPressure, always providing their time stamp (inside []), name,
  /// channel value, and message specific values. Here are examples:
  /// * [213916.44] NoteOn: channel=1, key=42, velocity=53, pitch=F#2, freq=92.499
  /// * [213207.19] NoteOff: channel=1, key=60, velocity=105
  /// * [213265.06] ProgramChange: channel=1, number=1
  /// * [213821.11] PitchWheel: channel=1, value=8192
  /// * [213851.85] ControlChange: channel=1, controller=Modulation Wheel (coarse), value=6
   static const juce::String midiMessageString(const juce::MidiMessage& msg) ;
   
private:
  //==============================================================================
   
  /// An array of MIDI message strings to display in the logger.
   juce::StringArray messageLog;

  /// Converts a key number 0-127 into floating point Hertz: 440.0 * 2^((KN-69)/12).
  static float keynumToFrequency(int keynum) ;
  
  /// Converts an integer key number (0-127) into a note name. Midi note names
  /// should be "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B"
  /// and octaves are "00", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9".
   static juce::String keynumToPitch(int keynum) ;
  
  /// Converts an integer velocity 0-127 into floating point amplitude 0.0-1.0.
  static float velocityToAmplitude(int velocity) ;
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiMessageLog)
};
