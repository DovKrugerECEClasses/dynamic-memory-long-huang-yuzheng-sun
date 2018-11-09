#include <iostream>
using namespace std;
class String {
private:
    uint32_t capacity;
    uint32_t len;
    char* s;
    uint32_t stringlen(const char* str) const{
        uint32_t count = 0;
        while (*str++ != '\0')
            count++;
        return count;
    }
    void checkGrow(const uint32_t& newLen){
        if(newLen > capacity){
            capacity = newLen*2;
            char* old = s;
            s = new char[capacity];
            for(int i=0; i<len; i++)
                s[i] = old[i];
            delete [] old;
        }
    }
public:
    String();
    String(const uint32_t& initialCapacity);
    String(const char str[]);

    String(const char str[], const uint32_t& mult);
    ~String();

    //copy constructor
    String(const String& orig);
    String& operator =(const String& orig);
    char  operator [](const uint32_t& pos)const;
    char& operator [](const uint32_t& pos);
    friend ostream& operator<<(ostream& s, const String& str);
    void operator +=(const char str[]);
    String substring(const int& p, const uint32_t& l);
    void replace(const char& past, const char& now);
    int length() const;
    void insert(const int& p, const String& str);
    friend String operator +(const String& s1, const String& s2);
};
