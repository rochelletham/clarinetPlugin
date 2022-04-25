//==============================================================================
#include "MidiMessageLog.h"
//for keynumto pitch


MidiMessageLog::MidiMessageLog() {
   setModel(this);
   this->Component::setColour(ListBox::backgroundColourId, juce::Colours::black);
//   this->Component::setColour(1, juce::Colours::black);
}

MidiMessageLog::~MidiMessageLog() {

}

//==============================================================================
/// ListBoxModel overrides.

int MidiMessageLog::getNumRows() {  
  return messageLog.size();
}

void MidiMessageLog::paintListBoxItem (int row, juce::Graphics& g, int width, int height, bool)  {
   if (juce::isPositiveAndBelow(row, messageLog.size())) {
      g.setColour(juce::Colours::white);
      g.setFont(15);
      g.drawText(messageLog[row], juce::Rectangle<int>(width, height).reduced(4,0), juce::Justification::centredLeft, true);
   }
}

//==============================================================================
/// AsyncUpdater override.

void MidiMessageLog::handleAsyncUpdate() {
   updateContent();
   scrollToEnsureRowIsOnscreen(messageLog.size() - 1);
   repaint();
}

//==============================================================================
// MidiMessageLog methods.

void MidiMessageLog::addMidiMessage (const juce::MidiMessage& message) {
   juce::String temp (MidiMessageLog::midiMessageString(message));
   messageLog.add(temp);
   triggerAsyncUpdate();
}

