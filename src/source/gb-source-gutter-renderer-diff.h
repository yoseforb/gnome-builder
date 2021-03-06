/* gb-source-gutter-renderer-diff.h
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

#ifndef GB_SOURCE_GUTTER_RENDERER_DIFF_H
#define GB_SOURCE_GUTTER_RENDERER_DIFF_H

#include <gtksourceview/gtksourcegutterrenderer.h>

#include "gb-source-diff.h"

G_BEGIN_DECLS

#define GB_TYPE_SOURCE_GUTTER_RENDERER_DIFF            (gb_source_gutter_renderer_diff_get_type())
#define GB_SOURCE_GUTTER_RENDERER_DIFF(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_SOURCE_GUTTER_RENDERER_DIFF, GbSourceGutterRendererDiff))
#define GB_SOURCE_GUTTER_RENDERER_DIFF_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_SOURCE_GUTTER_RENDERER_DIFF, GbSourceGutterRendererDiff const))
#define GB_SOURCE_GUTTER_RENDERER_DIFF_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_SOURCE_GUTTER_RENDERER_DIFF, GbSourceGutterRendererDiffClass))
#define GB_IS_SOURCE_GUTTER_RENDERER_DIFF(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_SOURCE_GUTTER_RENDERER_DIFF))
#define GB_IS_SOURCE_GUTTER_RENDERER_DIFF_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_SOURCE_GUTTER_RENDERER_DIFF))
#define GB_SOURCE_GUTTER_RENDERER_DIFF_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_SOURCE_GUTTER_RENDERER_DIFF, GbSourceGutterRendererDiffClass))

typedef struct _GbSourceGutterRendererDiff        GbSourceGutterRendererDiff;
typedef struct _GbSourceGutterRendererDiffClass   GbSourceGutterRendererDiffClass;
typedef struct _GbSourceGutterRendererDiffPrivate GbSourceGutterRendererDiffPrivate;

struct _GbSourceGutterRendererDiff
{
   GtkSourceGutterRenderer parent;

   /*< private >*/
   GbSourceGutterRendererDiffPrivate *priv;
};

struct _GbSourceGutterRendererDiffClass
{
   GtkSourceGutterRendererClass parent_class;
};

GType                    gb_source_gutter_renderer_diff_get_type (void) G_GNUC_CONST;
GtkSourceGutterRenderer *gb_source_gutter_renderer_diff_new      (GbSourceDiff *diff);

G_END_DECLS

#endif /* GB_SOURCE_GUTTER_RENDERER_DIFF_H */
