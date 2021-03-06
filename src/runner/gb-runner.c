/* gb-runner.c
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

#include <glib/gi18n.h>

#include "gb-runner.h"

G_DEFINE_ABSTRACT_TYPE(GbRunner, gb_runner, G_TYPE_OBJECT)

struct _GbRunnerPrivate
{
   gpointer dummy;
};

enum
{
   PROP_0,
   LAST_PROP
};

//static GParamSpec *gParamSpecs[LAST_PROP];

static void
gb_runner_finalize (GObject *object)
{
   G_OBJECT_CLASS(gb_runner_parent_class)->finalize(object);
}

static void
gb_runner_get_property (GObject    *object,
                        guint       prop_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
   //GbRunner *runner = GB_RUNNER(object);

   switch (prop_id) {
   default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
   }
}

static void
gb_runner_set_property (GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
   //GbRunner *runner = GB_RUNNER(object);

   switch (prop_id) {
   default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
   }
}

static void
gb_runner_class_init (GbRunnerClass *klass)
{
   GObjectClass *object_class;

   object_class = G_OBJECT_CLASS(klass);
   object_class->finalize = gb_runner_finalize;
   object_class->get_property = gb_runner_get_property;
   object_class->set_property = gb_runner_set_property;
   g_type_class_add_private(object_class, sizeof(GbRunnerPrivate));
}

static void
gb_runner_init (GbRunner *runner)
{
   runner->priv = G_TYPE_INSTANCE_GET_PRIVATE(runner,
                                              GB_TYPE_RUNNER,
                                              GbRunnerPrivate);
}
