//==============================================================================

#include "MainWindow.h"
#include "PluginEditor.h"
/*
 Set the window to use the native title bar for whatever OS the app is on.
 Create the main component and assign it to be the main content component
 of the window. The window should NOT conform to the main component
 when the content component changes size. See: ResizableWindow::setContentOwned().
 The window should be resizable and should use a bottom right corner sizer.
 The resize limits of the window should be a minimum 600 width and 400 height
 and double those values as the maximum.
 The window should appear in the center of the screen with its minimum width and height.
 Set its visibility to true.
 */
MainWindow::MainWindow(String name)
: DocumentWindow(name, Colours::white, DocumentWindow::allButtons) {
   setUsingNativeTitleBar(true);
   std::cout<< "SETTING NAME" << std::endl;
   setName("Clarinet Plugin");
//   ResizableWindow::setContentOwned(new MainComponent(), true);
   //resizeable and can use bottom right corner for resizing
   ResizableWindow::setResizable (true, true);
   ResizableWindow::setResizeLimits ( 600,400,1200,800);
   centreWithSize (600, 400);
   setVisible(true);



   // On windows or linux install the menubar in the window.
   // FIXME: on iOs or Android you will do something else!
#if JUCE_WINDOWS || JUCE_LINUX
   setMenuBar(MainApplication::getApp().getMenuBarModel());
#endif

   // add our content component. owned means that when the window is
   // deleted it will automatically delete our content component
//   auto maincomp = std::make_unique<PluginEditor>();
//   setContentOwned(maincomp.release(), false);

   // On laptops put the window in the middle of the screen with size
   // determined by our content component.
#if JUCE_MAC || JUCE_WINDOWS || JUCE_LINUX
   setResizable(true, true);
   setResizeLimits(500, 250, 1000, 500);
   centreWithSize(getWidth(), getHeight());
#else // JUCE_IOS || JUCE_ANDROID
   setFullScreen (true);
#endif
   // make the window visible
   setVisible(true);
}

MainWindow::~MainWindow() {
}

//==============================================================================
// DocumentWindow overrides
/*
 This is called when the user tries to close this window.
 Here, we'll just ask the app to quit when this happens,
 but you can change this to do whatever you need.
 */
void MainWindow::closeButtonPressed() {
  // when the main window is closed signal the app to exit
  JUCEApplication::getInstance()->systemRequestedQuit();
}


