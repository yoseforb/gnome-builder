/* gb-source-overlay.c
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

#include <glib/gi18n.h>
#include <string.h>

#include "gb-source-overlay.h"

G_DEFINE_TYPE(GbSourceOverlay, gb_source_overlay, GTK_TYPE_DRAWING_AREA)

struct _GbSourceOverlayPrivate
{
   GdkRGBA      background_color;
   gchar       *tag;
   GtkTextView *widget;
};

enum
{
   PROP_0,
   PROP_BACKGROUND_COLOR,
   PROP_TAG,
   PROP_WIDGET,
   LAST_PROP
};

static GParamSpec *gParamSpecs[LAST_PROP];

GtkWidget *
gb_source_overlay_new (void)
{
   return g_object_new(GB_TYPE_SOURCE_OVERLAY, NULL);
}

static void
subtract_region (cairo_region_t *region,
                 GtkTextView    *view,
                 GtkTextBuffer  *buffer,
                 GtkTextIter    *begin,
                 GtkTextIter    *end)
{
   cairo_rectangle_int_t r;
   GdkRectangle rect;
   GdkRectangle rect2;

   gtk_text_view_get_iter_location(view, begin, &rect);
   gtk_text_view_get_iter_location(view, end, &rect2);

   gtk_text_view_buffer_to_window_coords(view, GTK_TEXT_WINDOW_WIDGET, rect.x, rect.y, &rect.x, &rect.y);
   gtk_text_view_buffer_to_window_coords(view, GTK_TEXT_WINDOW_WIDGET, rect2.x, rect2.y, &rect2.x, &rect2.y);

   r.x = MIN(rect.x, rect2.x);
   r.y = MIN(rect.y, rect2.y);
   r.width = MAX(rect.x + rect.width, rect2.x) - r.x;
   r.height = MAX(rect.y + rect.height, rect2.y + rect2.height) - r.y;
   cairo_region_subtract_rectangle(region, &r);
}

static void
rounded_rectangle (cairo_t *cr,
                   gint     x,
                   gint     y,
                   gint     width,
                   gint     height,
                   gint     x_radius,
                   gint     y_radius)
{
   gint x1, x2;
   gint y1, y2;
   gint xr1, xr2;
   gint yr1, yr2;

   x1 = x;
   x2 = x1 + width;
   y1 = y;
   y2 = y1 + height;

   x_radius = MIN (x_radius, width / 2.0);
   y_radius = MIN (y_radius, width / 2.0);

   xr1 = x_radius;
   xr2 = x_radius / 2.0;
   yr1 = y_radius;
   yr2 = y_radius / 2.0;

   cairo_move_to (cr, x1 + xr1, y1);
   cairo_line_to (cr, x2 - xr1, y1);
   cairo_curve_to (cr, x2 - xr2, y1, x2, y1 + yr2, x2, y1 + yr1);
   cairo_line_to (cr, x2, y2 - yr1);
   cairo_curve_to (cr, x2, y2 - yr2, x2 - xr2, y2, x2 - xr1, y2);
   cairo_line_to (cr, x1 + xr1, y2);
   cairo_curve_to (cr, x1 + xr2, y2, x1, y2 - yr2, x1, y2 - yr1);
   cairo_line_to (cr, x1, y1 + yr1);
   cairo_curve_to (cr, x1, y1 + yr2, x1 + xr2, y1, x1 + xr1, y1);
   cairo_close_path (cr);
}

static void
draw_bevel (GbSourceOverlay *overlay,
            cairo_t         *cr,
            guint            rad,
            GtkTextIter     *begin,
            GtkTextIter     *end)
{
   cairo_rectangle_int_t r;
   GdkRectangle rect;
   GdkRectangle rect2;
   GtkTextView *view;

   view = GTK_TEXT_VIEW(overlay->priv->widget);

   gtk_text_view_get_iter_location(view, begin, &rect);
   gtk_text_view_get_iter_location(view, end, &rect2);

   gtk_text_view_buffer_to_window_coords(view, GTK_TEXT_WINDOW_WIDGET, rect.x, rect.y, &rect.x, &rect.y);
   gtk_text_view_buffer_to_window_coords(view, GTK_TEXT_WINDOW_WIDGET, rect2.x, rect2.y, &rect2.x, &rect2.y);

   r.x = MIN(rect.x, rect2.x);
   r.y = MIN(rect.y, rect2.y);
   r.width = MAX(rect.x + rect.width, rect2.x) - r.x;
   r.height = MAX(rect.y + rect.height, rect2.y + rect2.height) - r.y;

   r.x -= rad;
   r.y -= rad;
   r.width += rad * 2;
   r.height += rad * 2;

   rounded_rectangle(cr, r.x, r.y, r.width, r.height, rad, rad);
}

static void
get_visible_bounds (GtkTextView   *view,
                    GtkTextIter   *begin,
                    GtkTextIter   *end)
{
   GdkRectangle rect;

   gtk_text_view_get_visible_rect(view, &rect);
   gtk_text_view_get_iter_at_position(view, begin, NULL, rect.x, rect.y);
   gtk_text_view_get_iter_at_position(view, end, NULL, rect.x + rect.width, rect.y + rect.height);
}

static void
draw_bevels (GbSourceOverlay *overlay,
             cairo_t         *cr,
             GtkTextBuffer   *buffer,
             GtkTextTag      *tag)
{
   GtkTextIter begin;
   GtkTextIter end;
   GtkTextIter end_vis;
   GtkTextIter iter;
   GdkRGBA rgba;

   get_visible_bounds(GTK_TEXT_VIEW(overlay->priv->widget), &iter, &end_vis);

   /*
    * TODO: Make the highlight colors configurable.
    */

   gdk_rgba_parse(&rgba, "#edd400");
   gdk_cairo_set_source_rgba(cr, &rgba);

   do {
      if (gtk_text_iter_forward_to_tag_toggle(&iter, tag)) {
         if (!gtk_text_iter_begins_tag(&iter, tag)) {
            gtk_text_iter_backward_to_tag_toggle(&iter, tag);
         }
         gtk_text_iter_assign(&begin, &iter);
         gtk_text_iter_forward_to_tag_toggle(&iter, tag);
         gtk_text_iter_assign(&end, &iter);
         draw_bevel(overlay, cr, 2, &begin, &end);
      }
   } while (gtk_text_iter_forward_to_tag_toggle(&iter, tag) && gtk_text_iter_compare(&iter, &end_vis) < 0);

   cairo_fill(cr);

   get_visible_bounds(GTK_TEXT_VIEW(overlay->priv->widget), &iter, &end_vis);

   gdk_rgba_parse(&rgba, "#fce94f");
   gdk_cairo_set_source_rgba(cr, &rgba);

   do {
      if (gtk_text_iter_forward_to_tag_toggle(&iter, tag)) {
         if (!gtk_text_iter_begins_tag(&iter, tag)) {
            gtk_text_iter_backward_to_tag_toggle(&iter, tag);
         }
         gtk_text_iter_assign(&begin, &iter);
         gtk_text_iter_forward_to_tag_toggle(&iter, tag);
         gtk_text_iter_assign(&end, &iter);
         draw_bevel(overlay, cr, 1, &begin, &end);
      }
   } while (gtk_text_iter_forward_to_tag_toggle(&iter, tag) && gtk_text_iter_compare(&iter, &end_vis) < 0);

   cairo_fill(cr);
}

