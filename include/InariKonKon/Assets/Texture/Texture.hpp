#pragma once

#include <cstddef>
#include <vector>

#include "InariKonKon/Assets/File/File.hpp"

namespace ikk
{
    class [[nodiscard]] Texture final
    {
    public:
        [[nodiscard]] Texture() noexcept = default;
        [[nodiscard]] Texture(const File& path) noexcept;
        [[nodiscard]] Texture(std::uint32_t width, std::uint32_t height, std::uint32_t bytesPerPixel, const std::vector<std::byte>& buffer) noexcept;

        Texture(const Texture&) noexcept = default;
        Texture(Texture&&) noexcept = default;

        Texture& operator=(const Texture&) noexcept = default;
        Texture& operator=(Texture&&) noexcept = default;

        ~Texture() noexcept = default;

        void create(std::uint32_t width, std::uint32_t height, std::uint32_t bytesPerPixel = 1) noexcept;

        void load(const File& path) noexcept;
        void load(const std::vector<std::byte>& buffer) noexcept;

        const std::vector<std::byte>& getBuffer() const noexcept;
        const std::uint32_t getWidth() const noexcept;
        const std::uint32_t getHeight() const noexcept;
        const std::uint32_t getBytesPerPixel() const noexcept;
    private:
        std::uint32_t m_width = 0;
        std::uint32_t m_height = 0;
        std::uint32_t m_bytesPerPixel = 0;

        std::vector<std::byte> m_buffer{};
    };
}