/* AGS - Advanced GTK Sequencer
 * Copyright (C) 2015 Joël Krähemann
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <ags/X/import/ags_track_collection.h>
#include <ags/X/import/ags_track_collection_callbacks.h>

#include <ags/object/ags_connectable.h>
#include <ags/object/ags_applicable.h>

void ags_track_collection_class_init(AgsTrackCollectionClass *track_collection);
void ags_track_collection_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_track_collection_applicable_interface_init(AgsApplicableInterface *applicable);
void ags_track_collection_init(AgsTrackCollection *track_collection);
void ags_track_collection_connect(AgsConnectable *connectable);
void ags_track_collection_disconnect(AgsConnectable *connectable);
void ags_track_collection_set_update(AgsApplicable *applicable, gboolean update);
void ags_track_collection_apply(AgsApplicable *applicable);
void ags_track_collection_reset(AgsApplicable *applicable);
void ags_track_collection_show(GtkWidget *widget);

/**
 * SECTION:ags_track_collection
 * @short_description: Property of audio, channels or pads in bulk mode.
 * @title: AgsTrackCollection
 * @section_id:
 * @include: ags/X/ags_track_collection.h
 *
 * #AgsTrackCollection is a composite widget to property. A property editor 
 * should be packed by a #AgsPropertyCollectionEditor.
 */

GType
ags_track_collection_get_type(void)
{
  static GType ags_type_track_collection = 0;

  if(!ags_type_track_collection){
    static const GTypeInfo ags_track_collection_info = {
      sizeof (AgsTrackCollectionClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_track_collection_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsTrackCollection),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_track_collection_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_track_collection_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_applicable_interface_info = {
      (GInterfaceInitFunc) ags_track_collection_applicable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_track_collection = g_type_register_static(GTK_TYPE_VBOX,
						      "AgsTrackCollection\0", &ags_track_collection_info,
						      0);
    
    g_type_add_interface_static(ags_type_track_collection,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_track_collection,
				AGS_TYPE_APPLICABLE,
				&ags_applicable_interface_info);
  }

  return(ags_type_track_collection);
}

void
ags_track_collection_class_init(AgsTrackCollectionClass *track_collection)
{
}

void
ags_track_collection_connectable_interface_init(AgsConnectableInterface *connectable)
{
  connectable->is_ready = NULL;
  connectable->is_connected = NULL;
  connectable->connect = ags_track_collection_connect;
  connectable->disconnect = ags_track_collection_disconnect;
}

void
ags_track_collection_applicable_interface_init(AgsApplicableInterface *applicable)
{
  applicable->set_update = ags_track_collection_set_update;
  applicable->apply = ags_track_collection_apply;
  applicable->reset = ags_track_collection_reset;
}

void
ags_track_collection_init(AgsTrackCollection *track_collection)
{
  track_collection->flags = 0;

  track_collection->enabled = (GtkCheckButton *) gtk_check_button_new_with_label("enabled\0");
  gtk_box_pack_start(GTK_BOX(track_collection),
		     GTK_WIDGET(track_collection->enabled),
		     FALSE, FALSE,
		     0);
}

void
ags_track_collection_connect(AgsConnectable *connectable)
{
  AgsTrackCollection *track_collection;
  GList *pad_list;

  /* AgsTrackCollection */
  track_collection = AGS_TRACK_COLLECTION(connectable);

  g_signal_connect_after(G_OBJECT(track_collection->enabled), "toggled\0",
			 G_CALLBACK(ags_track_collection_enable_callback), track_collection);
}

void
ags_track_collection_disconnect(AgsConnectable *connectable)
{
  /* empty */
}

void
ags_track_collection_set_update(AgsApplicable *applicable, gboolean update)
{
  AgsTrackCollection *track_collection;

  track_collection = AGS_TRACK_COLLECTION(applicable);
}

void
ags_track_collection_apply(AgsApplicable *applicable)
{
  AgsTrackCollection *track_collection;

  track_collection = AGS_TRACK_COLLECTION(applicable);
}

void
ags_track_collection_reset(AgsApplicable *applicable)
{
  AgsTrackCollection *track_collection;

  track_collection = AGS_TRACK_COLLECTION(applicable);
}

void
ags_track_collection_show(GtkWidget *widget)
{
  AgsTrackCollection *track_collection = (AgsTrackCollection *) widget;
}

/**
 * ags_track_collection_new:
 * @child_type: 
 * @child_parameter_count:
 * @child_parameter:
 *
 * Creates an #AgsTrackCollection
 *
 * Returns: a new #AgsTrackCollection
 *
 * Since: 0.4.3
 */
AgsTrackCollection*
ags_track_collection_new(GType child_type,
			 guint child_parameter_count,
			 GParameter *child_parameter)
{
  AgsTrackCollection *track_collection;

  track_collection = (AgsTrackCollection *) g_object_new(AGS_TYPE_TRACK_COLLECTION,
							 NULL);

  track_collection->child_type = child_type;
  track_collection->child_parameter_count = child_parameter_count;
  track_collection->child_parameter = child_parameter;
  
  return(track_collection);
}
