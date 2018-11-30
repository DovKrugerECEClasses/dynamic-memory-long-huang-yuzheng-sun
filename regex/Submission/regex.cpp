#include <fstream>
#include <regex>
using namespace std;

int main() {

    regex regex_tspan("<[/]?tspan[^>]*>");
    regex regex_floating("([-]?[0-9]+\\.)([0-9]+)");

    ifstream f1;
    f1.open("Periodic.svg");

    ofstream f2;
    f2.open("Periodic_new.svg");

    string line;
    while(!f1.eof()){
        getline(f1,line);

        line = regex_replace(line,regex_tspan,"");

        smatch sm;
        string newLine = line;
        if(regex_search(line,sm,regex_floating)){
            newLine = "";
            while(regex_search(line,sm,regex_floating)){
                newLine = newLine + sm.prefix().str() + sm[1].str() + sm[2].str()[0];
                line = sm.suffix().str();
            }
            newLine += line;
        }

        f2<<newLine<<'\n';
    }

    f1.close();
    f2.close();

}