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

#ifndef PULSAR_DETAILS_SHADERDECL_HPP
#define PULSAR_DETAILS_SHADERDECL_HPP

#include "Dependencies.hpp"

#include "../ShaderGenerator.hpp"

namespace pul
{
    class Shader
    {
    public:
        explicit constexpr Shader() noexcept;
        explicit inline Shader(std::string_view vertexFilePath,
            std::string_view fragmentFilePath) noexcept;
        explicit inline Shader(const ShaderGenerator& sg) noexcept;

        inline void init(std::string_view vertexFilePath,
            std::string_view fragmentFilePath) noexcept;
        inline void init(const ShaderGenerator& sg) noexcept;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        inline void free() noexcept;

        inline void setInt(std::string_view name, int value) const noexcept;
        template <typename T>
            requires requires(const T& values)
            {
                std::ranges::size(values);
                std::ranges::data(values);
            }
        inline void setInts(std::string_view name,
            const T& values) const noexcept;
        inline void setFloat(std::string_view name, float value) const noexcept;
        inline void setVec4(std::string_view name,
            const glm::vec4& value) const noexcept;
        inline void setMat4(std::string_view name,
            const glm::mat4& value) const noexcept;

    private:
        [[nodiscard]] static inline unsigned int genShader() noexcept;
        static inline void delShader(unsigned int shader) noexcept;

        using ShaderID =
            eqx::UniqueResource<unsigned int, decltype(&delShader)>;

        [[nodiscard]] static inline std::string parseShader(
            std::string_view filePath) noexcept;
        [[nodiscard]] static inline unsigned int compileShader(
            unsigned int type, const char* src) noexcept;
        [[nodiscard]] static inline ShaderID linkShader(
            unsigned int vertexShader, unsigned int fragmentShader) noexcept;

        ShaderID m_Shader;
    };

    namespace shader
    {
        [[nodiscard]] static inline const Shader& getBasic() noexcept;
        [[nodiscard]] static inline Shader makeBasic() noexcept;
    }

    namespace batch
    {
        class Basic
        {
        public:
            explicit constexpr Basic() noexcept
                :
                m_Data()
            {
            }

            constexpr void setXYZ(std::size_t index, const glm::vec3& coord)
            {
                setX(index, coord.x);
                setY(index, coord.y);
                setZ(index, coord.z);
            }

            constexpr void setX(std::size_t index, float x) noexcept
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(0_size + (index * 3_size)) = x;
            }

            constexpr void setY(std::size_t index, float y) noexcept
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(1_size + (index * 3_size)) = y;
            }

            constexpr void setZ(std::size_t index, float z) noexcept
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(2_size + (index * 3_size)) = z;
            }

            constexpr const std::array<float, 600_size>& getData() noexcept
            {
                return m_Data;
            }

        private:
            std::array<float, 600_size> m_Data;
        };

        class VP
        {
        public:
            explicit constexpr VP() noexcept
                :
                m_Data()
            {
            }

            constexpr void setXYZ(std::size_t index, const glm::vec3& coord)
            {
                setX(index, coord.x);
                setY(index, coord.y);
                setZ(index, coord.z);
            }

            constexpr void setX(std::size_t index, float x) noexcept
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(0_size + (index * 9_size)) = x;
            }

            constexpr void setY(std::size_t index, float y) noexcept
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(1_size + (index * 9_size)) = y;
            }

            constexpr void setZ(std::size_t index, float z) noexcept
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(2_size + (index * 9_size)) = z;
            }

            constexpr void setTrans(std::size_t index, const glm::vec3& coord)
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(3_size + (index * 9_size)) = coord.x;
                m_Data.at(4_size + (index * 9_size)) = coord.y;
                m_Data.at(5_size + (index * 9_size)) = coord.z;
            }

            constexpr void setScale(std::size_t index, const glm::vec3& coord)
            {
                eqx::runtimeAssert(index < 200_size, "Batch Overflow"sv);
                m_Data.at(6_size + (index * 9_size)) = coord.x;
                m_Data.at(7_size + (index * 9_size)) = coord.y;
                m_Data.at(8_size + (index * 9_size)) = coord.z;
            }

            constexpr const std::array<float, 600_size>& getData() noexcept
            {
                return m_Data;
            }

        private:
            std::array<float, 600_size> m_Data;
        };
    }
}

#endif // PULSAR_DETAILS_SHADERDECL_HPP
