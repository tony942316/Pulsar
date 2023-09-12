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

namespace pul
{
    class Quad
    {
    public:
        explicit constexpr Quad() noexcept;
        explicit inline Quad(const eqx::Rectangle<float>& drawBox) noexcept;

        inline void setMixture(float mixture) noexcept;
        inline void setColor(const glm::vec4 color) noexcept;
        inline void setDrawBox(const eqx::Rectangle<float>& drawBox) noexcept;
        inline void setTexture(Texture* texture) noexcept;
        inline void setTextureIndex(unsigned int index) noexcept;

        [[nodiscard]] constexpr const Texture& getTexture() const noexcept;
        [[nodiscard]] constexpr const std::array<float, 40_size>&
            getVertexData() const noexcept;
        [[nodiscard]] constexpr eqx::Rectangle<float>
            getDrawBox() const noexcept;
        [[nodiscard]] constexpr glm::vec4 getColor() const noexcept;
        [[nodiscard]] constexpr float getMixture() const noexcept;

        [[nodiscard]] static constexpr const std::array<int, 5_size>&
            getAttribs() noexcept;
        [[nodiscard]] static constexpr const std::array<unsigned int, 6_size>&
            getIndices() noexcept;

    private:
        Texture* m_Texture;
        /*
            x, y, ts, tt, r, g, b, a, m, ti
            0, 1, 2,  3,  4, 5, 6, 7, 8, 9
         */
        std::array<float, 40_size> m_VertexData;

        static constexpr auto c_X = std::array<std::size_t, 4_size>({
            0_size, 10_size, 20_size, 30_size });

        static constexpr auto c_R = c_X | std::views::transform(
            [](std::size_t x) constexpr { return x + 4_size; });
        static constexpr auto c_M = c_X | std::views::transform(
            [](std::size_t x) constexpr { return x + 8_size; });
        static constexpr auto c_T = c_X | std::views::transform(
            [](std::size_t x) constexpr { return x + 9_size; });

        static constexpr auto c_Attribs = std::array<int, 5_size>({
            2, 2, 4, 1, 1 });

        static constexpr auto c_Indices = std::array<unsigned int, 6_size>({
            0U, 1U, 2U,
            0U, 2U, 3U });
    };
}

#endif // PULSAR_DETAILS_QUADDECL_HPP
