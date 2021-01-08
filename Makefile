
.PHONY : all
all : 
	gcc simple-egl.cpp -lEGL -lGLESv2 -lwayland-egl -lwayland-client -o simple-egl-display
	gcc simple-egl.cpp -lEGL -lGLESv2 -o simple-egl-display
