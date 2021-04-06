#!/bin/bash

gcc simple-egl-wayland.cpp -lEGL -lGLESv2 -lwayland-egl -lwayland-client -o simple-egl-display-wayland
