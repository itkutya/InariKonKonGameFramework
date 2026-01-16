#include "InariKonKon/Assets/File/File.hpp"

namespace ikk
{
    File::File(const std::filesystem::path& path) noexcept
        : m_path(path)
    {
    }

    const std::filesystem::path& File::getPath() const noexcept
    {
        return this->m_path;
    }
}