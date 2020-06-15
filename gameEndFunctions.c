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

//function for if the player loses
void lose(ALLEGRO_FONT *font, ALLEGRO_EVENT ev, int &mouse_x, int &mouse_y, bool &restart){
    
    //variable for if the user has made a decision on whether to play again or not
    bool decision = false;
    
    //draws text on screen
    al_draw_text(font, text_colour, 120, 700, 0, "You have destroyed an asteroid and lost! Play again?");
    al_draw_text(font, text_colour, 300, 770, 0, "Yes");
    al_draw_text(font, text_colour, 500, 770, 0, "No");
    
    //run loop until user has made a decision
    while (!decision){
        
        //wait for an event
        al_wait_for_event(event_queue, &ev);
        
        //tracking the x and y coordinates of the mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;
            
            //if the user left clicks
            if (ev.mouse.button & 1){
                
                //if the user wants to play again
                if (mouse_x > 300 && mouse_x < 350 && mouse_y > 770 && mouse_y < 800){
                    restart = true;
                    decision = true;
                }
                //if the user does not want to play again
                if (mouse_x > 500 && mouse_x < 550 && mouse_y > 770 && mouse_y < 800){
                    decision = true;
                    restart = false;
                }
            }
        }
        al_flip_display();
    }
}

//function for when the user wins
void win(ALLEGRO_FONT *font, ALLEGRO_EVENT ev, int &mouse_x, int &mouse_y, bool &restart, int &timeStart){
    
    al_rest(1.0);
    
    //structure to hold high scores
    struct Score{
        char name[10];
        float time = 0.0;
    };
    
    //create variable for structure and declare more highscore-related variables
    Score highscore[11];
    Score gameScore;
    int scoreRank = 0;
    bool highscoreGet = false;
    FILE *fptr;
    
    //get the ending time of the game
    int timeEnd = clock();
    
    //read highscores from file
    fptr = fopen("highscores.txt", "r");

    if (!fptr){
        printf("Error opening highscores.");
    }
    
    //scan info from file 
    for(int i = 0; i < 10; i++){
        fscanf(fptr, "%d", &scoreRank);
        fscanf(fptr, "%s", highscore[i].name);
        fscanf(fptr, "%f", &highscore[i].time);
    }
    
    //get the total time in seconds of the game
    gameScore.time = (float)(timeEnd - timeStart) / 1000;
    
    //loop to determine if the score is a highscore
    for(int i = 0; i < 10; i++){
        if(gameScore.time <= highscore[i].time){
            highscoreGet = true;
            //if the score is a highscore
            if (highscoreGet == true){
                //create highscore screen
                al_clear_to_color(highscore_screen_colour);

                al_draw_text(font, text_colour, 500, 50, 0, "HIGHSCORES");

                static char convertInt[10];
                static char convertFloat[10];
                static char convertTime[10];
                
                //draw the old leaderboard
                for(int j = 0; j < 10; j++){
                    sprintf(convertInt, "%d.", j+1);
                    sprintf(convertFloat, "%.3f", highscore[j].time);
                    al_draw_text(font, text_colour, 500, 30 * j + 100, 0, convertInt);
                    al_draw_text(font, text_colour, 540, 30 * j + 100, 0, highscore[j].name);
                    al_draw_text(font, text_colour, 620, 30 * j + 100, 0, convertFloat);
                }
                
                //show the user their time
                sprintf(convertTime, "Your time: %.3f", gameScore.time);
                al_draw_text(font, text_colour, 150, 300, 0, convertTime);
                al_draw_text(font, text_colour, 150, 100, 0, "You got a high score!");
                al_draw_text(font, text_colour, 75, 150, 0, "Enter your name in the other window.");
                al_draw_text(font, text_colour, 45, 700, 0, "Congratulations! You have cleared the asteroid field! Play again?");
                al_draw_text(font, text_colour, 300, 770, 0, "Yes");
                al_draw_text(font, text_colour, 500, 770, 0, "No");
                al_flip_display();
                
                //get the user to enter their name for highscores
                printf("Enter your name: ");
                scanf("%s", gameScore.name);

            }
            //loop to drop every time worse than the highscore down one place
            for(int j = 10; j > i; j--){
                strcpy(highscore[j].name, highscore[j - 1].name);
                highscore[j].time = highscore[j - 1].time;
            }
            
            //takes shortened form of user's name
            for(int j = 0; j < 3; j++){
                highscore[i].name[j] = gameScore.name[j];
            }
            
            //gets time of the highscore
            highscore[i].time = gameScore.time;
            break;
        }
    }
    
    //write the new info to the text file
    fptr = fopen("Highscores.txt", "w");

    if(!fptr)
        printf("\nFile not found");

    for(int i = 0; i < 10; i++){
        fprintf(fptr, "%d %s %.3f\n", i + 1, highscore[i].name, highscore[i].time);
    }
    
    //if the score is not a highscore
    if (highscoreGet == false){

        static char convertTime[10];
        
        //prints the time to the normal screen
        sprintf(convertTime, "%.3f", gameScore.time);
        al_draw_text(font, text_colour, 30, 300, 0, "Your time:");
        al_draw_text(font, text_colour, 30, 330, 0, convertTime);

    }
    
    //draws winning text
    al_draw_text(font, text_colour, 45, 700, 0, "Congratulations! You have cleared the asteroid field! Play again?");
    al_draw_text(font, text_colour, 300, 770, 0, "Yes");
    al_draw_text(font, text_colour, 500, 770, 0, "No");
    al_flip_display();

    fclose(fptr);


    //waits for the user to make a decision
    bool decision = false;

    while (!decision){
        //same code as the losing function
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;

            if (ev.mouse.button & 1){
                if (mouse_x > 300 && mouse_x < 350 && mouse_y > 770 && mouse_y < 800){
                    restart = true;
                    decision = true;
                }
                if (mouse_x > 500 && mouse_x < 550 && mouse_y > 770 && mouse_y < 800){
                    decision = true;
                    restart = false;
                }
            }
        }
        al_flip_display();
    }
}

//reveals all of the asteroids after game is over
void astReveal(int astField[18][18], bool clicked[18][18], bool flagged[18][18]){

    for (int i = 1; i < 17; i++){
        for (int j = 1; j < 17; j++){

            if (astField[i][j] == -1 && !clicked[i][j] && !flagged[i][j]){
                al_draw_bitmap(tile[11].bitmap, 128 + 32 * i, 128 + 32 * j, 0);
            }
        }
    }
    al_flip_display();
}