static gboolean
gb_source_overlay_draw (GtkWidget *widget,
                        cairo_t   *cr)
{
   GbSourceOverlayPrivate *priv;
   cairo_rectangle_int_t rect;
   GbSourceOverlay *overlay = (GbSourceOverlay *)widget;
   GtkTextTagTable *table;
   cairo_region_t *region;
   GtkAllocation alloc;
   GtkTextBuffer *buffer;
   GtkTextIter iter;
   GtkTextIter begin;
   GtkTextIter end;
   GtkTextTag *tag;
   GdkWindow *window;
   gint n_rectangles;
   gint i;

   g_assert(GB_IS_SOURCE_OVERLAY(overlay));
   g_assert(cr);

   priv = overlay->priv;

   if (!GTK_IS_TEXT_VIEW(priv->widget) || !priv->tag) {
      return FALSE;
   }

   if (!(buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(priv->widget)))) {
      return FALSE;
   }

   window = gtk_widget_get_window(widget);
   if (!gtk_cairo_should_draw_window(cr, window)) {
      return FALSE;
   }

   if (!(table = gtk_text_buffer_get_tag_table(buffer))) {
      return FALSE;
   }

   if (!(tag = gtk_text_tag_table_lookup(table, priv->tag))) {
      return FALSE;
   }

   gtk_widget_get_allocation(widget, &alloc);
   rect.x = alloc.x;
   rect.y = alloc.y;
   rect.width = alloc.width;
   rect.height = alloc.height;
   region = cairo_region_create_rectangle(&rect);

   gtk_text_buffer_get_bounds(buffer, &iter, &end);

   do {
      if (!gtk_text_iter_begins_tag(&iter, tag)) {
         if (!gtk_text_iter_forward_to_tag_toggle(&iter, tag)) {
            break;
         }
      }
      gtk_text_iter_assign(&begin, &iter);
      if (!gtk_text_iter_forward_to_tag_toggle(&iter, tag)) {
         break;
      }

      gtk_text_iter_assign(&end, &iter);
      subtract_region(region, GTK_TEXT_VIEW(priv->widget), buffer, &begin, &end);
   } while (gtk_text_iter_forward_char(&iter));

   cairo_save(cr);

   n_rectangles = cairo_region_num_rectangles(region);
   for (i = 0; i < n_rectangles; i++) {
      cairo_region_get_rectangle(region, i, &rect);
      cairo_rectangle(cr, rect.x, rect.y, rect.width, rect.height);
   }
   gdk_cairo_set_source_rgba(cr, &priv->background_color);
   cairo_fill_preserve(cr);
   cairo_clip(cr);

   draw_bevels(overlay, cr, buffer, tag);

   cairo_restore(cr);

   cairo_region_destroy(region);

   return FALSE;
}

