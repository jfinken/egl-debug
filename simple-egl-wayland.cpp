#include <stdio.h>
#include <assert.h>
#include <math.h>

//#include <X11/Xlib.h>
//#include <X11/Xlibint.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <errno.h>
#include <cstring>
#include <wayland-egl.h>

// gcc simple-egl.cpp -lEGL -lGLESv2 -lwayland-egl -lwayland-client -o simple-egl-display

int main(int argc, char *argv[]) {

    EGLNativeDisplayType egl_native_display;
    EGLDisplay egl_display_wayland;
	EGLint major_version, minor_version;


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
    printf("%p\n", _display);

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (display == EGL_NO_DISPLAY) {
        printf("EGL NO DISPLAY (because we likely do not support Wayland properly...)\n");
        //return 1;
    } else {
	
		// initialize the EGL display connection
		result = eglInitialize(display, NULL, NULL);

		if (result == EGL_FALSE) {
			fprintf(stderr, "Can't initialise EGL via the default display...\n");
			// return 1;
		}
	}

    // Requires wayland
	// char const *p_name;
    printf("Using default Wayland display...\n");
    egl_native_display = EGLNativeDisplayType(wl_display_connect(NULL));
	if (egl_native_display == NULL) {
		printf("wl_display_connect failed: %s\n", strerror(errno));
		return 1;
	} else {

		// Now initialize EGL!
		egl_display_wayland = eglGetDisplay(egl_native_display);

		if (egl_display_wayland == EGL_NO_DISPLAY){
			printf("Could not obtain EGL display (wayland)\n");
			return 1;
		}

		if (!eglInitialize(egl_display_wayland, &major_version, &minor_version))
		{
			printf("Could not initialize EGL (wayland)");
			egl_display_wayland = EGL_NO_DISPLAY;
			return 1;
		}	
	}


    return 0;
}
