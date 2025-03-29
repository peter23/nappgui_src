# NAppGUI CMake targets

set(ALL_TARGETS "")
set(ALL_TARGETS ${ALL_TARGETS};src/sewer;src/osbs;src/core;src/geom2d;src/draw2d;src/osgui;src/gui;src/osapp;src/inet;src/ogl3d;tools/nrc)

if (NAPPGUI_DEMO)
    set(ALL_TARGETS ${ALL_TARGETS};demo)
endif()