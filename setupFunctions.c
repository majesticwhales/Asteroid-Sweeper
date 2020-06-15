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

//plays intro
void intro(ALLEGRO_BITMAP *background, ALLEGRO_FONT *font){
    
    //load and display background
    background = al_load_bitmap("images/spacebackground.jpg");

    if (!background){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
    }

    al_draw_bitmap(background, 0, 0, 0);
    
    //draw all of the text to the intro
    al_draw_text(font, text_colour, 30, 10, 0, "Welcome to Asteroid Sweeper!");
    al_draw_text(font, text_colour, 30, 100, 0, "You are stuck in an asteroid field. Your goal is to determine where");
    al_draw_text(font, text_colour, 30, 160, 0, "the asteroids in the field are located. You are given clues, however,");
    al_draw_text(font, text_colour, 30, 220, 0, "as whenever you discover an area without an asteroid, you are told");
    al_draw_text(font, text_colour, 30, 280, 0, "how many asteroids surround that location. You must use those clues");
    al_draw_text(font, text_colour, 30, 340, 0, "to your advantage. Good luck.");
    al_draw_text(font, text_colour, 30, 500, 0, "Controls:");
    al_draw_text(font, text_colour, 30, 550, 0, "Left Click to reveal a tile");
    al_draw_text(font, text_colour, 30, 600, 0, "Right Click to flag a potential asteroid");
    al_draw_text(font, text_colour, 30, 700, 0, "Your quest will begin shortly.");

    al_flip_display();
    
    //wait a little bit so that the user can read the text
    al_rest(15.0);

}

//randomly generates asteroids in a 16x16 field
void randomizeAst(int &numAst, int astField[18][18]){

    int random = 0;
    
    //runs a loop to keep generating asteroids until there are 40 asteroids
    while (numAst < 40){
        for (int i = 1; i < 17; i++){
            for (int j = 1; j < 17; j++){
                random = rand() % 100;
                if (astField[i][j] == 0 && numAst < 40 && random == 0){
                    //if astField[i][j] is equal to -1, there will be an asteroid there
                    astField[i][j] = -1;
                    numAst++;

                }
            }
        }
    }
}

//function to generate the numbers of tiles that aren't asteroids
void generateField(int astField[18][18]){
    
    //loops for each tile of the board
    for (int i = 1; i < 17; i++){
        for (int j = 1; j < 17; j++){
            
            if (astField[i][j] != -1){
                //loops to check each tile around the tile given in the first two loops
                for (int k = -1; k < 2; k++){
                    for (int m = -1; m < 2; m++){
                        //if a tile surrounding the chosen tile is a mine, add 1 to the value of the tile
                        if (astField[i+k][j+m] == -1){
                            astField[i][j]++;
                        }
                    }
                }
            }
        }
    }
    //debugging so that the buffer tiles will not get revealed, 10 is an arbitrary value
    for (int i = 0; i < 18; i++){
        astField[0][i] = 10;
    }
    //debugging so that the buffer tiles will not get revealed
    for (int i = 0; i < 18; i++){
        astField[i][0] = 10;
    }
}

//displays a blank asteroid field, every tile is blank
void displayField(int astField[18][18], Images tile[14]){

    for (int i = 1; i < 17; i++){
        for (int j = 1; j < 17; j++){
               
            //this image corresponds to the blank tile
            al_draw_bitmap(tile[9].bitmap, 128 + 32 * j, 128 + 32 * i, 0);

        }
    }
}

//draws title text
void displayText(ALLEGRO_FONT *titleFont, ALLEGRO_FONT *font){

    al_draw_text(titleFont, text_colour, 280, 50, 0, "Asteroid Sweeper");
    al_draw_text(font, text_colour, 340, 100, 0, "by Max Odell");

}
