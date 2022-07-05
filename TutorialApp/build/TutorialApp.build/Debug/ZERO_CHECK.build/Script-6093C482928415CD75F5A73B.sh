#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/adrianm2/Desktop/TutorialApp/build
  make -f /Users/adrianm2/Desktop/TutorialApp/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/adrianm2/Desktop/TutorialApp/build
  make -f /Users/adrianm2/Desktop/TutorialApp/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/adrianm2/Desktop/TutorialApp/build
  make -f /Users/adrianm2/Desktop/TutorialApp/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/adrianm2/Desktop/TutorialApp/build
  make -f /Users/adrianm2/Desktop/TutorialApp/build/CMakeScripts/ReRunCMake.make
fi

