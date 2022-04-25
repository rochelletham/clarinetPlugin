//==============================================================================

#include "MidiPianoRoll.h"

//==============================================================================
// PianoRollNote

PianoRollNote::PianoRollNote(int key, int vel) {
   keynum = key;
   velocity = vel;
}


PianoRollNote::~PianoRollNote() {
}

void PianoRollNote::paint(juce::Graphics& gr) {
   gr.fillAll(juce::Colours::red);
}

//==============================================================================
// MidiPianoRoll

MidiPianoRoll::MidiPianoRoll() {
   this->AnimatedAppComponent::setFramesPerSecond(FPS);
}

MidiPianoRoll::~MidiPianoRoll() {
   clear();
}

void MidiPianoRoll::clear() {
   if (notes.size() != 0) {
      notes.clear();
   }
}

void MidiPianoRoll::paint(juce::Graphics& gr) {
//   gr.fillAll(juce::Colours::black);
//   this->Component::setColour(ListBox::backgroundColourId, juce::Colours::black);
   gr.fillAll (juce::Colours::black);
}
/*
 iterate over the notes array moving them left to right in a manner
 dependant on whether or not the note has already received its note off or not.
 If it has, then the note just needs to have its X position incremented by PPF
 with its Y position remaining the same.
 However if it has not yet received its note off then
 its X will remain 0 and its current width will be be incremented by PPF
 with its height remaining the same.
 Once the note has been animated, check to see if its X position
 is beyond the right side of the component, and if it is,
 the note should be erased from from the notes array, see std::vector's erase() method.
 Note that when the subcomponent is deleted JUCE will remove it from
 its parent component automatically.
 */
void MidiPianoRoll::update() {
//   std::cout <<"note size" << notes.size() <<std::endl;
   for (auto it = notes.begin(); it != notes.end(); it++) {
      if ((*it)->haveNoteOff) {
         auto bounds = (*it)->getBounds();
         bounds.setX(bounds.getX()+PPF);
         (*it)->setBounds(bounds);
//         std::cout << "notes x pos " << notes[i]->getX() <<std::endl;
//         std::cout << "component width" << this->getParentWidth()  <<std::endl;
//         std::cout << "notes y pos " << notes[i]->getY() <<std::endl;
//         std::cout << "notes width " << notes[i]->getWidth() <<std::endl;
//         std::cout << "notes height " << notes[i]->getHeight() <<std::endl;
//         setBounds(<#int x#>, <#int y#>, <#int width#>, <#int height#>)
//         std::cout <<"testing getframe counter" << getFrameCounter() <<std::endl;
      } else {
         auto bounds = (*it)->getBounds();
         bounds.setWidth(bounds.getWidth() +PPF);
         (*it)->setBounds(bounds);
//         std::cout << "before note off" <<std::endl;
//         notes[i]->setBounds(notes[i]->getX(), notes[i]->getY(), notes[i]->getWidth() +PPF, notes[i]->getHeight());
//         std::cout << "after note off" <<std::endl;
         if ((*it)->getX() > getWidth()) {
            this->removeChildComponent(it->get());
            it = notes.erase(it);
         }
      }

   }
}

void MidiPianoRoll::addMidiMessage (const juce::MidiMessage& msg) {
   if (msg.isNoteOn()) {
      std::unique_ptr<PianoRollNote> note_ptr = std::make_unique<PianoRollNote>(msg.getNoteNumber(), msg.getVelocity());
      addAndMakeVisible(note_ptr.get());
      note_ptr->setBounds(this->getX(), this->getHeight() * (127-msg.getNoteNumber()) / 128, 0, this->getHeight()/128);
      notes.push_back(std::move(note_ptr));
   } else if (msg.isNoteOff()) {
      for (int i = (int) notes.size() - 1; i>=0; i--) {
         if (notes[i]->haveNoteOff != true && notes[i]->keynum ==msg.getNoteNumber()) {
            notes[i]->haveNoteOff = true;
            break;
         }
      }
   }
}

