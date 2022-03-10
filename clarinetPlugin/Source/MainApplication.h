//==============================================================================
// MainApplication.h
// This file defines the class representing our application instance.
//==============================================================================

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainWindow;

/// A JUCEApplication that generates various types of wave forms and displays
/// them in a visualizer. NOTE: Member declarations without documentation
/// should behave the same as the GUI Basics app.
class MainApplication : public JUCEApplication {
public:

  MainApplication();

  //==============================================================================
  // JUCEApplication overrides

  const String getApplicationName() override;

  const String getApplicationVersion() override;

  bool moreThanOneInstanceAllowed() override;

  /// Initializes the application. Your method should perform the following actions:
  /// * Initialize the audioDeviceManager to 0 input channels and 2 output channels.
  /// See: audioDeviceManager::initialise().
  /// * Raise an assertion if initialization results in an non-null error message. See: jassert().
  /// * Create the application window.
  
  void initialise (const String& commandLine) override;

  /// Add your application's shutdown code here.
  void shutdown() override;
 
  void systemRequestedQuit() override;

  void anotherInstanceStarted (const String& commandLine) override;

  //==============================================================================
  // MainApplication members
  
  /// Returns our application instance.
  static MainApplication& getApp();

  /// Manages the system's audio and MIDI settings.
  AudioDeviceManager audioDeviceManager;

private:

  /// Closes any open dialog or alert sindows the user left open when they quit
  /// the app.  Your method should take the following actions:
  /// * Iterate all the top-level components in juce::Desktop::getInstance()
  /// * Use dynamic_cast to get a pointer any open DialogWindow or AlertWindow.
  /// * Assign that pointer to a unique pointer so that the open window will be
  /// deleted when the unique pointer goes out of scope.
  void closeAllAlertAndDialogWindows();

  /// Pointer to the main window of the app.
  std::unique_ptr<MainWindow> mainWindow;
};
