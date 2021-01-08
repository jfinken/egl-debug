#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>


// gcc simple-egl.cpp -lEGL -lGLESv2 -o simple-egl-display

int main(int argc, char *argv[]) {

    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    EGLConfig config;
    EGLBoolean result;

    // No real X11 on Mendel
    // Display *x_display = XOpenDisplay(NULL);
    // display = eglGetDisplay((EGLNativeDisplayType) x_display);

    // TF Lite gpu-delegate code:
    EGLDisplay _display = eglGetCurrentDisplay();

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (display == EGL_NO_DISPLAY) {
        fprintf(stderr, "EGL_NO_DISPLAY...\n");
        return 1;
    } 
	
    // initialize the EGL display connection
    result = eglInitialize(display, NULL, NULL);

    if (result == EGL_FALSE) {
        fprintf(stderr, "Cannot initialize EGL via the default display...\n");
        return 1;
    }

    return 0;
}
