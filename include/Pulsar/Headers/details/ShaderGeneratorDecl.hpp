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

#ifndef PULSAR_SHADERGENERATORDECL_HPP
#define PULSAR_SHADERGENERATORDECL_HPP

#include "Dependencies.hpp"

namespace pul
{
    class ShaderGenerator
    {
    public:
        struct ShaderConfig
        {
            std::vector<std::string> inputs;
            std::vector<std::string> uniforms;
            std::vector<std::string> outputs;
            std::string code;
        };

        explicit constexpr ShaderGenerator() noexcept;

        explicit inline ShaderGenerator(const ShaderConfig& vc,
            const ShaderConfig& fc) noexcept;

        inline void init(const ShaderConfig& vc,
            const ShaderConfig& fc) noexcept;

        inline const std::string& getVertexSource() const noexcept;

        inline const std::string& getFragmentSource() const noexcept;

    private:
        eqx::UniquePointer<std::string> m_VertexSource;
        eqx::UniquePointer<std::string> m_FragmentSource;

        const ShaderConfig* m_VC;
        const ShaderConfig* m_FC;
    };
}

#endif // PULSAR_SHADERGENERATORDECL_HPP
