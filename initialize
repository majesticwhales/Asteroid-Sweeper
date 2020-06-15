#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "headers.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP *background;

extern Images tile[13];

bool allegroStart(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background){
	
	//makes display window
    display = al_create_display(832, 832);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return false;
	}
	
	//image addons
	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error",
    		"Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}
	
	//installs mouse
	if (!al_install_mouse()){
        al_show_native_message_box(display, "Error", "Error",
    		"Failed to initialize mouse!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}
	
	//creates event queue
	event_queue = al_create_event_queue();
   	if (!event_queue){
		al_show_native_message_box(display, "Error", "Error",
				   "Failed to initialize event queue!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		return false;
    }
    
	//gets event sources
    al_register_event_source(event_queue, al_get_mouse_event_source());

	//adds font
    if (!al_init_font_addon()){
        al_show_native_message_box(display, "Error", "Error", "Could not load font",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }
	//adds ttf so the font files will work
    if (!al_init_ttf_addon()){
        al_show_native_message_box(display, "Error", "Error", "Could not load ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

	return true;
}

bool imageIndex(ALLEGRO_BITMAP *background){
	
	//loads the background
    background = al_load_bitmap("images/spacebackground.jpg");

    if (!background){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return false;
    }
	//draws the bitmap of the background
    al_draw_bitmap(background, 0, 0, 0);

	//array of strings to hold the image files
    char imageFile[14][30] = {
        "images/tile0.png",
        "images/tile1.png",
        "images/tile2.png",
        "images/tile3.png",
        "images/tile4.png",
        "images/tile5.png",
        "images/tile6.png",
        "images/tile7.png",
        "images/tile8.png",
        "images/blanktile.png",
        "images/flaggedmine.png",
        "images/revealedast.png",
        "images/destroyedast.png",
        "images/wrongflag.png"};

	//puts the images into the structure for holding images
    for (int i = 0; i < 14; i++){

        tile[i].bitmap = al_load_bitmap(imageFile[i]);

        if (!tile[i].bitmap){
            al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return false;
        }
    }
    return true;
}
