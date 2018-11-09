#include <fstream>
#include <cmath>

using namespace std;

class Postscript {
private:
    ofstream file;
    double width, height;
public:
    Postscript(const string& filename, const int& w=800, const int& h=800): width(w), height(h){
        file.open(filename);
        file << "<</PageSize [" << width << " " << height << "]>> setpagedevice\n";
    }

    void line(const double& x1, const double& y1, const double& x2, const double& y2){
        file << x1 << " " << y1 << " moveto\n";
        file << x2 << " " << y2 << " lineto\n";
        file << "stroke\n";
    }

    void setColor(const int& r, const int& g, const int& b){
        file << r/255.0 << " " << g/255.0 << " " << b/255.0 << " setrgbcolor\n";
    }

    void rect(const double& x, const double& y, const double& w, const double& h){
        file << "newpath\n";
        file << x << " " << y << " moveto\n";
        file << x+w << " " << y << " lineto\n";
        file << x+w << " " << y+h << " lineto\n";
        file << x << " " << y+h << " lineto\n";
        file << "closepath\n";
    }

    void drawRect(const double& x, const double& y, const double& w, const double& h){
        rect(x,y,w,h);
        file << "stroke\n";
    }

    void fillRect(const double& x, const double& y, const double& w, const double& h){
        rect(x,y,w,h);
        file << "fill\n";
    }

    void triangle(const double& x1, const double& y1, const double& x2, const double& y2, const double& x3, const double& y3){
        file << "newpath\n";
        file << x1 << " " << y1 << " moveto\n";
        file << x2 << " " << y2 << " lineto\n";
        file << x3 << " " << y3 << " lineto\n";
        file << "closepath\n";
    }

    void drawTriangle(const double& x1, const double& y1, const double& x2, const double& y2, const double& x3, const double& y3){
        triangle(x1,y1,x2,y2,x3,y3);
        file << "stroke\n";
    }

    void fillTriangle(const double& x1, const double& y1, const double& x2, const double& y2, const double& x3, const double& y3){
        triangle(x1,y1,x2,y2,x3,y3);
        file << "fill\n";
    }

    void circle(const double& x, const double& y, const double& r){
        file << x << " " << y << " " << r << " 0" << " 360 arc\n";
    }

    void drawCircle(const double& x, const double& y, const double& r){
        circle(x,y,r);
        file << "stroke\n";
    }

    void fillCircle(const double& x, const double& y, const double& r){
        circle(x,y,r);
        file << "fill\n";
    }

    void setFont(const string& font, const int& num){
        file << "/" << font << " findfont " << num << " scalefont setfont\n";
    }

    void text(const double& x, const double& y, const string& t){
        file << x << " " << y << " moveto " << "(" << t << ") show\n";
    }

    void grid(const double& x1, const double& x_step, const double& x2, const double& y1, const double& y_step, const double& y2){
        for(double x = x1; x <= x2; x += x_step){
            line(x,y1,x,y2);
        }
        for(double y = y1; y <= y2; y += y_step){
            line(x1,y,x2,y);
        }
    }
};

int main() {
    Postscript p("test.ps");
    p.line(0,0, 300,400);  // 0 0 moveto 300 400 lineto stroke
    int r = 255, g = 0, b = 0;
    p.setColor(r, g, b); // r, g, b should be from 0.0 to 1.0
    // should turn into 1 0 0 setrgbcolor\n

    p.drawRect(100, 100, 80, 60);   // x y moveto x+w y lineto x+w y+h lineto ... closepath stroke
    p.fillRect(150, 200, 100, 50);   // x y moveto x+w y lineto x+w y+h lineto ... closepath fill
    p.drawTriangle(600,700, 300,300, 100,250);
    p.fillTriangle(400,200, 350,280, 480,300);
    p.drawCircle(400,400,100); // x y 0 360 r arc stroke
    p.fillCircle(700, 700, 50);
    p.setFont("Helvetica", 32); //  "/Helvetica findfont 32 scalefont setfont"
    p.text(300,400, "testing testing 123"); // 300 400 moveto (testing testing 123)show

    p.grid(300, 50, 500, 400, 50, 700); // x = 300 to 500 stepping 50
    // y = 400 to 700 stepping 50
}