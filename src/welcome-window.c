/*  dvdisaster: Additional error correction for optical media.
 *  Copyright (C) 2004-2017 Carsten Gnoerlich.
 *  Copyright (C) 2019-2021 The dvdisaster development team.
 *
 *  Email: support@dvdisaster.org
 *
 *  This file is part of dvdisaster.
 *
 *  dvdisaster is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  dvdisaster is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dvdisaster. If not, see <http://www.gnu.org/licenses/>.
 */

/*** src type: only GUI code ***/

#ifdef WITH_GUI_YES
#include "dvdisaster.h"

/***
 *** Creates the welcome window shown after startup.
 ***/

/*
 * The welcome window is shown first,
 * so it is convenient to initialize our GC when it is exposed.
 */

static void toggle_cb(GtkWidget *widget, gpointer data)
{  int state  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));

   Closure->welcomeMessage = state;
}

/*
 * Create the window
 */

void GuiCreateWelcomePage(GtkNotebook *notebook)
{  GtkWidget *box,*button,*align,*ignore;
   int show_msg;

   show_msg = Closure->welcomeMessage || Closure->version != Closure->dotFileVersion;

   align = gtk_alignment_new(0.5, 0.5, 0.0, 0.0);
   ignore = gtk_label_new("welcome_tab");
   box = show_msg ? gtk_vbox_new(FALSE, 0) : gtk_hbox_new(FALSE, 10);

   gtk_notebook_append_page(notebook, align, ignore);

   gtk_container_add(GTK_CONTAINER(align), box);

   if(!show_msg)
     {  return;  // simply leave the window blank 
#if 0            // would print a centered dvdisaster logo
      GtkWidget *widget;  

      widget  = gtk_image_new_from_stock("dvdisaster-create", GTK_ICON_SIZE_LARGE_TOOLBAR);
      gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);

      GuiAboutText(box, "<span weight=\"bold\" size=\"xx-large\">dvdisaster</span>");
      return;
#endif
   }

   GuiAboutText(box, _("<span weight=\"bold\" size=\"xx-large\">Welcome to dvdisaster!</span>"));

   GuiAboutText(box, _("\ndvdisaster creates error correction data to protect\n"
		       "optical media (CD,DVD,BD) against data loss.\n"));

   GuiAboutTextWithLink(box, _("Please see the [manual] for typical uses of dvdisaster.\n\n"), 
		     "manual.pdf");

   GuiAboutText(box, _("<i>New in this Version:</i>"));

   GuiAboutTextWithLink(box, _("This is <b>v0.79.10-pl3</b>. The [patchlevel series] are enhanced from the last upstream release.\n"
      "We add support for BD-R TL/QL, Windows and MacOS builds, an option to produce bigger BD-R RS03,\n"
      "images, support for stripping ECC from ISOs, re-enabled adaptive reading (except for RS03), and more.\n"
      "\n"
      "Please refer to the <i>Help &gt; Change log</i> menu for all the details."), "https://github.com/speed47/dvdisaster");

   gtk_box_pack_start(GTK_BOX(box), gtk_hseparator_new(), FALSE, FALSE, 10);

   button = gtk_check_button_new_with_label(_utf("Show this message again"));
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), Closure->welcomeMessage);
   g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(toggle_cb), NULL);
   gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

   gtk_widget_show_all(box);

   Closure->dotFileVersion = Closure->version;
}
#endif /* WITH_GUI_YES */
