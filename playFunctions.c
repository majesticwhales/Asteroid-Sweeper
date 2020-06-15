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

//main playing function
void mainPlay(ALLEGRO_FONT *font, int &numGood, int astField[18][18],int &astRemain, ALLEGRO_BITMAP *background, bool &restart){
	
	//declares necessary variables to the function
    bool done = false;
    bool clicked[18][18] = {false};
    bool flagged[18][18] = {false};
    static char printRemaining[40];
    
	//loads background so it can be displayed over the intro text
    background = al_load_bitmap("images/spacebackground.jpg");

	//uses clock function to take the time started, will be used once game is won
    int timeStart = clock();

	//will only be done if asteroid is clicked or if all good tiles cleared
    while(!done){
	
	//sets allegro event
        ALLEGRO_EVENT ev;
	
	//variables for coordinates of mouse
        int mouse_x;
        int mouse_y;
	
	//draws text to print number of asteroids left in the field every time an event happens
        al_draw_bitmap(background, 550, -1020, 0);
	sprintf(printRemaining, "Asteroids Remaining: %d", astRemain);
        al_draw_text(font, text_colour, 550, 20, ALLEGRO_ALIGN_LEFT, printRemaining);
        al_flip_display();
	
	//waits for events
        al_wait_for_event(event_queue, &ev);
		
		//to track mouse coordinates
		if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;
			
		//if mouse is left-clicked
            if (ev.mouse.button & 1){
	    	//if tile clicked is an asteroid
                if (tileClick(mouse_x, mouse_y, astField, clicked, flagged, numGood) == -1){
			//finishes game and runs all of the game ending functions necessary
                    done = true;
                    astReveal(astField, clicked, flagged);
                    //wrongflags(astField, clicked, flagged);
                    lose(font, ev, mouse_x, mouse_y, restart);
                }
		//if all of the safe tiles are clicked
                if (numGood == 216){
			//ends game and runs all of the game ending functions
                    done = true;
                    win(font, ev, mouse_x, mouse_y, restart, timeStart);
                    astReveal(astField, clicked, flagged);
                }
            }
		//if mouse is right clicked
            if (ev.mouse.button & 2){
	    	//runs flag function
                flag(mouse_x, mouse_y, clicked, flagged, astRemain);

            }
		}
    }
}

//when a tile is left clicked
int tileClick(int mouse_x, int mouse_y, int astField[18][18], bool clicked[18][18], bool flagged[18][18], int &numGood){
	
	//decares variables to find which tile was clicked
    int xClick = 0;
    int yClick = 0;
	
	//these two for loops find which tile was clicked
    for (int i = 1; i < 17; i++){
        if (mouse_x > 128 + 32 * i && mouse_x < 160 + 32 * i){
            xClick = i;
        }
    }
    for (int i = 1; i < 17; i++){
        if (mouse_y > 128 + 32 * i && mouse_y < 160 + 32 * i){
            yClick = i;
        }
    }
	//if the tile selected hasn't been clicked already or flagged
    if (clicked[xClick][yClick] == false && flagged[xClick][yClick] == false){
    
	//displays the tile that was clicked
        switch (astField[xClick][yClick]){
            case -1: al_draw_bitmap(tile[12].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 0: al_draw_bitmap(tile[0].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 1: al_draw_bitmap(tile[1].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 2: al_draw_bitmap(tile[2].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 3: al_draw_bitmap(tile[3].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 4: al_draw_bitmap(tile[4].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 5: al_draw_bitmap(tile[5].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 6: al_draw_bitmap(tile[6].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 7: al_draw_bitmap(tile[7].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            case 8: al_draw_bitmap(tile[8].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
                break;
            default:
                break;
        }
	//if the tile clicked was not an asteroid
        if (astField[xClick][yClick] > -1 && astField[xClick][yClick] < 9){
            numGood++;
        }
	
	//the tile selected becomes clicked
        clicked[xClick][yClick] = true;
	
	//if the tile selected has no mines near it, it must clear everything around that tile
        if (astField[xClick][yClick] == 0){
            clearReveal(astField, xClick, yClick, clicked, numGood);
        }

        al_flip_display();
        return astField[xClick][yClick];
    }
    return 10;
}


//function to flag tiles
void flag(int mouse_x, int mouse_y, bool clicked[18][18], bool flagged[18][18], int &astRemain){
	
	//declares variable to find which tile was clicked
    int xClick = 0;
    int yClick = 0;

    for (int i = 1; i < 17; i++){
        if (mouse_x > 128 + 32 * i && mouse_x < 160 + 32 * i){
            xClick = i;
        }
    }
    for (int i = 1; i < 17; i++){
        if (mouse_y > 128 + 32 * i && mouse_y < 160 + 32 * i){
            yClick = i;
        }
    }

    if (clicked[xClick][yClick] == false){
        if (flagged[xClick][yClick] == true && xClick != 0 && yClick != 0){
            al_draw_bitmap(tile[9].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
            flagged[xClick][yClick] = false;
            astRemain++;
        }else if (flagged[xClick][yClick] == false && xClick != 0 && yClick != 0){
            al_draw_bitmap(tile[10].bitmap, 128 + 32 * xClick, 128 + 32 * yClick, 0);
            flagged[xClick][yClick] = true;
            astRemain--;
        }
    }

    al_flip_display();

}

int clearReveal(int astField[18][18], int &xClick, int &yClick, bool clicked[18][18], int &numGood){

    bool clearing = true;

    while(clearing){

        clearing = false;

        for (int xClick = 1; xClick < 17; xClick++){
            for (int yClick = 1; yClick < 17; yClick++){
                if (astField[xClick][yClick] == 0 && clicked[xClick][yClick] == true){
                    for (int k = -1; k < 2; k++){
                        for (int m = -1; m < 2; m++){

                            int newX = xClick + k;
                            int newY = yClick + m;

                            if (clicked[newX][newY] == false && newX > 0 && newX < 17 && newY > 0 && newY < 17){

                                switch (astField[newX][newY]){
                                    case -1: al_draw_bitmap(tile[12].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 0: al_draw_bitmap(tile[0].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 1: al_draw_bitmap(tile[1].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 2: al_draw_bitmap(tile[2].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 3: al_draw_bitmap(tile[3].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 4: al_draw_bitmap(tile[4].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 5: al_draw_bitmap(tile[5].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 6: al_draw_bitmap(tile[6].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 7: al_draw_bitmap(tile[7].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    case 8: al_draw_bitmap(tile[8].bitmap, 128 + 32 * newX, 128 + 32 * newY, 0);
                                        break;
                                    default:
                                        break;
                                }
                                al_flip_display();

                                if (astField[newX][newY] > -1 && astField[newX][newY] < 9){
                                    numGood++;
                                    clearing = true;
                                }

                                clicked[newX][newY] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
