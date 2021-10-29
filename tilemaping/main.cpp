#include <SDL_image.h>
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define WIDTH 320
#define HEIGHT 320
#define HTILE 12
#define WTILE 12
#define NBLIGNE 10
#define NBCOL 10
#define WTILESET 32

void genereNiveau(SDL_Texture* tileset, SDL_Renderer* rend, int table[][NBCOL], int largeurTile, int hauteurTile);

using namespace std;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "error initializing SDL: %s\n" << SDL_GetError();
    }

    SDL_Window* win;
    SDL_Renderer* rend;

    

    win = SDL_CreateWindow("GAME", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);

    // creation du renderer
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    ifstream myfile1("../map/mapDecor.txt");
    ifstream myfile2("../map/mapTerain.txt");
    if (!myfile1 || !myfile2)
    {
        cout << "Error opening output file" << endl;
    }

    

    SDL_Surface* image = IMG_Load("../assets/tileset.png");
    if (!image)
    {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    SDL_Texture* tileSet = SDL_CreateTextureFromSurface(rend, image);
    SDL_FreeSurface(image);

    int layer1[NBLIGNE][NBCOL];
    int layer2[NBLIGNE][NBCOL]; 
     

    for (int n_i = 0; n_i < NBLIGNE; n_i++)
    {
        for (int n_j = 0; n_j < NBCOL; n_j++)
        {
            myfile1 >> layer2[n_i][n_j];
            myfile2 >> layer1[n_i][n_j];
        }
    }

    myfile1.close();
    myfile2.close();

    int close = 0;


    while (!close)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
            }
        }

        SDL_RenderClear(rend);
       

        genereNiveau(tileSet, rend, layer1, WTILE, HTILE);
        genereNiveau(tileSet, rend, layer2, WTILE, HTILE);

        
        SDL_RenderPresent(rend);

        SDL_Delay(1000/60);
    }


    return 1;
}

void genereNiveau(SDL_Texture* tileset, SDL_Renderer* rend, int table [][NBCOL], int largeurTile, int hauteurTile)
{
    int l, c;
    SDL_Rect rectSource, rectDest;

    rectDest.w = 32;
    rectDest.h = 32;
    rectSource.w = 12;
    rectSource.h = 12;

    for (l = 0; l < NBLIGNE; l++)
    {
        for (c = 0; c < NBCOL; c++)
        {
            rectDest.x = c * 32;
            rectDest.y = l * 32;
            
            rectSource.x = (table[l][c] % WTILESET) * 12;
            rectSource.y = table[l][c] / WTILESET * 12;

            SDL_RenderCopy(rend, tileset, &rectSource, &rectDest);
        }
    }


}