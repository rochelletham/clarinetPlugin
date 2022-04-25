//==============================================================================
/// @file MidiPianoRoll.h
/// A component that displays a piano roll animation of incoming midi messages.

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

/// A Component that displays a midi note in piano roll notation.
struct PianoRollNote : public juce::Component {

  /// Constructor. This should set the note's keynum and velocity members.
  PianoRollNote(int key, int vel);
  /// Destructor.
  ~PianoRollNote();

  /// Should fill the local bounds (rectangle) of the note with the color red.
   void paint(juce::Graphics& gr);

  /// The key number of this midi note.
  int keynum = 0;

  /// The velocity of this midi note.
  int velocity = 0;

  /// Set to true by the update() function when an incoming message is
  /// this note's note off. At that point the total pixel width for
  /// drawing the note is known.
  bool haveNoteOff = false;
};

/// A subclass of juce's AnimatedAppComponent that displays a moving
/// 'piano roll' display of incoming midi notes. The piano roll moves left
/// to right across the component at a speed determined by FPS and PPF (see
/// below).
struct MidiPianoRoll : public juce::AnimatedAppComponent {

  /// Constructor. This should set the animation's frames per second to FPS.
  MidiPianoRoll();

  /// Destructor. This should clear any active PianoRollNotes.
  ~MidiPianoRoll();
  
  /// Automatically called after each update() to paint the piano roll component.
  /// Your method should set the component's background color to black.
   void paint(juce::Graphics& gr) override;

  /// Adds or completes a PianoRollNote given an incoming midi message. If the
  /// message is a NoteOn then a new PianoRollNote will be added
  /// to the end of the notes array (see below) and to this component with its height
  /// should be set to 128th of the height of the PianoRollComponent.
  /// Thus, midi note 127 (the highest note possible) will be drawn at the top
  /// of the display (Y position 0) and the Y position of midi note 0 will be at
  /// the height (bottom) of the display less the height of the note. Since the
  /// new PianoRollNote has not yet been turned off its initial X position and
  /// width will be 0 and its width will increase by PPF until its NoteOff arrives.
  /// If the incoming midi message is a noteOff then that note will be found and
  /// have its haveNoteOff value set to true if it has not already been
  /// turned off.
   void addMidiMessage (const juce::MidiMessage& message) ;
  
  /// Deletes all PianoRollNotes in the notes array (see below).
  void clear();
  
  //==============================================================================
  
  /// Called at the frame rate to animate the active PianoRollNotes. Your method
  /// should iterate over the notes array moving them left to right in a manner
  /// dependant on whether or not the note has already received its note off or
  /// not. If it has, then the note needs to have its X position incremented by
  /// PPF with its Y position remaining the same. However if it has not yet received
  /// its note off then its current width should be be incremented by PPF with its
  /// height remaining the same. Once the note has been animated, check to see
  /// if its X position is beyond the right side of the component, and if it is,
  /// the note should be erased from from the notes array, see std::vector's
  /// erase() method. Note that when the subcomponent is deleted JUCE will remove
  /// it from its parent component automatically.
  void update() override;
  
  /// A vector of child components, each child representing a visible midi note.
  /// PianoRollNotes can be added using std::vector's push_back() method.
  std::vector<std::unique_ptr<PianoRollNote>> notes;
//   OwnedArray<PianoRollNote> notes;

  /// Frames per second, the rate at which the animation runs.
  const int FPS = 50;

  /// Pixels per frame, the number of pixels each note moves per frame.
  const int PPF = 2;
  
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiPianoRoll)
};
