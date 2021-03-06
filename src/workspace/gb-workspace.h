/* gb-workspace.h
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

#ifndef GB_WORKSPACE_H
#define GB_WORKSPACE_H

#include <gtk/gtk.h>

#include "gb-project.h"
#include "gb-workspace-layout.h"

G_BEGIN_DECLS

#define GB_TYPE_WORKSPACE            (gb_workspace_get_type())
#define GB_WORKSPACE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_WORKSPACE, GbWorkspace))
#define GB_WORKSPACE_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_WORKSPACE, GbWorkspace const))
#define GB_WORKSPACE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_WORKSPACE, GbWorkspaceClass))
#define GB_IS_WORKSPACE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_WORKSPACE))
#define GB_IS_WORKSPACE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_WORKSPACE))
#define GB_WORKSPACE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_WORKSPACE, GbWorkspaceClass))

typedef struct _GbWorkspace        GbWorkspace;
typedef struct _GbWorkspaceClass   GbWorkspaceClass;
typedef enum   _GbWorkspaceMode    GbWorkspaceMode;
typedef struct _GbWorkspacePrivate GbWorkspacePrivate;

enum _GbWorkspaceMode
{
   GB_WORKSPACE_SPLASH,
   GB_WORKSPACE_EDIT,
   GB_WORKSPACE_UI,
   GB_WORKSPACE_DEBUG,
   GB_WORKSPACE_GIT,
   GB_WORKSPACE_DOCS,
};

struct _GbWorkspace
{
   GtkApplicationWindow parent;

   /*< private >*/
   GbWorkspacePrivate *priv;
};

struct _GbWorkspaceClass
{
   GtkApplicationWindowClass parent_class;
};

GbProject *gb_workspace_get_project    (GbWorkspace     *workspace);
GType      gb_workspace_get_type       (void) G_GNUC_CONST;
gboolean   gb_workspace_is_fullscreen  (GbWorkspace     *workspace);
void       gb_workspace_set_mode       (GbWorkspace     *workspace,
                                        GbWorkspaceMode  mode);
void       gb_workspace_set_project    (GbWorkspace     *workspace,
                                        GbProject       *project);
void       gb_workspace_update_actions (GbWorkspace     *workspace);

G_END_DECLS

#endif /* GB_WORKSPACE_H */
