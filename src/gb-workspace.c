/* gb-workspace.c
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

#include <gd/gd-header-bar.h>
#include <glib/gi18n.h>

#include "gb-workspace.h"
#include "gb-workspace-layout.h"
#include "gb-workspace-layout-edit.h"
#include "gb-workspace-layout-splash.h"
#include "gb-workspace-layout-switcher.h"
#include "gb-workspace-pane.h"

G_DEFINE_TYPE(GbWorkspace, gb_workspace, GTK_TYPE_APPLICATION_WINDOW)

struct _GbWorkspacePrivate
{
   GbProject *project;

   GtkWidget *edit;
   GtkWidget *layout;
   GtkWidget *notebook;
   GtkWidget *splash;
   GtkWidget *switcher;
   GtkWidget *toolbar;
   GtkWidget *vbox;
};

enum
{
   PROP_0,
   LAST_PROP
};

//static GParamSpec *gParamSpecs[LAST_PROP];

void
gb_workspace_set_project (GbWorkspace *workspace,
                          GbProject   *project)
{
   GbWorkspacePrivate *priv;
   GbWorkspaceLayoutClass *klass = NULL;

   g_return_if_fail(GB_IS_WORKSPACE(workspace));
   g_return_if_fail(!project || GB_IS_PROJECT(project));

   priv = workspace->priv;

   if (priv->layout) {
      klass = GB_WORKSPACE_LAYOUT_GET_CLASS(priv->layout);
   }

   if (priv->layout && priv->project && klass->unload) {
      klass->unload(GB_WORKSPACE_LAYOUT(priv->layout), priv->project);
   }

   g_clear_object(&priv->project);

   if (project) {
      priv->project = g_object_ref(project);
   }

   if (priv->layout && priv->project && klass->load) {
      klass->load(GB_WORKSPACE_LAYOUT(priv->layout), priv->project);
   }
}

#if 0
void
gb_workspace_set_layout (GbWorkspace       *workspace,
                         GbWorkspaceLayout *layout)
{
   GbWorkspaceLayoutClass *klass;
   GbWorkspacePrivate *priv;

   g_return_if_fail(GB_IS_WORKSPACE(workspace));
   g_return_if_fail(!layout || GB_IS_WORKSPACE_LAYOUT(layout));

   priv = workspace->priv;

   g_object_set(priv->toolbar, "visible", !!layout, NULL);

   if (!layout) {
      layout = g_object_new(GB_TYPE_WORKSPACE_LAYOUT_SPLASH,
                            "visible", TRUE,
                            NULL);
   }

   if (priv->layout && priv->project) {
      klass = GB_WORKSPACE_LAYOUT_GET_CLASS(priv->layout);
      if (klass->unload) {
         klass->unload(GB_WORKSPACE_LAYOUT(priv->layout), priv->project);
      }
   }

   if (priv->layout) {
      gtk_container_remove(GTK_CONTAINER(priv->vbox), priv->layout);
   }

   priv->layout = GTK_WIDGET(layout);

   gtk_container_add(GTK_CONTAINER(priv->vbox), priv->layout);

   if (priv->project) {
      klass = GB_WORKSPACE_LAYOUT_GET_CLASS(layout);
      if (klass->load) {
         klass->load(layout, priv->project);
      }
   }
}
#endif

void
gb_workspace_set_mode (GbWorkspace     *workspace,
                       GbWorkspaceMode  mode)
{
   GbWorkspacePrivate *priv;

   g_return_if_fail(GB_IS_WORKSPACE(workspace));

   priv = workspace->priv;

   gtk_notebook_set_current_page(GTK_NOTEBOOK(priv->notebook),
                                 (guint)mode);

   priv->layout = gtk_notebook_get_nth_page(GTK_NOTEBOOK(priv->notebook),
                                            (guint)mode);

   g_object_set(priv->toolbar,
                "visible", (mode != GB_WORKSPACE_SPLASH),
                NULL);
}

static void
gb_workspace_add (GtkContainer *container,
                  GtkWidget    *child)
{
   GbWorkspacePrivate *priv = GB_WORKSPACE(container)->priv;

   g_print("%s\n", g_type_name(G_TYPE_FROM_INSTANCE(child)));
   g_print("gb_workspace_add\n");

   if (GB_IS_WORKSPACE_PANE(child)) {
      g_print("it is a workspace pane\n");
      gtk_container_add(GTK_CONTAINER(priv->layout), child);
   } else {
      GTK_CONTAINER_CLASS(gb_workspace_parent_class)->add(container, child);
   }
}

static void
gb_workspace_finalize (GObject *object)
{
   G_OBJECT_CLASS(gb_workspace_parent_class)->finalize(object);
}

static void
gb_workspace_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
   //GbWorkspace *workspace = GB_WORKSPACE(object);

   switch (prop_id) {
   default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
   }
}

static void
gb_workspace_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
   //GbWorkspace *workspace = GB_WORKSPACE(object);

   switch (prop_id) {
   default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
   }
}

static void
gb_workspace_class_init (GbWorkspaceClass *klass)
{
   GObjectClass *object_class;
   GtkContainerClass *container_class;

   object_class = G_OBJECT_CLASS(klass);
   object_class->finalize = gb_workspace_finalize;
   object_class->get_property = gb_workspace_get_property;
   object_class->set_property = gb_workspace_set_property;
   g_type_class_add_private(object_class, sizeof(GbWorkspacePrivate));

   container_class = GTK_CONTAINER_CLASS(klass);
   container_class->add = gb_workspace_add;
}

static void
gb_workspace_init (GbWorkspace *workspace)
{
   GbWorkspacePrivate *priv;
   GtkWidget *image;
   GtkWidget *button;

   workspace->priv = G_TYPE_INSTANCE_GET_PRIVATE(workspace,
                                                 GB_TYPE_WORKSPACE,
                                                 GbWorkspacePrivate);

   priv = workspace->priv;

   g_object_set(workspace,
                "hide-titlebar-when-maximized", TRUE,
                NULL);

   priv->vbox =
      g_object_new(GTK_TYPE_BOX,
                   "orientation", GTK_ORIENTATION_VERTICAL,
                   "vexpand", TRUE,
                   "visible", TRUE,
                   NULL);
   gtk_container_add(GTK_CONTAINER(workspace), priv->vbox);

   priv->switcher =
      g_object_new(GB_TYPE_WORKSPACE_LAYOUT_SWITCHER,
                   "visible", TRUE,
                   NULL);

   priv->toolbar =
      g_object_new(GD_TYPE_HEADER_BAR,
                   "custom-title", workspace->priv->switcher,
                   "name", "GbHeaderBar",
                   "height-request", 48,
                   "vexpand", FALSE,
                   "visible", TRUE,
                   NULL);
   gtk_style_context_add_class(gtk_widget_get_style_context(priv->toolbar),
                               "builder-header");
   gtk_container_add(GTK_CONTAINER(priv->vbox), priv->toolbar);

   image = g_object_new(GTK_TYPE_IMAGE,
                        "icon-name", "edit-find-symbolic",
                        "icon-size", GTK_ICON_SIZE_MENU,
                        "visible", TRUE,
                        NULL);
   button = g_object_new(GTK_TYPE_TOGGLE_BUTTON,
                         "image", image,
                         "hexpand", FALSE,
                         "visible", TRUE,
                         NULL);
   gd_header_bar_pack_end(GD_HEADER_BAR(priv->toolbar), button);

   image = g_object_new(GTK_TYPE_IMAGE,
                        "icon-name", "emblem-system-symbolic",
                        "icon-size", GTK_ICON_SIZE_MENU,
                        "visible", TRUE,
                        NULL);
   button = g_object_new(GTK_TYPE_MENU_BUTTON,
                         "image", image,
                         "hexpand", FALSE,
                         "visible", TRUE,
                         NULL);
   gd_header_bar_pack_end(GD_HEADER_BAR(priv->toolbar), button);

   button = g_object_new(GTK_TYPE_BUTTON,
                         "label", _("Build"),
                         "hexpand", FALSE,
                         "visible", TRUE,
                         "width-request", 75,
                         NULL);
   gtk_style_context_add_class(gtk_widget_get_style_context(button),
                               "suggested-action");
   gd_header_bar_pack_start(GD_HEADER_BAR(priv->toolbar), button);

   priv->notebook =
      g_object_new(GTK_TYPE_NOTEBOOK,
                   "hexpand", TRUE,
                   "show-tabs", FALSE,
                   "show-border", FALSE,
                   "vexpand", TRUE,
                   "visible", TRUE,
                   NULL);
   gtk_container_add(GTK_CONTAINER(priv->vbox), priv->notebook);

   priv->splash = g_object_new(GB_TYPE_WORKSPACE_LAYOUT_SPLASH,
                               "visible", TRUE,
                               NULL);
   gtk_container_add(GTK_CONTAINER(priv->notebook), priv->splash);

   priv->edit = g_object_new(GB_TYPE_WORKSPACE_LAYOUT_EDIT,
                             "visible", TRUE,
                             NULL);
   gtk_container_add(GTK_CONTAINER(priv->notebook), priv->edit);

   gb_workspace_set_mode(workspace, GB_WORKSPACE_SPLASH);
}