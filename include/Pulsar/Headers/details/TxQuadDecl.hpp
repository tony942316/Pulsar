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

#ifndef PULSAR_DETAILS_TXQUADDECL_HPP
#define PULSAR_DETAILS_TXQUADDECL_HPP

#include "Dependencies.hpp"

#include "../Texture.hpp"
#include "../Batch.hpp"

namespace pul
{
    class TxQuad
    {
    public:
        explicit constexpr TxQuad() noexcept;
        explicit constexpr TxQuad(const eqx::Rectangle<float>& rect,
            const Texture& tex) noexcept;

        constexpr void setLoc(const eqx::Point<float>& loc) noexcept;
        constexpr void setRect(const eqx::Rectangle<float>& rect) noexcept;
        constexpr void setTexture(const Texture& tex) noexcept;

        [[nodiscard]] constexpr eqx::Point<float> getLoc() const noexcept;
        [[nodiscard]] constexpr eqx::Rectangle<float> getRect() const noexcept;
        [[nodiscard]] constexpr const Texture& getTexture() const noexcept;

        [[nodiscard]] static constexpr Batch<5_size, 4_size>
            batch(std::span<TxQuad> quads) noexcept;
        [[nodiscard]] static constexpr
            std::span<const int> getAttribs() noexcept;
        [[nodiscard]] static constexpr
            std::span<const unsigned int> getIndices() noexcept;

    private:
        eqx::Rectangle<float> m_Rect;
        const Texture* m_Tex;

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
    };
}

#endif // PULSAR_DETAILS_TXQUADDECL_HPP
