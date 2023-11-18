/* Copyright 2023 Steuv1871
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define TAPPING_TOGGLE 2

// Redefine ENCODER PINS as they are mixed up in info.json for my board
#undef ENCODERS_PAD_A
#undef ENCODERS_PAD_B
#define ENCODERS_PAD_A { C7, B3 }
#define ENCODERS_PAD_B { B7, B2 }

#define ENCODER_RESOLUTION 4
