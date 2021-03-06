/* gb-project-file.h
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

#ifndef GB_PROJECT_FILE_H
#define GB_PROJECT_FILE_H

#include "gb-project-item.h"

G_BEGIN_DECLS

#define GB_TYPE_PROJECT_FILE            (gb_project_file_get_type())
#define GB_PROJECT_FILE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_PROJECT_FILE, GbProjectFile))
#define GB_PROJECT_FILE_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_PROJECT_FILE, GbProjectFile const))
#define GB_PROJECT_FILE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_PROJECT_FILE, GbProjectFileClass))
#define GB_IS_PROJECT_FILE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_PROJECT_FILE))
#define GB_IS_PROJECT_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_PROJECT_FILE))
#define GB_PROJECT_FILE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_PROJECT_FILE, GbProjectFileClass))

typedef struct _GbProjectFile        GbProjectFile;
typedef struct _GbProjectFileClass   GbProjectFileClass;
typedef struct _GbProjectFilePrivate GbProjectFilePrivate;

struct _GbProjectFile
{
   GbProjectItem parent;

   /*< private >*/
   GbProjectFilePrivate *priv;
};

struct _GbProjectFileClass
{
   GbProjectItemClass parent_class;
};

GType gb_project_file_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* GB_PROJECT_FILE_H */
