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

#ifndef PROVINGGROUNDS_DETAILS_TESTERDECL_HPP
#define PROVINGGROUNDS_DETAILS_TESTERDECL_HPP

#include "Dependencies.hpp"

#include "../Ui.hpp"
#include "../QuadTest.hpp"
#include "../TextTest.hpp"
#include "../CubeTest.hpp"
#include "../BlenderTest.hpp"
#include "../BatchTest.hpp"

class Tester
{
public:
    enum class State
    {
        None,
        Quad,
        Text,
        Cube,
        Blender,
        Batch
    };

    Tester() = delete;
    Tester(const Tester&) = delete;
    Tester(Tester&&) = delete;
    Tester& operator= (const Tester&) = delete;
    Tester& operator= (Tester&&) = delete;
    ~Tester() = delete;

    static inline void run() noexcept;
    static inline void update() noexcept;
    static inline void render() noexcept;

private:
    constinit static inline auto s_Window = pul::Window();

    constinit static inline auto s_State = State::None;
};

#endif // PROVINGGROUNDS_DETAILS_TESTERDECL_HPP