static void
propagate_event (GtkWidget *widget,
                 GdkEvent  *event)
{
   GbSourceOverlay *overlay = (GbSourceOverlay *)widget;
   GtkWidget *parent;
   GtkWidget *child;

   child = GTK_WIDGET(overlay->priv->widget);
   if ((parent = gtk_widget_get_parent(child)) && GTK_IS_SCROLLED_WINDOW(parent)) {
      gtk_propagate_event(parent, event);
   } else {
      gtk_propagate_event(child, event);
   }
}

static gboolean
gb_source_overlay_button_press_event (GtkWidget      *widget,
                                      GdkEventButton *button)
{
   propagate_event(widget, (GdkEvent *)button);
   return FALSE;
}

static gboolean
gb_source_overlay_button_release_event (GtkWidget      *widget,
                                        GdkEventButton *button)
{
   propagate_event(widget, (GdkEvent *)button);
   gtk_widget_hide(widget);
   return FALSE;
}

static gboolean
gb_source_overlay_scroll_event (GtkWidget      *widget,
                                GdkEventScroll *scroll)
{
   propagate_event(widget, (GdkEvent *)scroll);
   return FALSE;
}

static gboolean
gb_source_overlay_touch_event (GtkWidget     *widget,
                               GdkEventTouch *touch)
{
   /*
    * TODO: This does not seem to be enough to propagate scrolls to the
    *       underlying scrolled window. Need to investigate.
    */
   propagate_event(widget, (GdkEvent *)touch);
   switch (touch->type) {
   case GDK_TOUCH_END:
   case GDK_TOUCH_CANCEL:
      gtk_widget_hide(widget);
      break;
   default:
      break;
   }
   return FALSE;
}

static void
gb_source_overlay_set_background_color (GbSourceOverlay *overlay,
                                        const GdkRGBA   *background_color)
{
   GbSourceOverlayPrivate *priv;

   g_return_if_fail(GB_IS_SOURCE_OVERLAY(overlay));

   priv = overlay->priv;

   memset(&priv->background_color, 0, sizeof priv->background_color);
   if (background_color) {
      memcpy(&priv->background_color, background_color,
             sizeof priv->background_color);
   }
}

