#include "InariKonKon/Assets/Texture/Texture.hpp"

namespace ikk
{
    Texture::Texture(const File& path) noexcept
    {
        //TODO:
    }

    Texture::Texture(std::uint32_t width, std::uint32_t height, std::uint32_t bytesPerPixel, const std::vector<std::byte>& buffer) noexcept
        : m_width(width), m_height(height), m_bytesPerPixel(bytesPerPixel), m_buffer(buffer)
    {
    }

    void Texture::create(std::uint32_t width, std::uint32_t height, std::uint32_t bytesPerPixel) noexcept
    {
        this->m_width = width;
        this->m_height = height;
        this->m_bytesPerPixel = bytesPerPixel;

        this->m_buffer.resize(this->m_width * this->m_height * this->m_bytesPerPixel, std::byte{0});
    }

    void Texture::load(const File& path) noexcept
    {
        Texture temp{path};
        this->m_buffer = temp.getBuffer();
    }

    void Texture::load(const std::vector<std::byte>& buffer) noexcept
    {
        if (this->m_width * this->m_height * this->m_bytesPerPixel != buffer.size())
            return;

        this->m_buffer = buffer;
    }

    const std::vector<std::byte>& Texture::getBuffer() const noexcept
    {
        return this->m_buffer;
    }
}