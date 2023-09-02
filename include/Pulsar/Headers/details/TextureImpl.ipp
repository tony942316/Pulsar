/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PULSAR_DETAILS_TEXTUREIMPL_IPP
#define PULSAR_DETAILS_TEXTUREIMPL_IPP

#include "TextureDecl.hpp"

namespace pul
{
    constexpr Texture::Texture() noexcept
        :
        m_Texture(),
        m_FilePath()
    {
    }

    inline Texture::Texture(std::string_view filePath) noexcept
        :
        Texture()
    {
        init(filePath);
    }

    inline void Texture::init(std::string_view filePath) noexcept
    {
        m_Texture.init(delTex, genTex);
        m_FilePath.init(delStr, genStr);
        *m_FilePath.get() = filePath;

        enable();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;

        unsigned char* data = stbi_load(m_FilePath.get()->c_str(),
            &width, &height, &nrChannels, 0);
        eqx::runtimeAssert(data != nullptr,
            "Couldn't Load Texture: "s + *m_FilePath.get());

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        disable();
    }

    inline void Texture::free() noexcept
    {
        m_Texture.free();
        m_FilePath.free();
    }

    inline void Texture::enable() const noexcept
    {
        glBindTexture(GL_TEXTURE_2D, m_Texture.get());
    }

    inline void Texture::disable() const noexcept
    {
        glBindTexture(GL_TEXTURE_2D, 0U);
    }

    inline void Texture::enableTextureSlot(unsigned int i) noexcept
    {
        glActiveTexture(GL_TEXTURE0 + i);
    }

    [[nodiscard]] inline unsigned int Texture::genTex() noexcept
    {
        unsigned int tex;
        glGenTextures(1, &tex);
        return tex;
    }

    inline void Texture::delTex(unsigned int tex) noexcept
    {
        glDeleteTextures(1, &tex);
    }

    [[nodiscard]] inline std::string* Texture::genStr() noexcept
    {
        return new std::string();
    }

    inline void Texture::delStr(std::string* str) noexcept
    {
        delete str;
    }
}

#endif // PULSAR_DETAILS_TEXTUREIMPL_IPP
