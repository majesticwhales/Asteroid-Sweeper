#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "headers.h"

//globals
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_BITMAP *background = nullptr;

//struct to hold images
Images tile[13];

int main (int argc, char *argv[]){

    //used to randomize location of asteroids
    srand(time(0));
    
    //initialize allegro
    al_init();

    //allows players to play again
    bool restart = true;

    if (!allegroStart(display, background)){
        printf("Error, failed to initialize Allegro addons!");
        return 1;
    }
	//loads fonts
    ALLEGRO_FONT *titleFont = al_load_ttf_font("SF_Cartoonist_Hand.ttf", 48, 0);
    ALLEGRO_FONT *font = al_load_ttf_font("SF_Cartoonist_Hand.ttf", 36, 0);
	
	//plays introduction
    intro(background, font);

	
    while (restart){
    	//loads images
        if (!imageIndex(background)){
            printf("Error, failed to load images!");
            return 1;
        }
	
		//declares variables
        int astField[18][18] = {0};
        int numAst = 0;
        int astRemain = 40;
        int numGood = 0;

		//all of the setup functions
        randomizeAst(numAst, astField);
        generateField(astField);
        displayField(astField, tile);
        displayText(titleFont, font);
        al_flip_display();
	
		//main play function
        mainPlay(font, numGood, astField, astRemain, background, restart);

    }

    al_destroy_display(display);

    return 0;

}
