#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#define DYNAMICGLES_NO_NAMESPACE
#define DYNAMICEGL_NO_NAMESPACE
#include "DynamicGles.h"

using namespace std;

int main(int /*argc*/, char** /*argv*/) {
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    cout << "Creating sync with glFenceSync" << endl;
    GLsync sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glWaitSync(sync, 0, GL_TIMEOUT_IGNORED);
    GLenum err = glGetError();
    assert(err == GL_NO_ERROR);

    GLsizei length = 0;
    GLint value = 0;
    unsigned int loopCount = 0;

    // cout << "glFlush..." << endl;
    // glFlush();

    // Use 'loopCount' to make sure the test doesn't get stuck in an infinite loop
    cout << "glGetSynciv while-loop..." << endl;
    while (value != GL_SIGNALED /*&& loopCount <= 1000000*/) {
        loopCount++;

        cout << "value: " << std::hex << value << endl;
        // glGetSynciv(sync, GL_SYNC_STATUS, 1, &length, &value);
        glGetSynciv(sync, GL_SYNC_STATUS, sizeof(GLint), nullptr, &value);

        GLenum err = glGetError();
        assert(err == GL_NO_ERROR);
    }
    cout << "glGetSynciv while-loop...done.  loopCount: " << loopCount << endl;
    assert(value == GL_SIGNALED);

    cout << "glClientWaitSync for-loop..." << endl;
    for (size_t i = 0; i < 20; i++) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClientWaitSync(sync, GL_SYNC_FLUSH_COMMANDS_BIT, GL_TIMEOUT_IGNORED);
        GLenum err = glGetError();
        assert(err == GL_NO_ERROR);
    }
    cout << "glClientWaitSync for-loop...done" << endl;

    return 0;
}