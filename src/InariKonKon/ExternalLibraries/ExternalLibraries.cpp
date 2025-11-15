#include "InariKonKon/ExternalLibraries/ExternalLibraries.hpp"

#include "InariKonKon/ExternalLibraries/GLFW.hpp" // IWYU pragma: keep
#include "InariKonKon/Utility/Log.hpp"

namespace ikk
{
    ExternalLibraries::~ExternalLibraries() noexcept
    {
        glfwTerminate();
        this->m_initialized = false;
        DEBUG_LOG("Destroying glfw context.");
    }

    std::expected<void, Error> ExternalLibraries::init()
    {
        if (this->m_initialized == true)
        {
            DEBUG_LOG("GLFW context has already been created.");
            return {};
        }

        if (glfwInit() == GLFW_FALSE)
        {
            this->m_initialized = false;
            return std::unexpected(Error{ "Cannot initialize GLFW." });
        }

        this->m_initialized = true;
        DEBUG_LOG("GLFW context created.");
        return {};
    }
}