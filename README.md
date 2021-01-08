
#### quick debug program describing this issue

https://github.com/tensorflow/tensorflow/issues/46163

#### compile the simple-egl code (on a system with Wayland and X11)
```
gcc simple-egl.cpp -lEGL -lGLESv2 -o simple-egl-display
gcc simple-egl-wayland.cpp -lEGL -lGLESv2 -lwayland-egl -lwayland-client -o simple-egl-display-wayland

# or
make
```

#### cmake build OpenGLESHelloAPI_LinuxX11 code
```
mkdir build && cd build
cmake -DPVR_WINDOW_SYSTEM=X11 ..
# or cmake -DPVR_WINDOW_SYSTEM=Wayland ..
make
```

```
$ simple-egl-display-wayland
EGL: Warning: No default display support on wayland
EGL NO DISPLAY
```

The PowerVR-Graphics stuff (DynamicGles.h, etc) are [from this repo](https://github.com/powervr-graphics/Native_SDK)

I simply copied those three headers here.

[This post describes](https://docs.imgtec.com/Framework_DevGuide/topics/General_Overview/Additional_Header_Files/c_PVRFramework_dynamic.html) what is DynamicGles.h etc

