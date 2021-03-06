/* gb-util.h
 *
 * Copyright (C) 2013 Christian Hergert <christian@hergert.me>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GB_UTIL_H
#define GB_UTIL_H

#include <gdk/gdk.h>

G_BEGIN_DECLS


void
_gb_rgba_shade (const GdkRGBA *color,
                gdouble        factor,
                GdkRGBA       *result);

G_END_DECLS

#endif /* GB_UTIL_H */
