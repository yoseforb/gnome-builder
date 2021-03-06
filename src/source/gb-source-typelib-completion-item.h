/* gb-source-typelib-completion-item.h
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

#ifndef GB_SOURCE_TYPELIB_COMPLETION_ITEM_H
#define GB_SOURCE_TYPELIB_COMPLETION_ITEM_H

#include <gtksourceview/gtksourcecompletionproposal.h>

G_BEGIN_DECLS

#define GB_TYPE_SOURCE_TYPELIB_COMPLETION_ITEM            (gb_source_typelib_completion_item_get_type())
#define GB_SOURCE_TYPELIB_COMPLETION_ITEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_SOURCE_TYPELIB_COMPLETION_ITEM, GbSourceTypelibCompletionItem))
#define GB_SOURCE_TYPELIB_COMPLETION_ITEM_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_SOURCE_TYPELIB_COMPLETION_ITEM, GbSourceTypelibCompletionItem const))
#define GB_SOURCE_TYPELIB_COMPLETION_ITEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_SOURCE_TYPELIB_COMPLETION_ITEM, GbSourceTypelibCompletionItemClass))
#define GB_IS_SOURCE_TYPELIB_COMPLETION_ITEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_SOURCE_TYPELIB_COMPLETION_ITEM))
#define GB_IS_SOURCE_TYPELIB_COMPLETION_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_SOURCE_TYPELIB_COMPLETION_ITEM))
#define GB_SOURCE_TYPELIB_COMPLETION_ITEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_SOURCE_TYPELIB_COMPLETION_ITEM, GbSourceTypelibCompletionItemClass))

typedef struct _GbSourceTypelibCompletionItem        GbSourceTypelibCompletionItem;
typedef struct _GbSourceTypelibCompletionItemClass   GbSourceTypelibCompletionItemClass;
typedef struct _GbSourceTypelibCompletionItemPrivate GbSourceTypelibCompletionItemPrivate;

struct _GbSourceTypelibCompletionItem
{
   GObject parent;

   /*< private >*/
   GbSourceTypelibCompletionItemPrivate *priv;
};

struct _GbSourceTypelibCompletionItemClass
{
   GObjectClass parent_class;
};

GType gb_source_typelib_completion_item_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* GB_SOURCE_TYPELIB_COMPLETION_ITEM_H */
