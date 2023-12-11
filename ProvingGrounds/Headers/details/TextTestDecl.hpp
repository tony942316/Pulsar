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

#ifndef PROVINGGROUNDS_DETAILS_TEXTTESTDECL_HPP
#define PROVINGGROUNDS_DETAILS_TEXTTESTDECL_HPP

#include "Dependencies.hpp"

class TextTest
{
public:
    TextTest() = delete;
    TextTest(const TextTest&) = delete;
    TextTest(TextTest&&) = delete;
    TextTest& operator= (const TextTest&) = delete;
    TextTest& operator= (TextTest&&) = delete;
    ~TextTest() = delete;

    static inline void update() noexcept;
    static inline void render() noexcept;

private:
    constinit static inline auto s_Font = pul::Font();
    constinit static inline auto s_LowerCase = pul::batch::QuadT();
    constinit static inline auto s_UpperCase = pul::batch::QuadT();
    constinit static inline auto s_Phrase = pul::batch::QuadT();
};

#endif // PROVINGGROUNDS_DETAILS_TEXTTESTDECL_HPP
