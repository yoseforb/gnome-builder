/* gb-workspace-layout-splash.h
 *
 * Copyright (C) 2013 Christian Hergert <christian@hergert.me>
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GB_WORKSPACE_LAYOUT_SPLASH_H
#define GB_WORKSPACE_LAYOUT_SPLASH_H

#include "gb-workspace-layout.h"

G_BEGIN_DECLS

#define GB_TYPE_WORKSPACE_LAYOUT_SPLASH            (gb_workspace_layout_splash_get_type())
#define GB_WORKSPACE_LAYOUT_SPLASH(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_WORKSPACE_LAYOUT_SPLASH, GbWorkspaceLayoutSplash))
#define GB_WORKSPACE_LAYOUT_SPLASH_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_WORKSPACE_LAYOUT_SPLASH, GbWorkspaceLayoutSplash const))
#define GB_WORKSPACE_LAYOUT_SPLASH_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_WORKSPACE_LAYOUT_SPLASH, GbWorkspaceLayoutSplashClass))
#define GB_IS_WORKSPACE_LAYOUT_SPLASH(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_WORKSPACE_LAYOUT_SPLASH))
#define GB_IS_WORKSPACE_LAYOUT_SPLASH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_WORKSPACE_LAYOUT_SPLASH))
#define GB_WORKSPACE_LAYOUT_SPLASH_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_WORKSPACE_LAYOUT_SPLASH, GbWorkspaceLayoutSplashClass))

typedef struct _GbWorkspaceLayoutSplash        GbWorkspaceLayoutSplash;
typedef struct _GbWorkspaceLayoutSplashClass   GbWorkspaceLayoutSplashClass;
typedef struct _GbWorkspaceLayoutSplashPrivate GbWorkspaceLayoutSplashPrivate;

struct _GbWorkspaceLayoutSplash
{
   GbWorkspaceLayout parent;

   /*< private >*/
   GbWorkspaceLayoutSplashPrivate *priv;
};

struct _GbWorkspaceLayoutSplashClass
{
   GbWorkspaceLayoutClass parent_class;
};

GType gb_workspace_layout_splash_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* GB_WORKSPACE_LAYOUT_SPLASH_H */