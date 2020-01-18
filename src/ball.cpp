#include <iostream>
using namespace std;

class Ball{
    public:
        double x,y,r;
        int sx, sy;

        Ball(){ }
        Ball(double xx,double yy,double rr, int ssx, int ssy){
            x = xx;
            y = yy;
            r = rr;
            sx = ssx;
            sy = ssy;
        }

        void mmove(int xx, int yy){
            x = xx;
            y = yy;
        }

        void move(int w, int h){
            x += sx;
            y += sy;
            if(x>w){x=w; sx*=-1;}
            if(x<0){x=0; sx*=-1;}
            if(y>h){y=h; sy*=-1;}
            if(y<0){y=0; sy*=-1;}
        }
};
