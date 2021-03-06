/* gb-file-filters.c
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

#include "gb-file-filters.h"

/**
 * gb_file_filter_c_new:
 *
 * Returns a new file filter for C/C++ source files.
 *
 * Returns: (transfer full): A #GtkFileFilter.
 */
GtkFileFilter *
gb_file_filter_c_new (void)
{
   GtkFileFilter *filter;

   filter = gtk_file_filter_new();
   gtk_file_filter_set_name(filter, _("C/C++ Source"));
   gtk_file_filter_add_pattern(filter, "*.c");
   gtk_file_filter_add_pattern(filter, "*.cc");
   gtk_file_filter_add_pattern(filter, "*.cpp");
   return filter;
}

/**
 * gb_file_filter_header_new:
 *
 * Returns a new file filter for C/C++ header files.
 *
 * Returns: (transfer full): A #GtkFileFilter.
 */
GtkFileFilter *
gb_file_filter_header_new (void)
{
   GtkFileFilter *filter;

   filter = gtk_file_filter_new();
   gtk_file_filter_set_name(filter, _("C/C++ Header"));
   gtk_file_filter_add_pattern(filter, "*.h");
   gtk_file_filter_add_pattern(filter, "*.hh");
   gtk_file_filter_add_pattern(filter, "*.hpp");
   return filter;
}

/**
 * gb_file_filter_js_new:
 *
 * Returns a new file filter for javascript files.
 *
 * Returns: (transfer full): A #GtkFileFilter.
 */
GtkFileFilter *
gb_file_filter_js_new (void)
{
   GtkFileFilter *filter;

   filter = gtk_file_filter_new();
   gtk_file_filter_set_name(filter, _("JavaScript"));
   gtk_file_filter_add_pattern(filter, "*.js");
   return filter;
}

/**
 * gb_file_filter_text_new:
 *
 * Returns a new file filter for text files.
 *
 * Returns: (transfer full): A #GtkFileFilter.
 */
GtkFileFilter *
gb_file_filter_text_new (void)
{
   GtkFileFilter *filter;

   filter = gtk_file_filter_new();
   gtk_file_filter_set_name(filter, _("Text Files"));
   gtk_file_filter_add_mime_type(filter, "text/*");
   return filter;
}
