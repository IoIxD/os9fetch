#include "functions.hpp"
#include <GL/gl.h>
#include <gl.h>

extern "C"
{
    void gpu_raw()
    {
#ifdef FOR_PPC
        const GLubyte *vendor = glGetString(GL_VENDOR);     // Returns the vendor
        const GLubyte *renderer = glGetString(GL_RENDERER); // Returns a hint to the model
        printf("%s, %s", vendor, renderer);
#endif
    }
}
namespace detection
{
    void gpu()
    {
        gpu_raw();
    }

}
