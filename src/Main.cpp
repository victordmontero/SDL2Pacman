#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* pacTex;
SDL_Texture* blockTex;
SDL_Texture* ghotsTex;
SDL_Texture* fruitTex;
SDL_Event event;
SDL_RendererFlip pacFlip;
/*SDL_RendererFlip ghostFlip;
SDL_RendererFlip blueghostFlip;*/
SDL_RendererFlip ghostsFlips[4];

const int WIDTH = 480;
const int HEIGHT = 320;

const int MAXROWS = 20;
const int MAXCOLS = 31;

const int FPS = 8;

char map[MAXROWS][MAXCOLS] = {
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "XfffF|fFffffXXXXXXfffFFf|FfffX",
    "XfXXXfXXXXXfXXXXXXfXXXXXfXXXfX",
    "XfXXXfXXXXXfXXXXXXfXXXXXfXXXfX",
    "Xffff|ff|ffffffffffff|ff|ffffX",
    "XfXXXfXXfXXXXXXXXXXXXfXXfXXXfX",
    "X|fff|XXfffffXXXXfffffXX|fff|X",
    "XfXXXfXXXXXXfXXXXfXXXXXXfXXXfX",
    "XfXXXfXXffFf|ffff|fFffXXfXXXfX",
    "f|XXXfXXfXXXXXXXXXXXXfXXfXXX|f",
    "XfXXXfXXfXXXXXXXXXXXXfXXfXXXfX",
    "XfXXXfXXffFf|ffff|ffffXXfXXXfX",
    "XfXXXfXXXXXXfXXXXfXXXXXXfXXXfX",
    "X|fff|XXffFffXXXXffFffXX|fff|X",
    "XfXXXfXXfXXXXXXXXXXXXfXXfXXXfX",
    "XfXXX|ff||fffffffff|f|ff|XXXfX",
    "XfXXXfXXXfXXXXXXXXXfXXXXfXXXfX",
    "XfXXXfXXXfffffffffffXXXXfXXXfX",
    "f|fff|ffffXXXXXXXXXfffff|fff|f",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

Uint32 frameStart;
Uint32 frameTime;

struct point
{
    int x,y;
} pacBPos ,pacPos = {14*16,8*16};

int pacSpeed = 16;

point ghosts[4] = {
    {1*16,1*16},
    {28*16,1*16},
    {28*16,18*16},
    {1*16,18*16}
};

std::vector<SDL_Rect> blockRects;

double angle = 0.0f;

int frame = 0;
int ghostsframe = 0;
int dir = 3;


void InitSDLWindowRenderer();
void DestroySDLWindowRenderer();
void DrawMap();
SDL_Texture* LoadIMG(const char* filename);
bool IsGameOver();
void handleGhostAI(point& ghostPos, SDL_RendererFlip& ghostFlip);
bool CollisionWith(const SDL_Rect& object);
bool CollisionWithBlocks(const std::vector<SDL_Rect>& object);
void PacDie();

int main(int args,char* argv[])
{
    srand(time(NULL));

    InitSDLWindowRenderer();

    blockTex = LoadIMG("assets/ironblock.png");
    fruitTex = LoadIMG("assets/fruit.png");
    ghotsTex = LoadIMG("assets/ghostgray.png");
    pacTex = LoadIMG("assets/pacman.png");

    while(true)
    {
        frameStart = SDL_GetTicks();

        pacBPos = pacPos;

        ///<-Events->///
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                break;

        }

        const Uint8* state = SDL_GetKeyboardState(NULL);

        if(state[SDL_SCANCODE_E])
        {
            //fprintf(stdout,"map[pacPos.x/16][(pacPos.y-16)/16] = '%c' x:%d y:%d\n",map[(pacPos.y-16)/16][(pacPos.x)/16],(pacPos.y-16)/16,(pacPos.x)/16);
            if(map[(pacPos.y-16)/16][(pacPos.x)/16] != 'X')
            {
                pacPos.y -= pacSpeed;
                pacFlip = SDL_FLIP_VERTICAL;
                angle = 270;
                frame = 14 * int((SDL_GetTicks()/FPS)%3);
            }
        }
        else if(state[SDL_SCANCODE_D])
        {
            if(map[(pacPos.y+16)/16][(pacPos.x)/16] != 'X')
            {
                //fprintf(stdout,"map[pacPos.x/16][(pacPos.y-16)/16] = '%c' x:%d y:%d\n",map[(pacPos.y+16)/16][(pacPos.x)/16],(pacPos.y+16)/16,(pacPos.x)/16);
                pacPos.y += pacSpeed;
                pacFlip = SDL_FLIP_NONE;
                angle = 90;
                frame = 14 * int((SDL_GetTicks()/FPS)%3);
            }

        }
        else if(state[SDL_SCANCODE_S])
        {
            if(map[pacPos.y/16][(pacPos.x-16)/16] != 'X')
            {
                //fprintf(stdout,"map[pacPos.x/16][(pacPos.y-16)/16] = '%c' x:%d y:%d\n",map[pacPos.y/16][(pacPos.x-16)/16],(pacPos.x-16)/16,pacPos.y/16);
                //dir = 2;
                pacPos.x -= pacSpeed;
                pacFlip = SDL_FLIP_HORIZONTAL;
                angle = 0;
                frame = 14 * int((SDL_GetTicks()/FPS)%3);
            }
        }
        else if(state[SDL_SCANCODE_F])
        {
            if(map[pacPos.y/16][(pacPos.x+16)/16] != 'X')
            {
                //fprintf(stdout,"map[pacPos.x/16][(pacPos.y-16)/16] = '%c' x:%d y:%d\n",map[pacPos.y/16][(pacPos.x+16)/16],(pacPos.x+16)/16,pacPos.y/16);
                //dir = 3;
                pacPos.x += pacSpeed;
                pacFlip = SDL_FLIP_NONE;
                angle = 0;
                frame = 14 * int((SDL_GetTicks()/FPS)%3);
            }
        }

        if(state[SDL_SCANCODE_ESCAPE])
            break;


        /*if(dir == 0) ghostPos.y -= 16;
        if(dir == 1) ghostPos.y += 16;
        if(dir == 2) ghostPos.x -= 16;
        if(dir == 3) ghostPos.x += 16;*/

        for(int i=0;i<4;i++)
        {
            handleGhostAI(ghosts[i],ghostsFlips[i]);
            handleGhostAI(ghosts[i],ghostsFlips[i]);

            if(ghosts[i].x <= 0)
                ghosts[i].x = WIDTH;
            else if(ghosts[i].x >= WIDTH)
                ghosts[i].x = 1;

            SDL_Rect ghostRect = {ghosts[i].x,ghosts[i].y,14,14};
            if(CollisionWith(ghostRect))
            {
                PacDie();
            }
        }
        //<- End Events->///
        
        //removes the fruits from map 
        if(map[(pacPos.y)/16][(pacPos.x)/16] == 'F' || map[(pacPos.y)/16][(pacPos.x)/16] == 'f')
                map[(pacPos.y)/16][(pacPos.x)/16] = ' ';

        //Mirrors pacman shorcuts
        if(pacPos.x <= 0)
            pacPos.x = WIDTH;
        else if(pacPos.x >= WIDTH)
            pacPos.x = 1;

        //Mirrors ghost shorcuts

        if(IsGameOver())
            break;

        //<-Drawing Section->//
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);

        DrawMap();

        //Pacman drawing
        SDL_Rect clip = {frame,0,14,14};
        SDL_Rect rect = {pacPos.x,pacPos.y,14,14};
        SDL_RenderCopyEx(renderer,pacTex,&clip,&rect,angle,NULL,pacFlip);

        //Ghost drawing
        for(int i = 0;i<4;i++)
        {
            clip = {0,ghostsframe,14,14};
            rect = {ghosts[i].x,ghosts[i].y,14,14};
            SDL_RenderCopyEx(renderer,ghotsTex,&clip,&rect,0.0f,NULL,ghostsFlips[i]);
        }

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime<(1000/FPS))
        {
            SDL_Delay((1000/FPS) - frameTime);
        }

        //<-Drawing Section->//
    }
    SDL_DestroyTexture(pacTex);
    SDL_DestroyTexture(ghotsTex);
    SDL_DestroyTexture(blockTex);
    SDL_DestroyTexture(fruitTex);
    DestroySDLWindowRenderer();
}

