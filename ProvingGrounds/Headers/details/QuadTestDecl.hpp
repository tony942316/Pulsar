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

#ifndef PROVINGGROUNDS_DETAILS_QUADTESTDECL_HPP
#define PROVINGGROUNDS_DETAILS_QUADTESTDECL_HPP

#include "Dependencies.hpp"

class QuadTest
{
public:
    QuadTest() = delete;
    QuadTest(const QuadTest&) = delete;
    QuadTest(QuadTest&&) = delete;
    QuadTest& operator= (const QuadTest&) = delete;
    QuadTest& operator= (QuadTest&&) = delete;
    ~QuadTest() = delete;

    static inline void update() noexcept;
    static inline void render() noexcept;

private:
    constinit static inline auto s_Face = pul::TxQuad();
    constinit static inline auto s_Face2 = pul::TxQuad();
    constinit static inline auto s_Cat = pul::TxQuad();
};

#endif // PROVINGGROUNDS_DETAILS_QUADTESTDECL_HPP
