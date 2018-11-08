#include <iostream>
#include "Color.hh"
#include <cmath>
using namespace std;

class Bitmap{
private:
    uint width, height;
    uint32_t* map;
public:
    Bitmap(const uint& width, const uint& height): width(width), height(height), map(new uint32_t[width*height]){}

    ~Bitmap(){
        delete [] map;
    }

    void drawPixel(const int& x, const int& y, const Color& color){
        if(x>=0 && x<width && y>=0 && y<height) {
            map[x + y*width] = color.getRgba();
        }
    }

    void line(const int& x1, const int& y1, const int& x2, const int& y2, const Color& color){
        int x,y,dx,dy,unitx,unity,abs_dx,abs_dy;
        dx=x2-x1;
        dy=y2-y1;
        abs_dx = abs(dx);
        abs_dy = abs(dy);
        x=x1;
        y=y1;
        if( abs_dx > abs_dy )
        {
            unitx = dx / abs_dx ;
            for(int i=0;i<=abs_dx;i++)
            {
                y=round(1.0*dy/dx*(x-x1)+y1);
                drawPixel(x,y,color);
                x+=unitx;
            }
        }
        else {
            unity = dy / abs_dy ;
            for(int i=0;i<=abs_dy;i++)
            {
                x=round(1.0*dx/dy*(y-y1)+y1);
                drawPixel(x,y,color);
                y+=unity;
            }
        }
    }

    void horizLine(const int& x1, const int& x2, const int& y, const Color& color){
        for(int x=x1;x<=x2;x++)
            drawPixel(x,y,color);
    }

    void vertLine(const int& x, const int& y1, const int& y2, const Color& color){
        for(int y=y1;y<=y2;y++)
            drawPixel(x,y,color);
    }

    void drawRect(const int& x0, const int& y0, const uint& w, const uint& h, const Color& color){
        horizLine(x0,x0+w,y0,color);
        horizLine(x0,x0+w,y0+h,color);
        vertLine(x0,y0,y0+h,color);
        vertLine(x0+w,y0,y0+h,color);
    }

    void fillRect(const int& x0, const int& y0, const uint& w, const uint& h, const Color& color){
        for(int x=x0;x<=x0+w;x++){
            for(int y=y0;y<=y0+h;y++){
                drawPixel(x,y,color);
            }
        }
    }

    void ellipse(const int& x0, const int& y0, const uint& w, const uint& h, const Color& color){
        if(w > h){
            int y1,y2;
            for(int x=round(x0-w/2.0); x<=round(x0+w/2.0);x++){
                y1 = round(sqrt((1-4.0*(x-x0)*(x-x0)/(w*w))*(h*h/4.0))+y0);
                y2 = round(-sqrt((1-4.0*(x-x0)*(x-x0)/(w*w))*(h*h/4.0))+y0);
                drawPixel(x,y1,color);
                drawPixel(x,y2,color);
            }
        }
        else{
            int x1,x2;
            for(int y=round(y0-h/2.0); y<=round(y0+h/2.0);y++){
                x1 = round(sqrt((1-4.0*(y-y0)*(y-y0)/(h*h))*(w*w/4.0))+x0);
                x2 = round(-sqrt((1-4.0*(y-y0)*(y-y0)/(h*h))*(w*w/4.0))+x0);
                drawPixel(x1,y,color);
                drawPixel(x2,y,color);
            }
        }
    }

    friend ostream& operator <<(ostream& s, const Bitmap& b){
        for(int i=0; i<b.height; i++){
            for(int j=0; j<b.width; j++){
                cout<<getColor(b.map[i*b.width+j])<<" ";
            }
            cout<<'\n';
        }
        return s;
    }
};

int main() {
    Bitmap b(30,20); // 30 pixels across, 20 pixels high, each pixel RGBA
    // top left pixel = (0,0)
    Color RED(255,0,0); // all red, no green, no blue (fully opaque)
    Color GREEN(0,255,0);
    Color BLUE(0,0,255);
    Color WHITE(255,255,255);
    Color BLACK(0,0,0);


    b.line(0,0,   19,19, RED);
    b.line(0,5,   29,10, BLUE); //Bresenham algorithm
    //https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

    // https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
    //TODO: b.line(0,100, 100,50, BLUE); //Wu algorithm
    b.horizLine(0, 20, 19, GREEN); // from x=0 to x=20 at y=19
    b.vertLine(5, 0,19, GREEN); // from y = 0 to y=19 at x = 5
    b.fillRect(10,10, 4, 3,BLACK); // x = 10, y =10 w=4, h=3
    b.drawRect(10,10, 4, 3,WHITE); // x = 10, y =10 w=4, h=3
    b.ellipse(15,0, 8, 5, RED);    // ellipse centered at (15,0) w= 8, h=5
    cout << b;
    /*
R
 R
  R
   R
    R
BBB
   BBBBB
        BBBBBB


     */
}