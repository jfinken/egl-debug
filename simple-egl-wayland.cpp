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

#include <GLES2/gl2.h>         
#include <GLES2/gl2ext.h>
#include <GLES3/gl31.h>

// gcc simple-egl-wayland.cpp -lEGL -lGLESv2 -lwayland-egl -lwayland-client -o simple-egl-display-wayland

int GlActiveSyncWait() {
  	GLsync sync;
	sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	// Since creating a Sync object is itself a GL command it *must* be flushed.
	// Otherwise glGetSynciv may never succeed. Perform a flush with
 	// glClientWaitSync call.
    printf("glClientWaitSync...\n");
	GLenum status = glClientWaitSync(sync, GL_SYNC_FLUSH_COMMANDS_BIT,
									   /* timeout ns = */ 0);
    printf("...is done\n");
	switch (status) {
		case GL_TIMEOUT_EXPIRED:
		  break;
		case GL_CONDITION_SATISFIED:
		case GL_ALREADY_SIGNALED:
    	  printf("GL_COND_SATISFIED or GL_ALREADY_SIGNALED\n");
		  return 0;
		case GL_WAIT_FAILED:
    	  printf("GL_WAIT_FAILED\n");
		  return 1;
	}
	// Start active loop.
	GLint result = GL_UNSIGNALED;
	while (true) {
        printf("while(true) on glGetSynciv...\n");
		glGetSynciv(sync, GL_SYNC_STATUS, sizeof(GLint), nullptr, &result);
        printf("glGetSynciv...done\n");
		if (result == GL_SIGNALED) {
    	  printf("while(true) on glGetSynciv...GL_SIGNALED\n");
		  return 0;
		}
	}
}

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
    printf("Attempting Wayland display...\n");
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
    printf("Woot! wl_display_connect worked...\n");

	GlActiveSyncWait();

    return 0;
}
