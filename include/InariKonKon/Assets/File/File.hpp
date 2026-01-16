#ifndef IKK_FILE_HPP
#define IKK_FILE_HPP

#include <filesystem>

namespace ikk
{
    class [[nodiscard]] File
    {
    public:
        [[nodiscard]] File(const std::filesystem::path& path) noexcept;

        File(const File&) noexcept = default;
        File(File&&) noexcept = default;

        File& operator=(const File&) noexcept = default;
        File& operator=(File&&) noexcept = default;

        virtual ~File() noexcept = default;

        const std::filesystem::path& getPath() const noexcept;
    private:
        std::filesystem::path m_path;
    };
}

#endif