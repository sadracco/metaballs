#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <array>
#include <time.h>
#include "ball.cpp"
#include <math.h>
using namespace std;

class Vis{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        const static int w=300;
        const static int h=300;

        int mX;
        int mY;
        int wX;
        int wY;

        double surf[h][w] = {0};

        Ball balls[7];

        bool isOn;

        void run(){
            while(isOn){
                check_events();
                update();
                render();
            }
        }

        void check_events(){
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        isOn = false;
                        break;

                    case SDL_MOUSEMOTION:
                        SDL_GetWindowPosition(window,&wX,&wY);
                        SDL_GetGlobalMouseState(&mX,&mY);
                        mX -= wX;
                        mY -= wY;
                        break;
                }
            }
        }

        double fallback(double r){
            if(r>1)
                return 0;
            return r;
        }

        void update(){
            double v;
            double s;
            double dx, dy;
            for(int y=0; y<h; y++){
                for(int x=0; x<w; x++){
                    s = 0;
                    for(auto b : balls){
                        dx = b.x-x;
                        dy = b.y-y;
                        v = b.r*b.r/(dx*dx+dy*dy);
                        s += v;
                    }
                    surf[y][x] = fallback(s);
                }
            }

            for(int i=0; i<sizeof(balls)/sizeof(Ball)-1; i++)
                balls[i].move(w, h);

            balls[sizeof(balls)/sizeof(Ball)-1].mmove(mX, mY);
        }

        void color(double v){
            int b = v*v*255;
            int g = 0;
            int r = 0;
            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
        }

        void render(){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            for(int y=0; y<h; y++){
                for(int x=0; x<w; x++){
                    color(surf[y][x]);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }

            SDL_RenderPresent(renderer);
        }

    public:
        Vis(std::string name){
            srand(time(NULL));
            for(int i=0; i<sizeof(balls)/sizeof(Ball); i++)
                balls[i] = Ball(rand()%w, rand()%h, rand()%20+10, rand()%10-5, rand()%10-5);

            SDL_Init(SDL_INIT_VIDEO);
            window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
            isOn = true;
            run();
            SDL_Quit();
        }
};
