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

#ifndef PROVINGGROUNDS_DETAILS_UIDECL_HPP
#define PROVINGGROUNDS_DETAILS_UIDECL_HPP

#include "Dependencies.hpp"

class Ui
{
public:
    Ui() = delete;
    Ui(const Ui&) = delete;
    Ui(Ui&&) = delete;
    Ui& operator= (const Ui&) = delete;
    Ui& operator= (Ui&&) = delete;
    ~Ui() = delete;

    static inline bool update() noexcept;
    static inline void render() noexcept;

private:
    constinit static inline auto s_Button = pul::CQuad();
};

#endif // PROVINGGROUNDS_DETAILS_UIDECL_HPP
