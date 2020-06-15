#define text_colour al_map_rgb(0xff, 0xff, 0xff)
#define highscore_screen_colour al_map_rgb(25,25,112)

struct Images{

    ALLEGRO_BITMAP *bitmap;

};

bool allegroStart(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background);
bool imageIndex(ALLEGRO_BITMAP *background);
void randomizeAst(int &numAst, int astField[18][18]);
void generateField(int astField[18][18]);
void displayField(int astField[18][18], Images tile[14]);
void displayText(ALLEGRO_FONT *titleFont, ALLEGRO_FONT *font);
void mainPlay(ALLEGRO_FONT *font, int &numGood, int astField[18][18],int &astRemain, ALLEGRO_BITMAP *background, bool &restart);
int tileClick(int mouse_x, int mouse_y, int astField[18][18], bool clicked[18][18], bool flagged[18][18], int &numGood);
void flag(int mouse_x, int mouse_y, bool clicked[18][18], bool flagged[18][18], int &astRemain);
int clearReveal(int astField[18][18], int &xClick, int &yClick, bool clicked[18][18], int &numGood);
void lose(ALLEGRO_FONT *font, ALLEGRO_EVENT ev, int &mouse_x, int &mouse_y, bool &restart);
void win(ALLEGRO_FONT *font, ALLEGRO_EVENT ev, int &mouse_x, int &mouse_y, bool &restart, int &timeStart);
void intro(ALLEGRO_BITMAP *background, ALLEGRO_FONT *font);
void astReveal(int astField[18][18], bool clicked[18][18], bool flagged[18][18]);
