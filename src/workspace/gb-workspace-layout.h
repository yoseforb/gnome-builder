/* gb-workspace-layout.h
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

#ifndef GB_WORKSPACE_LAYOUT_H
#define GB_WORKSPACE_LAYOUT_H

#include <gtk/gtk.h>

#include "gb-project.h"

G_BEGIN_DECLS

#define GB_TYPE_WORKSPACE_LAYOUT            (gb_workspace_layout_get_type())
#define GB_WORKSPACE_LAYOUT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_WORKSPACE_LAYOUT, GbWorkspaceLayout))
#define GB_WORKSPACE_LAYOUT_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_WORKSPACE_LAYOUT, GbWorkspaceLayout const))
#define GB_WORKSPACE_LAYOUT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_WORKSPACE_LAYOUT, GbWorkspaceLayoutClass))
#define GB_IS_WORKSPACE_LAYOUT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_WORKSPACE_LAYOUT))
#define GB_IS_WORKSPACE_LAYOUT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_WORKSPACE_LAYOUT))
#define GB_WORKSPACE_LAYOUT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_WORKSPACE_LAYOUT, GbWorkspaceLayoutClass))

typedef struct _GbWorkspaceLayout        GbWorkspaceLayout;
typedef struct _GbWorkspaceLayoutClass   GbWorkspaceLayoutClass;
typedef struct _GbWorkspaceLayoutPrivate GbWorkspaceLayoutPrivate;

struct _GbWorkspaceLayout
{
   GtkGrid parent;

   /*< private >*/
   GbWorkspaceLayoutPrivate *priv;
};

struct _GbWorkspaceLayoutClass
{
   GtkGridClass parent_class;

   void (*load)   (GbWorkspaceLayout *layout,
                   GbProject         *project);
   void (*unload) (GbWorkspaceLayout *layout,
                   GbProject         *project);

   void (*fullscreen)   (GbWorkspaceLayout *layout);
   void (*unfullscreen) (GbWorkspaceLayout *layout);

   gpointer padding[32];
};

GType gb_workspace_layout_get_type     (void) G_GNUC_CONST;
void  gb_workspace_layout_fullscreen   (GbWorkspaceLayout *layout);
void  gb_workspace_layout_unfullscreen (GbWorkspaceLayout *layout);

G_END_DECLS

#endif /* GB_WORKSPACE_LAYOUT_H */