void MidiMessageLog::clear() {
   if(!messageLog.isEmpty()) {
      std::cout << "message log size before : " << messageLog.size() <<std::endl;
      messageLog.removeRange(0, messageLog.size());
      std::cout << "message log size after : " << messageLog.size()<<std::endl;
   }
   triggerAsyncUpdate();
}
/*
For all messages the returned string includes the message's time stamp
 rounded to two places and enclosed in square brackets.
If the message is NOT a channel message, then the JUCE message description
 is included and the function immediately returns. See: MidiMessage::getDescription().
Otherwise (the message is a channel message) the string includes:
The 'midi type' of the message, one of "NoteOn", "NoteOff",
 "ControlChange", "ProgramChange", "PitchWheel", "AfterTouch", "ChannelPressure".
The (one-based) channel number.
For a note on or note off on channel 10 (drum track) the string
 includes the drum map's name for the note and the velocity.
 See: MidiMessage::getRhythmInstrumentName().
If the NoteOn or NoteOff is NOT on channel 10 then the string includes:
The note's keynum and velocity.
If the message is a NoteOn then the string also
 includes the note's pitch and frequency. See: keynumToPitch() and keynumToFrequency().
If the message is a control change the string
 includes the name and value of the message.
 See: MidiMessage::getControllerName() and MidiMessage::getControllerValue().
If the message is a program change the string includes the change value. See: MidiMessage::getProgramChangeNumber().
If the message is a pitch wheel change the string includes the change value. See: MidiMessage::getPitchWheelValue().
If the message is an aftertouch value the string includes the aftertouch value. See: MidiMessage::getAfterTouchValue().
If the message is a channel pressure value the string includes the pressure value. See: MidiMessage::getChannelPressureValue().
*/
const juce::String MidiMessageLog::midiMessageString(const juce::MidiMessage& msg) {
   double startTime = juce::Time::getMillisecondCounterHiRes() * 0.001;
   double timeStamp = startTime + (msg.MidiMessage::getTimeStamp()* 0.001);
   juce::String time ="[" + juce::String(timeStamp) +  "] ";
   juce::String channel = juce::String(msg.getChannel());
   juce::String velocity = juce::String(msg.getVelocity());
   juce::String retString;

   if (msg.isNoteOnOrOff()) {
      juce::String key = juce::String(msg.getNoteNumber());
      juce::String pitch = juce::String(keynumToPitch(msg.getNoteNumber()));
      juce::String freq = juce::String(keynumToFrequency(msg.getNoteNumber()));
      //For a note on or note off on channel 10 (drum track)
      // the string includes the drum map's name for the note and the velocity.
   //See: MidiMessage::getRhythmInstrumentName().
      if (msg.getChannel() == 10) {
         juce::String drumMap = juce::String(juce::MidiMessage::getRhythmInstrumentName(msg.getNoteNumber()));
         retString = time + "NoteOn: " + "channel=" + channel + ", key=" + key +
         " velocity=" + velocity + " drum map name= " + drumMap;
         return retString;
      } else {
         if (msg.isNoteOn()) {
            retString = time + "NoteOn: " + "channel=" + channel + ", key=" + key +
            " velocity=" + velocity + " pitch=" + pitch + ", freq=" + freq;
            return retString;
         } else if (msg.isNoteOff()) {
            retString = time + "NoteOff: " + "channel=" + channel + ", key=" + key +
            " velocity=" + velocity;
            return retString;
         }
      }
   } else if (msg.isController()) {
      juce::String controlName = juce::String(juce::MidiMessage::getControllerName (msg.getControllerNumber()));
      juce::String controlValue = juce::String(msg.MidiMessage::getControllerValue());
      retString = time + "ControlChange: " + "controller=" + controlName + ", " + "value=" + controlValue;
      return retString;
   } else if (msg.isProgramChange()) {
      juce::String programName = juce::String(msg.MidiMessage::getProgramChangeNumber());
      retString = time + "ProgramChange: channel=" +channel + ", number=" + programName;
      return retString;
   } else if (msg.isPitchWheel()) {
      //pitch wheel change the string includes the change value. See: MidiMessage::getPitchWheelValue().
      juce::String pitchWheel = juce::String(msg.MidiMessage::getPitchWheelValue());
      retString = time + "PitchWheel: channel=" + channel + ", value=" + pitchWheel;
      return retString;
   } else if (msg.isAftertouch()) {
      //string includes the aftertouch value. See: MidiMessage::getAfterTouchValue().
      juce::String pitchWheel = juce::String(msg.MidiMessage::getPitchWheelValue());
      retString = time + "PitchWheel: channel=" + channel + ", value=" + pitchWheel;
      return retString;
   } else if (msg.isChannelPressure()) {
      //string includes the pressure value. See: MidiMessage::getChannelPressureValue().
      juce::String pressureChange = juce::String(msg.MidiMessage::getChannelPressureValue());
      retString = time + "PitchWheel: channel=" + channel + ", value=" + pressureChange;
      return retString;
   }
   std::cout << "reached the end" <<std::endl;
   return msg.MidiMessage::getDescription();
}

float MidiMessageLog::keynumToFrequency(int keynum) {
  auto freq = (440) * pow(2, float((keynum - 69) / 12.0));
//   std::cout << float((keynum - 69) / 12.0) <<std::endl;
//   std::cout << "keynum" << keynum << " freq " << freq <<std::endl;
   return freq;
}

/*
 Converts an integer key number (0-127) into a note name.

 Midi note names should be "C", "C#", "D", "Eb", "E", "F", "F#",
 "G", "Ab", "A", "Bb", "B" and octaves are "00", "0", "1", "2", "3",
 "4", "5", "6", "7", "8", "9". The midi keynumber 60 is C4.
 */
juce::String octaveArray[11] = {"00", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
juce::String letterArray[12] = {"C", "C#", "D", "Eb", "E", "F", "F#",
   "G", "Ab", "A", "Bb", "B"};
juce::String MidiMessageLog::keynumToPitch(int keynum) {
   if (keynum < 0 || keynum > 127) { return "";}
   int letter = keynum % 12;
   int octave = keynum / 12;
   return juce::String(letterArray[letter] + octaveArray[octave]);
}

float MidiMessageLog::velocityToAmplitude(int velocity) {
   return (float) (velocity % 127)/100;

}

