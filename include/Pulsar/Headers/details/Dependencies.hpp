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

#ifndef PULSAR_DETAILS_DEPENDENCIES_HPP
#define PULSAR_DETAILS_DEPENDENCIES_HPP

#include "../../Dependencies/Equinox/include/Equinox/Equinox.hpp"
#include "../../Dependencies/glad/include/glad/glad.h"
#include "../../Dependencies/glfw/include/GLFW/glfw3.h"
#include "../../Dependencies/glm/glm/glm.hpp"
#include "../../Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/glm/gtc/type_ptr.hpp"

namespace pul
{
    using namespace eqx::literals;
    using namespace eqx::TimeTypes;
}

#endif // PULSAR_DETAILS_DEPENDENCIES_HPP
