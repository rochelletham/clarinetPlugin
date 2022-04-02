//==============================================================================

#include "MainApplication.h"
#include "MainWindow.h"
//#include "MainComponent.h"

//==============================================================================
// MainApplication members

MainApplication& MainApplication::getApp() {
  MainApplication* const app = dynamic_cast<MainApplication*>(JUCEApplication::getInstance());
  jassert(app != nullptr);
  return *app;
}

/*

 Iterate all the top-level components in juce::Desktop::getInstance()
 Use dynamic_cast to get a pointer any open DialogWindow or AlertWindow.
 Assign that pointer to a unique pointer so that the open window will
 be deleted when the unique pointer goes out of scope.
 */
void MainApplication::closeAllAlertAndDialogWindows() {
  
}

//==============================================================================
// JUCEApplication overrides

MainApplication::MainApplication() {
}

const String MainApplication::getApplicationName() {
//  return ProjectInfo::projectName
   return "Clarinet Plugin";
}

const String MainApplication::getApplicationVersion() {
  return ProjectInfo::versionString;
}

bool MainApplication::moreThanOneInstanceAllowed() {
  return false;
}
//
//Initialize the audioDeviceManager to 0 input channels
//and 2 output channels. See: audioDeviceManager::initialise().
//Raise an assertion if initialization results in an non-null error message. See: jassert().
//Create the application window.
void MainApplication::initialise(const String& commandLine) {
  // initialize the audio device manager
   auto errors = audioDeviceManager.initialise(0, 2, nullptr, true);
  // use jassert to ensure audioError is empty
   jassert(errors.isEmpty());
  // Create the application window.
  mainWindow = std::make_unique<MainWindow>(getApplicationName());
}

void MainApplication::shutdown() {
  // Delete our main window
  mainWindow = nullptr;
}

void MainApplication::systemRequestedQuit() {
  closeAllAlertAndDialogWindows();
  quit();
}

void MainApplication::anotherInstanceStarted(const String& commandLine) {
}

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (MainApplication)
