/*
 * Copyright (C) 2024 Anthony H. Grasso
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

#ifndef PROVINGGROUNDS_DETAILS_BATCHTESTDECL_HPP
#define PROVINGGROUNDS_DETAILS_BATCHTESTDECL_HPP

#include "Dependencies.hpp"

class BatchTest
{
public:
    BatchTest() = delete;
    BatchTest(const BatchTest&) = delete;
    BatchTest(BatchTest&) = delete;
    BatchTest& operator= (const BatchTest&) = delete;
    BatchTest& operator= (BatchTest&&) = delete;
    ~BatchTest() = delete;

    static inline void update(float dt) noexcept;
    static inline void render() noexcept;

private:
    static inline void shuffle() noexcept;

    constinit static inline auto s_Batch1 = std::array<pul::TxQuad, 32ULL>();
    constinit static inline auto s_Batch2 = std::array<pul::TxQuad, 64ULL>();
};

#endif // PROVINGGROUNDS_DETAILS_BATCHTESTDECL_HPP