void InitSDLWindowRenderer()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
#ifdef DEBUG
        fprintf(stderr,"%s",SDL_GetError());
#endif
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    if(SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0,&window,&renderer))
    {
#ifdef DEBUG
        fprintf(stderr,"%s",SDL_GetError());
#endif
        system("PAUSE");
        exit(EXIT_FAILURE);
    }
}

void DestroySDLWindowRenderer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DrawMap()
{
    int row,col;
    for(col=0;col<MAXCOLS;col++)
    {
        for(row=0;row<MAXROWS;row++)
        {
            SDL_Rect rect = {col*16,row*16,16,16};
            blockRects.push_back(rect);

            if(map[row][col] == 'X')
            {
                SDL_RenderCopy(renderer,blockTex,NULL,&rect);
            }
            if(map[row][col] == 'F')
            {
                SDL_Rect clip = {7,0,7,7};
                SDL_RenderCopy(renderer,fruitTex,&clip,&rect);
            }
            if(map[row][col] == 'f')
            {
                SDL_Rect clip = {0,0,7,7};
                SDL_RenderCopy(renderer,fruitTex,&clip,&rect);
            }
        }
    }
}

SDL_Texture* LoadIMG(const char* filename)
{
    SDL_Rect clip;
    SDL_Surface* tempsurf;
    SDL_Texture* tempTex;

    tempsurf = IMG_Load(filename);
    if(!tempsurf)
    {
#ifdef DEBUG
        fprintf(stderr,"%s",SDL_GetError());
#endif
        exit(EXIT_FAILURE);
    }
    tempTex = SDL_CreateTextureFromSurface(renderer,tempsurf);
    if(!tempTex)
    {
#ifdef DEBUG
        fprintf(stderr,"%s",SDL_GetError());
#endif
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(tempsurf);
    
    return tempTex;
}

bool IsGameOver()
{
    int row,col;
    for(col=0;col<MAXCOLS;col++)
        for(row=0;row<MAXROWS;row++)
            if(map[row][col] == 'F' || map[row][col] == 'f')
                return false;
    return true;
}

void handleGhostAI(point& ghostPos, SDL_RendererFlip& ghostFlip)
{

    if(map[ghostPos.y/16][ghostPos.x/16] == '|')
    {
        dir = rand()%4;
    }

    if(dir == 0)
    {
        if(map[(ghostPos.y-16)/16][ghostPos.x/16] != 'X')
            ghostPos.y -= 16;
        else
            dir = rand()%4;

        ghostsframe = 14 * int((SDL_GetTicks()/FPS)%2);
    }

    if(dir == 1)
    {
        if(map[(ghostPos.y+16)/16][ghostPos.x/16] != 'X')
            ghostPos.y += 16;
        else
            dir = rand()%4;

        ghostsframe = 14 * (2+int((SDL_GetTicks()/FPS)%2));
    }

    if(dir == 2)
    {
        if(map[ghostPos.y/16][(ghostPos.x-16)/16] != 'X')
            ghostPos.x -= 16;
        else
            dir = rand()%4;

        ghostsframe = 14 * (4+int((SDL_GetTicks()/FPS)%2));
        ghostFlip = SDL_FLIP_NONE;
    }

    if(dir == 3)
    {
        if(map[ghostPos.y/16][(ghostPos.x+16)/16] != 'X')
            ghostPos.x += 16;
        else
            dir = rand()%4;


        ghostsframe = 14 * (4+int((SDL_GetTicks()/FPS)%2));
        ghostFlip = SDL_FLIP_HORIZONTAL;
    }
}

bool CollisionWith(const SDL_Rect& object)
{
    /* if((ghost.x/16 == pacPos.x/16 && ghost.y/16 == pacPos.y/16)
            || (ghost.x/16 == pacBPos.x/16 && ghost.y/16 == pacBPos.y/16))
        return true; */
    // fprintf(stdout,"ghost x:%d y:%d\n",ghost.x,ghost.y);
    SDL_Rect rect1 = {pacPos.x,pacPos.y,14,14};
    SDL_Rect rect2 = {pacBPos.x,pacBPos.y,14,14};
    if(SDL_HasIntersection(&rect1,&object) || SDL_HasIntersection(&rect2,&object))
    {
        return true;
    }

    return false;
}

bool CollisionWithBlocks(const std::vector<SDL_Rect>& objects)
{
    for(int i=0;i<objects.size();i++)
    {
        if(CollisionWith(objects[i]))
        {
            fprintf(stdout,"Collision with Block\n");
            return true; 
        }
    }
    return false;
}

void PacDie()
{
    pacTex = LoadIMG("assets/pacmandie.png");
    SDL_DestroyTexture(ghotsTex);
    //frame = int((SDL_GetTicks()/100)%11);
    for(int i=0;i<11;i++)
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        DrawMap();
        frame = 19 * i;
        SDL_Rect clip = {frame,0,19,19};
        SDL_Rect rect = {pacPos.x,pacPos.y,14,14};
        SDL_RenderCopyEx(renderer,pacTex,&clip,&rect,angle,NULL,pacFlip);
        SDL_RenderPresent(renderer);
        SDL_Delay(80);
    }
    pacTex =  LoadIMG("assets/pacman.png");
    ghotsTex = LoadIMG("assets/ghostgray.png");
    frame = 0;
    SDL_Rect clip = {frame,0,14,14};
    SDL_Rect rect = {pacPos.x,pacPos.y,14,14};
    SDL_RenderCopyEx(renderer,pacTex,&clip,&rect,angle,NULL,pacFlip);
    pacPos = {14*16,8*16};
}
