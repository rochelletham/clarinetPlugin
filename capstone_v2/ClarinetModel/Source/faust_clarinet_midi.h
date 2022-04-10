#include <cmath>
#include <cstring>

#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

// BEGIN-FAUSTDSP

<<includeIntrinsic>>
/* ------------------------------------------------------------
copyright: "(c)Romain Michon, CCRMA (Stanford University), GRAME"
license: "MIT"
name: "clarinetMIDI", "ClarinetMIDI"
Code generated with Faust 2.38.16 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

class mydspSIG0 {

  private:

   int iVec1[2];
   int iRec18[2];

  public:

   int getNumInputsmydspSIG0() {
      return 0;
   }
   int getNumOutputsmydspSIG0() {
      return 1;
   }

   void instanceInitmydspSIG0(int sample_rate) {
      for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
         iVec1[l6] = 0;
      }
      for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
         iRec18[l7] = 0;
      }
   }

   void fillmydspSIG0(int count, float* table) {
      for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
         iVec1[0] = 1;
         iRec18[0] = ((iVec1[1] + iRec18[1]) % 65536);
         table[i1] = std::sin((9.58738019e-05f * float(iRec18[0])));
         iVec1[1] = iVec1[0];
         iRec18[1] = iRec18[0];
      }
   }

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float mydsp_faustpower2_f(float value) {
   return (value * value);
}
static float ftbl0mydspSIG0[65536];

class mydsp : public dsp {

 private:

   FAUSTFLOAT fHslider0;
   int iRec6[2];
   FAUSTFLOAT fHslider1;
   float fRec12[2];
   FAUSTFLOAT fHslider2;
   FAUSTFLOAT fHslider3;
   FAUSTFLOAT fButton0;
   float fVec0[2];
   FAUSTFLOAT fHslider4;
   int fSampleRate;
   float fConst1;
   float fRec15[2];
   float fConst5;
   int iRec17[2];
   float fConst6;
   float fConst7;
   float fConst8;
   float fRec16[3];
   FAUSTFLOAT fHslider5;
   FAUSTFLOAT fHslider6;
   float fRec19[2];
   float fRec13[2];
   FAUSTFLOAT fHslider7;
   int IOTA0;
   float fRec14[2048];
   float fConst9;
   float fConst10;
   FAUSTFLOAT fHslider8;
   FAUSTFLOAT fHslider9;
   float fRec20[2];
   float fVec2[2];
   float fRec11[2];
   float fRec2[2048];
   float fRec0[2];

 public:

   void metadata(Meta* m) {
      m->declare("basics_lib_name", "Faust Basic Element Library");
      m->declare("basics_lib_version", "0.5");
      m->declare("compilation_options", "-single -scal -I libraries/ -I project/ -lang wasm");
      m->declare("compile_options", "-lang cpp -es 1 -mcd 16 -single -ftz 0 ");
      m->declare("copyright", "(c)Romain Michon, CCRMA (Stanford University), GRAME");
      m->declare("delays_lib_name", "Faust Delay Library");
      m->declare("delays_lib_version", "0.1");
      m->declare("description", "Simple MIDI-controllable clarinet physical model with physical parameters.");
      m->declare("filename", "clarinetMIDI.dsp");
      m->declare("filters_lib_fir_author", "Julius O. Smith III");
      m->declare("filters_lib_fir_copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
      m->declare("filters_lib_fir_license", "MIT-style STK-4.3 license");
      m->declare("filters_lib_iir_author", "Julius O. Smith III");
      m->declare("filters_lib_iir_copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
      m->declare("filters_lib_iir_license", "MIT-style STK-4.3 license");
      m->declare("filters_lib_lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
      m->declare("filters_lib_lowpass0_highpass1_author", "Julius O. Smith III");
      m->declare("filters_lib_lowpass_author", "Julius O. Smith III");
      m->declare("filters_lib_lowpass_copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
      m->declare("filters_lib_lowpass_license", "MIT-style STK-4.3 license");
      m->declare("filters_lib_name", "Faust Filters Library");
      m->declare("filters_lib_tf2_author", "Julius O. Smith III");
      m->declare("filters_lib_tf2_copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
      m->declare("filters_lib_tf2_license", "MIT-style STK-4.3 license");
      m->declare("filters_lib_tf2s_author", "Julius O. Smith III");
      m->declare("filters_lib_tf2s_copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
      m->declare("filters_lib_tf2s_license", "MIT-style STK-4.3 license");
      m->declare("filters_lib_version", "0.3");
      m->declare("library_path0", "/libraries/stdfaust.lib");
      m->declare("library_path1", "/libraries/physmodels.lib");
      m->declare("library_path10", "/libraries/delays.lib");
      m->declare("library_path2", "/libraries/signals.lib");
      m->declare("library_path3", "/libraries/basics.lib");
      m->declare("library_path4", "/libraries/maths.lib");
      m->declare("library_path5", "/libraries/platform.lib");
      m->declare("library_path6", "/libraries/oscillators.lib");
      m->declare("library_path7", "/libraries/noises.lib");
      m->declare("library_path8", "/libraries/filters.lib");
      m->declare("library_path9", "/libraries/routes.lib");
      m->declare("license", "MIT");
      m->declare("maths_lib_author", "GRAME");
      m->declare("maths_lib_copyright", "GRAME");
      m->declare("maths_lib_license", "LGPL with exception");
      m->declare("maths_lib_name", "Faust Math Library");
      m->declare("maths_lib_version", "2.5");
      m->declare("name", "clarinetMIDI");
      m->declare("noises_lib_name", "Faust Noise Generator Library");
      m->declare("noises_lib_version", "0.3");
      m->declare("oscillators_lib_name", "Faust Oscillator Library");
      m->declare("oscillators_lib_version", "0.3");
      m->declare("physmodels_lib_name", "Faust Physical Models Library");
      m->declare("physmodels_lib_version", "0.1");
      m->declare("platform_lib_name", "Generic Platform Library");
      m->declare("platform_lib_version", "0.2");
      m->declare("routes_lib_name", "Faust Signal Routing Library");
      m->declare("routes_lib_version", "0.2");
      m->declare("signals_lib_name", "Faust Signal Routing Library");
      m->declare("signals_lib_version", "0.1");
   }

   virtual int getNumInputs() {
      return 0;
   }
   virtual int getNumOutputs() {
      return 2;
   }

   static void classInit(int sample_rate) {
      mydspSIG0* sig0 = newmydspSIG0();
      sig0->instanceInitmydspSIG0(sample_rate);
      sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
      deletemydspSIG0(sig0);
   }

   virtual void instanceConstants(int sample_rate) {
      fSampleRate = sample_rate;
      float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
      fConst1 = (1.0f / fConst0);
      float fConst2 = std::tan((6283.18555f / fConst0));
      float fConst3 = (1.0f / fConst2);
      float fConst4 = (((fConst3 + 1.41421354f) / fConst2) + 1.0f);
      fConst5 = (0.0500000007f / fConst4);
      fConst6 = (1.0f / fConst4);
      fConst7 = (((fConst3 + -1.41421354f) / fConst2) + 1.0f);
      fConst8 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fConst2))));
      fConst9 = (0.00882352982f * fConst0);
      fConst10 = (0.00147058826f * fConst0);
   }

   virtual void instanceResetUserInterface() {
      fHslider0 = FAUSTFLOAT(0.5f);
      fHslider1 = FAUSTFLOAT(0.5f);
      fHslider2 = FAUSTFLOAT(0.59999999999999998f);
      fHslider3 = FAUSTFLOAT(0.0f);
      fButton0 = FAUSTFLOAT(0.0f);
      fHslider4 = FAUSTFLOAT(1.0f);
      fHslider5 = FAUSTFLOAT(0.25f);
      fHslider6 = FAUSTFLOAT(5.0f);
      fHslider7 = FAUSTFLOAT(0.5f);
      fHslider8 = FAUSTFLOAT(440.0f);
      fHslider9 = FAUSTFLOAT(0.0f);
   }

   virtual void instanceClear() {
      for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
         iRec6[l0] = 0;
      }
      for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
         fRec12[l1] = 0.0f;
      }
      for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
         fVec0[l2] = 0.0f;
      }
      for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
         fRec15[l3] = 0.0f;
      }
      for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
         iRec17[l4] = 0;
      }
      for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
         fRec16[l5] = 0.0f;
      }
      for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
         fRec19[l8] = 0.0f;
      }
      for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
         fRec13[l9] = 0.0f;
      }
      IOTA0 = 0;
      for (int l10 = 0; (l10 < 2048); l10 = (l10 + 1)) {
         fRec14[l10] = 0.0f;
      }
      for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
         fRec20[l11] = 0.0f;
      }
      for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
         fVec2[l12] = 0.0f;
      }
      for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
         fRec11[l13] = 0.0f;
      }
      for (int l14 = 0; (l14 < 2048); l14 = (l14 + 1)) {
         fRec2[l14] = 0.0f;
      }
      for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
         fRec0[l15] = 0.0f;
      }
   }

   virtual void init(int sample_rate) {
      classInit(sample_rate);
      instanceInit(sample_rate);
   }
   virtual void instanceInit(int sample_rate) {
      instanceConstants(sample_rate);
      instanceResetUserInterface();
      instanceClear();
   }

   virtual mydsp* clone() {
      return new mydsp();
   }

   virtual int getSampleRate() {
      return fSampleRate;
   }

   virtual void buildUserInterface(UI* ui_interface) {
      ui_interface->openVerticalBox("clarinet");
      ui_interface->declare(0, "0", "");
      ui_interface->openHorizontalBox("midi");
      ui_interface->declare(&fHslider8, "0", "");
      ui_interface->declare(&fHslider8, "style", "knob");
      ui_interface->addHorizontalSlider("freq", &fHslider8, FAUSTFLOAT(440.0f), FAUSTFLOAT(50.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider9, "1", "");
      ui_interface->declare(&fHslider9, "hidden", "1");
      ui_interface->declare(&fHslider9, "midi", "pitchwheel");
      ui_interface->declare(&fHslider9, "style", "knob");
      ui_interface->addHorizontalSlider("bend", &fHslider9, FAUSTFLOAT(0.0f), FAUSTFLOAT(-2.0f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider2, "2", "");
      ui_interface->declare(&fHslider2, "style", "knob");
      ui_interface->addHorizontalSlider("gain", &fHslider2, FAUSTFLOAT(0.600000024f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider4, "3", "");
      ui_interface->declare(&fHslider4, "style", "knob");
      ui_interface->addHorizontalSlider("envAttack", &fHslider4, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(30.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider3, "4", "");
      ui_interface->declare(&fHslider3, "hidden", "1");
      ui_interface->declare(&fHslider3, "midi", "ctrl 64");
      ui_interface->declare(&fHslider3, "style", "knob");
      ui_interface->addHorizontalSlider("sustain", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f));
      ui_interface->closeBox();
      ui_interface->declare(0, "1", "");
      ui_interface->openHorizontalBox("otherParams");
      ui_interface->declare(&fHslider7, "0", "");
      ui_interface->declare(&fHslider7, "midi", "ctrl 1");
      ui_interface->declare(&fHslider7, "style", "knob");
      ui_interface->addHorizontalSlider("reedStiffness", &fHslider7, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider1, "1", "");
      ui_interface->declare(&fHslider1, "midi", "ctrl 3");
      ui_interface->declare(&fHslider1, "style", "knob");
      ui_interface->addHorizontalSlider("bellOpening", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider6, "2", "");
      ui_interface->declare(&fHslider6, "style", "knob");
      ui_interface->addHorizontalSlider("vibratoFreq", &fHslider6, FAUSTFLOAT(5.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider5, "3", "");
      ui_interface->declare(&fHslider5, "style", "knob");
      ui_interface->addHorizontalSlider("vibratoGain", &fHslider5, FAUSTFLOAT(0.25f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->declare(&fHslider0, "4", "");
      ui_interface->declare(&fHslider0, "style", "knob");
      ui_interface->addHorizontalSlider("outGain", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
      ui_interface->closeBox();
      ui_interface->declare(&fButton0, "2", "");
      ui_interface->addButton("gate", &fButton0);
      ui_interface->closeBox();
   }

   virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
      FAUSTFLOAT* output0 = outputs[0];
      FAUSTFLOAT* output1 = outputs[1];
      float fSlow0 = float(fHslider0);
      float fSlow1 = float(fHslider1);
      float fSlow2 = (1.0f - fSlow1);
      float fSlow3 = std::min<float>(1.0f, (float(fHslider3) + float(fButton0)));
      float fSlow4 = (0.00100000005f * float(fHslider4));
      int iSlow5 = (std::fabs(fSlow4) < 1.1920929e-07f);
      float fThen1 = std::exp((0.0f - (fConst1 / (iSlow5 ? 1.0f : fSlow4))));
      float fSlow6 = (iSlow5 ? 0.0f : fThen1);
      float fSlow7 = ((float(fHslider2) * fSlow3) * (1.0f - fSlow6));
      float fSlow8 = (0.00999999978f * float(fHslider5));
      float fSlow9 = (fConst1 * float(fHslider6));
      float fSlow10 = ((0.25999999f * float(fHslider7)) + -0.439999998f);
      float fSlow11 = (170.0f / float(fHslider8));
      float fSlow12 = std::pow(2.0f, (0.0833333358f * float(fHslider9)));
      int iSlow13 = (fSlow3 == 0.0f);
      for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
         iRec6[0] = 0;
         fRec12[0] = ((fSlow2 * fRec11[1]) + (fSlow1 * fRec12[1]));
         float fRec10 = (fRec12[0] + float(iRec6[1]));
         fVec0[0] = fSlow3;
         fRec15[0] = (fSlow7 + (fSlow6 * fRec15[1]));
         iRec17[0] = ((1103515245 * iRec17[1]) + 12345);
         fRec16[0] = ((4.65661287e-10f * float(iRec17[0])) - (fConst6 * ((fConst7 * fRec16[2]) + (fConst8 * fRec16[1]))));
         float fTemp0 = (fRec15[0] * ((fConst5 * (fRec16[2] + (fRec16[0] + (2.0f * fRec16[1])))) + 1.0f));
         fRec19[0] = (fSlow9 + (fRec19[1] - std::floor((fSlow9 + fRec19[1]))));
         float fTemp1 = ftbl0mydspSIG0[int((65536.0f * fRec19[0]))];
         float fTemp2 = (fSlow8 * fTemp1);
         fRec13[0] = (fTemp0 + (fRec0[1] + fTemp2));
         float fTemp3 = (0.0f - fRec13[1]);
         fRec14[(IOTA0 & 2047)] = ((fTemp2 + fTemp0) + (fTemp3 * std::max<float>(-1.0f, std::min<float>(1.0f, ((fSlow10 * fTemp3) + 0.699999988f)))));
         float fTemp4 = float(((fSlow3 == fVec0[1]) | iSlow13));
         fRec20[0] = ((fSlow12 * (1.0f - (0.999000013f * fTemp4))) + (0.999000013f * (fTemp4 * fRec20[1])));
         float fTemp5 = (fConst10 * ((fSlow11 / (fRec20[0] * ((fSlow8 * (fRec15[0] * fTemp1)) + 1.0f))) + -0.0500000007f));
         float fTemp6 = (fTemp5 + -1.49999499f);
         int iTemp7 = int(fTemp6);
         int iTemp8 = (int(std::min<float>(fConst9, float(std::max<int>(0, int(iTemp7))))) + 1);
         float fTemp9 = std::floor(fTemp6);
         float fTemp10 = (fTemp5 + (-1.0f - fTemp9));
         float fTemp11 = (0.0f - fTemp10);
         float fTemp12 = (fTemp5 + (-2.0f - fTemp9));
         float fTemp13 = (0.0f - (0.5f * fTemp12));
         float fTemp14 = (fTemp5 + (-3.0f - fTemp9));
         float fTemp15 = (0.0f - (0.333333343f * fTemp14));
         float fTemp16 = (fTemp5 + (-4.0f - fTemp9));
         float fTemp17 = (0.0f - (0.25f * fTemp16));
         float fTemp18 = (fTemp5 - fTemp9);
         int iTemp19 = (int(std::min<float>(fConst9, float(std::max<int>(0, int((iTemp7 + 1)))))) + 1);
         float fTemp20 = (0.0f - fTemp12);
         float fTemp21 = (0.0f - (0.5f * fTemp14));
         float fTemp22 = (0.0f - (0.333333343f * fTemp16));
         int iTemp23 = (int(std::min<float>(fConst9, float(std::max<int>(0, int((iTemp7 + 2)))))) + 1);
         float fTemp24 = (0.0f - fTemp14);
         float fTemp25 = (0.0f - (0.5f * fTemp16));
         float fTemp26 = (fTemp10 * fTemp12);
         int iTemp27 = (int(std::min<float>(fConst9, float(std::max<int>(0, int((iTemp7 + 3)))))) + 1);
         float fTemp28 = (0.0f - fTemp16);
         float fTemp29 = (fTemp26 * fTemp14);
         int iTemp30 = (int(std::min<float>(fConst9, float(std::max<int>(0, int((iTemp7 + 4)))))) + 1);
         fVec2[0] = (((((fRec14[((IOTA0 - iTemp8) & 2047)] * fTemp11) * fTemp13) * fTemp15) * fTemp17) + (fTemp18 * ((((((fRec14[((IOTA0 - iTemp19) & 2047)] * fTemp20) * fTemp21) * fTemp22) + (0.5f * (((fTemp10 * fRec14[((IOTA0 - iTemp23) & 2047)]) * fTemp24) * fTemp25))) + (0.166666672f * ((fTemp26 * fRec14[((IOTA0 - iTemp27) & 2047)]) * fTemp28))) + (0.0416666679f * (fTemp29 * fRec14[((IOTA0 - iTemp30) & 2047)])))));
         fRec11[0] = fVec2[1];
         float fRec7 = fRec10;
         float fRec8 = fRec11[0];
         float fRec9 = fRec11[0];
         fRec2[(IOTA0 & 2047)] = fRec7;
         float fRec3 = (((((fTemp11 * fTemp13) * fTemp15) * fTemp17) * fRec2[((IOTA0 - iTemp8) & 2047)]) + (fTemp18 * ((((((fTemp20 * fTemp21) * fTemp22) * fRec2[((IOTA0 - iTemp19) & 2047)]) + (0.5f * (((fTemp10 * fTemp24) * fTemp25) * fRec2[((IOTA0 - iTemp23) & 2047)]))) + (0.166666672f * ((fTemp26 * fTemp28) * fRec2[((IOTA0 - iTemp27) & 2047)]))) + (0.0416666679f * (fTemp29 * fRec2[((IOTA0 - iTemp30) & 2047)])))));
         float fRec4 = fRec8;
         float fRec5 = fRec9;
         fRec0[0] = fRec3;
         float fRec1 = fRec5;
         float fTemp31 = (fSlow0 * fRec1);
         output0[i0] = FAUSTFLOAT(fTemp31);
         output1[i0] = FAUSTFLOAT(fTemp31);
         iRec6[1] = iRec6[0];
         fRec12[1] = fRec12[0];
         fVec0[1] = fVec0[0];
         fRec15[1] = fRec15[0];
         iRec17[1] = iRec17[0];
         fRec16[2] = fRec16[1];
         fRec16[1] = fRec16[0];
         fRec19[1] = fRec19[0];
         fRec13[1] = fRec13[0];
         IOTA0 = (IOTA0 + 1);
         fRec20[1] = fRec20[0];
         fVec2[1] = fVec2[0];
         fRec11[1] = fRec11[0];
         fRec0[1] = fRec0[0];
      }
   }

};

#endif

<<includeclass>>

// END-FAUSTDSP
