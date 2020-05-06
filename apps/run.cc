// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include "home_finder_app.h"

using cinder::app::App;
using cinder::app::RendererGl;


namespace homefinderapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Home Finder Application");
}

}  // namespace homefinderapp


// This is a macro that runs the application.
CINDER_APP(homefinderapp::HomeFinderApp,
           RendererGl(RendererGl::Options().msaa(homefinderapp::kSamples)),
           homefinderapp::SetUp)