static void
gb_source_overlay_finalize (GObject *object)
{
   GbSourceOverlayPrivate *priv;

   priv = GB_SOURCE_OVERLAY(object)->priv;

   g_clear_object(&priv->widget);
   g_clear_pointer(&priv->tag, g_free);

   G_OBJECT_CLASS(gb_source_overlay_parent_class)->finalize(object);
}

static void
gb_source_overlay_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
   GbSourceOverlay *overlay = GB_SOURCE_OVERLAY(object);

   switch (prop_id) {
   case PROP_BACKGROUND_COLOR:
      g_value_set_boxed(value, &overlay->priv->background_color);
      break;
   case PROP_WIDGET:
      g_value_set_object(value, overlay->priv->widget);
      break;
   case PROP_TAG:
      g_value_set_string(value, overlay->priv->tag);
      break;
   default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
   }
}

static void
gb_source_overlay_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
   GbSourceOverlay *overlay = GB_SOURCE_OVERLAY(object);

   switch (prop_id) {
   case PROP_BACKGROUND_COLOR:
      gb_source_overlay_set_background_color(overlay,
                                             g_value_get_boxed(value));
      break;
   case PROP_WIDGET:
      g_clear_object(&overlay->priv->widget);
      overlay->priv->widget = g_value_dup_object(value);
      break;
   case PROP_TAG:
      g_clear_pointer(&overlay->priv->tag, g_free);
      overlay->priv->tag = g_value_dup_string(value);
      break;
   default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
   }
}

static void
gb_source_overlay_class_init (GbSourceOverlayClass *klass)
{
   GtkWidgetClass *widget_class;
   GObjectClass *object_class;

   object_class = G_OBJECT_CLASS(klass);
   object_class->finalize = gb_source_overlay_finalize;
   object_class->get_property = gb_source_overlay_get_property;
   object_class->set_property = gb_source_overlay_set_property;
   g_type_class_add_private(object_class, sizeof(GbSourceOverlayPrivate));

   widget_class = GTK_WIDGET_CLASS(klass);
   widget_class->draw = gb_source_overlay_draw;
   widget_class->button_press_event = gb_source_overlay_button_press_event;
   widget_class->button_release_event = gb_source_overlay_button_release_event;
   widget_class->scroll_event = gb_source_overlay_scroll_event;
   widget_class->touch_event = gb_source_overlay_touch_event;

   gParamSpecs[PROP_BACKGROUND_COLOR] =
      g_param_spec_boxed("background-color",
                         _("Background Color"),
                         _("The color for the background."),
                         GDK_TYPE_RGBA,
                         G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
   g_object_class_install_property(object_class, PROP_BACKGROUND_COLOR,
                                   gParamSpecs[PROP_BACKGROUND_COLOR]);

   gParamSpecs[PROP_WIDGET] =
      g_param_spec_object("widget",
                          _("Widget"),
                          _("The GtkTextView widget."),
                          GTK_TYPE_WIDGET,
                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
   g_object_class_install_property(object_class, PROP_WIDGET,
                                   gParamSpecs[PROP_WIDGET]);

   gParamSpecs[PROP_TAG] =
      g_param_spec_string("tag",
                          _("Tag"),
                          _("The name of the search tag."),
                          NULL,
                          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS);
   g_object_class_install_property(object_class, PROP_TAG,
                                   gParamSpecs[PROP_TAG]);
}

static void
gb_source_overlay_init (GbSourceOverlay *overlay)
{
   overlay->priv =
      G_TYPE_INSTANCE_GET_PRIVATE(overlay,
                                  GB_TYPE_SOURCE_OVERLAY,
                                  GbSourceOverlayPrivate);

   gdk_rgba_parse(&overlay->priv->background_color, "#000000");
   overlay->priv->background_color.alpha = 0.8;

   gtk_widget_add_events(GTK_WIDGET(overlay),
                         (GDK_BUTTON_PRESS_MASK |
                          GDK_BUTTON_RELEASE_MASK |
                          GDK_SCROLL_MASK |
                          GDK_TOUCH_MASK));
}