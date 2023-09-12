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

#ifndef PULSAR_DETAILS_RENDERERDECL_HPP
#define PULSAR_DETAILS_RENDERERDECL_HPP

#include "Dependencies.hpp"

#include "../Shader.hpp"
#include "../VertexArray.hpp"
#include "../Texture.hpp"
#include "../Quad.hpp"

namespace pul
{
    class Renderer
    {
    public:
        Renderer() = delete;
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&&) = delete;
        Renderer& operator= (const Renderer&) = delete;
        Renderer& operator= (Renderer&&) = delete;
        ~Renderer() = delete;

        static inline void draw(const Shader& shader,
            const VertexArray& vertexArray) noexcept;
        static inline void draw(Quad& quad) noexcept;
        static inline void draw(std::vector<Quad>& quads) noexcept;
        static inline void drawText(std::vector<Quad>& quads) noexcept;

        static inline void init(float width, float height) noexcept;

    private:
        constinit static inline auto s_QuadShader = Shader();
        constinit static inline auto s_TextShader = Shader();
        constinit static inline auto s_VA = VertexArray();
    };
}

#endif // PULSAR_DETAILS_RENDERERDECL_HPP
