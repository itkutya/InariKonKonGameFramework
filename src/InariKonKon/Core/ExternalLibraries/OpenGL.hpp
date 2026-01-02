#ifndef IKK_OPENGL_UTILITIES_HPP
#define IKK_OPENGL_UTILITIES_HPP

#include "glad/gl.h"

#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
#ifdef IKK_DEBUG
    inline void glClearError() noexcept
    {
        while (glGetError() != GL_NO_ERROR);
    }

    inline void glLogCall(const char* function, const char* file, int line) noexcept
    {
        while (GLenum error = glGetError())
            DEBUG_LOG(Log::Level::Error, "OpenGL Error: error code: {}, function: {}, file: {}, line: {}", error, function, file, line);
    }

#define glCheck(x)                      \
    glClearError();                     \
    x;                                  \
    glLogCall(#x, __FILE__, __LINE__);
#else
#define glCheck(x) x
#endif
}

#endif