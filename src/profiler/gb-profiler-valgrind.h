/* gb-profiler-valgrind.h
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

#ifndef GB_PROFILER_VALGRIND_H
#define GB_PROFILER_VALGRIND_H

#include "gb-profiler.h"

G_BEGIN_DECLS

#define GB_TYPE_PROFILER_VALGRIND            (gb_profiler_valgrind_get_type())
#define GB_PROFILER_VALGRIND(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_PROFILER_VALGRIND, GbProfilerValgrind))
#define GB_PROFILER_VALGRIND_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_PROFILER_VALGRIND, GbProfilerValgrind const))
#define GB_PROFILER_VALGRIND_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_PROFILER_VALGRIND, GbProfilerValgrindClass))
#define GB_IS_PROFILER_VALGRIND(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_PROFILER_VALGRIND))
#define GB_IS_PROFILER_VALGRIND_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_PROFILER_VALGRIND))
#define GB_PROFILER_VALGRIND_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_PROFILER_VALGRIND, GbProfilerValgrindClass))

typedef struct _GbProfilerValgrind        GbProfilerValgrind;
typedef struct _GbProfilerValgrindClass   GbProfilerValgrindClass;
typedef struct _GbProfilerValgrindPrivate GbProfilerValgrindPrivate;

struct _GbProfilerValgrind
{
   GbProfiler parent;

   /*< private >*/
   GbProfilerValgrindPrivate *priv;
};

struct _GbProfilerValgrindClass
{
   GbProfilerClass parent_class;
};

GType gb_profiler_valgrind_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* GB_PROFILER_VALGRIND_H */
