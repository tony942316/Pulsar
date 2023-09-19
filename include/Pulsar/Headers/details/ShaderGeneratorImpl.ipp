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

#ifndef PULSAR_SHADERGENERATORIMPL_IPP
#define PULSAR_SHADERGENERATORIMPL_IPP

#include "ShaderGeneratorDecl.hpp"

namespace pul
{
    constexpr ShaderGenerator::ShaderGenerator() noexcept
        :
        m_VertexSource(),
        m_FragmentSource(),
        m_VC(nullptr),
        m_FC(nullptr)
    {
    }

    inline ShaderGenerator::ShaderGenerator(const ShaderConfig& vc,
        const ShaderConfig& fc) noexcept
        :
        ShaderGenerator()
    {
        init(vc, fc);
    }

    inline void ShaderGenerator::init(const ShaderConfig& vc,
        const ShaderConfig& fc) noexcept
    {
        m_VertexSource.init();
        m_FragmentSource.init();
        m_VC = &vc;
        m_FC = &fc;

        *m_VertexSource.get() += "#version 450 core\n";

        std::ranges::for_each(vc.inputs,
            [&](const std::string& input)
            {
                *m_VertexSource.get() += input + "\n";
            });

        std::ranges::for_each(vc.uniforms,
            [&](const std::string& uniform)
            {
                *m_VertexSource.get() += uniform + "\n";
            });

        std::ranges::for_each(vc.outputs,
            [&](const std::string& output)
            {
                *m_VertexSource.get() += output + "\n";
            });

        *m_VertexSource.get() += "void main()\n";
        *m_VertexSource.get() += "{\n";
        *m_VertexSource.get() += vc.code;
        *m_VertexSource.get() += "}\n";

        *m_FragmentSource.get() += "#version 450 core\n";

        std::ranges::for_each(fc.inputs,
            [&](const std::string& input)
            {
                *m_FragmentSource.get() += input + "\n";
            });

        std::ranges::for_each(fc.uniforms,
            [&](const std::string& uniform)
            {
                *m_FragmentSource.get() += uniform + "\n";
            });

        std::ranges::for_each(fc.outputs,
            [&](const std::string& output)
            {
                *m_FragmentSource.get() += output + "\n";
            });

        *m_FragmentSource.get() += "void main()\n";
        *m_FragmentSource.get() += "{\n";
        *m_FragmentSource.get() += fc.code;
        *m_FragmentSource.get() += "}\n";
    }

    inline const std::string&
        ShaderGenerator::getVertexSource() const noexcept
    {
        return *m_VertexSource.get();
    }

    inline const std::string&
        ShaderGenerator::getFragmentSource() const noexcept
    {
        return *m_FragmentSource.get();
    }
}

#endif // PULSAR_SHADERGENERATORIMPL_IPP
