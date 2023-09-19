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

#ifndef PULSAR_DETAILS_QUADDECL_HPP
#define PULSAR_DETAILS_QUADDECL_HPP

#include "Dependencies.hpp"

#include "../Texture.hpp"
#include "../Shader.hpp"

namespace pul::shader
{
    [[nodiscard]] inline const Shader& getQuad() noexcept;
    [[nodiscard]] inline Shader makeQuad() noexcept;
}

namespace pul::batch
{
    class Quad
    {
    public:
        explicit constexpr Quad() noexcept;

        constexpr void setRect(std::size_t index,
            eqx::Rectangle<float> rect) noexcept;

        constexpr void setTexture(std::size_t index,
            const Texture& texture) noexcept;

        inline void enableTextures() const noexcept;

        constexpr const std::array<float, 640_size>& getData() const noexcept;

        static inline void setUniforms(float w, float h) noexcept;

        static consteval const std::array<unsigned int, 192_size>&
            getIndices() noexcept;

        static consteval const std::array<int, 3_size>& getAttribs() noexcept;

    private:
        std::array<float, 640_size> m_Data;
        std::array<const Texture*, 32_size> m_Textures;

        static constexpr auto c_Attribs = std::array<int, 3_size>({ 2, 2, 1 });
        static constexpr auto c_Indices = std::invoke(
            []() constexpr
            {
                constexpr auto c_Mask = std::array<unsigned int, 6_size>({
                    0U, 1U, 2U,
                    0U, 2U, 3U });

                auto result = std::array<unsigned int, 192_size>();

                auto off = 0_size;
                auto trans = 0U;
                for (auto index = 0_size; index < 32_size; index++)
                {
                    off = index * 6_size;
                    trans = static_cast<unsigned int>(index) * 4U;

                    result.at(0_size + off) =
                        c_Mask.at(0_size) + trans;
                    result.at(1_size + off) =
                        c_Mask.at(1_size) + trans;
                    result.at(2_size + off) =
                        c_Mask.at(2_size) + trans;
                    result.at(3_size + off) =
                        c_Mask.at(3_size) + trans;
                    result.at(4_size + off) =
                        c_Mask.at(4_size) + trans;
                    result.at(5_size + off) =
                        c_Mask.at(5_size) + trans;
                }

                return result;
            });

        /*
            x, y, s, t, tex
            0, 1, 2, 3, 4
            0, ...
            0, ...
            0, ...
        */
        static constexpr auto c_IndexX = 0_size;
        static constexpr auto c_IndexY = 1_size;
        static constexpr auto c_IndexS = 2_size;
        static constexpr auto c_IndexT = 3_size;
        static constexpr auto c_IndexTex = 4_size;

        static constexpr auto c_VStride = 5_size;
        static constexpr auto c_QStride = c_VStride * 4_size;
    };
}

#endif // PULSAR_DETAILS_QUADDECL_HPP
