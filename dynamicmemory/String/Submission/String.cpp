#include "String.hh"

String::String(): capacity(0), len(0), s(nullptr) {}

String::String(const uint32_t& initialCapacity): capacity(initialCapacity), len(0), s(new char[capacity]) {}

String::String(const char str[]): capacity(stringlen(str)), len(capacity), s(new char[capacity]) {
    for(int i=0; i<len; i++)
        s[i] = str[i];
}

String::String(const char str[], const uint32_t& mult): capacity(mult*stringlen(str)), len(capacity), s(new char[capacity]) {
    uint32_t strlen = len/mult;
    for(int i=0; i<mult; i++){
        for(int j=0; j<strlen; j++)
            s[i*strlen+j] = str[j];
    }
}

String::~String() {
    delete [] s;
}

//copy constructor
String::String(const String& orig): capacity(orig.capacity), len(orig.len), s(new char[capacity]) {
    memcpy(s,orig.s,len);
}
String& String::operator =(const String& orig) {
    String copy(orig);
    capacity = orig.capacity;
    len = orig.len;
    swap(s, copy.s);
    return *this;
}

char String::operator [](const uint32_t& pos)const {
    return s[pos];
}
char& String::operator [](const uint32_t& pos) {
    return s[pos];
}

ostream& operator<<(ostream& s, const String& str) {
    for(int i=0; i<str.len; i++)
        s << str.s[i];
    return s;
}

void String::operator+=(const char *str) {
    uint32_t strlen = stringlen(str);
    checkGrow(len+strlen);
    for(int i=0; i<strlen; i++)
        s[len+i] = str[i];
    len = len + strlen;
}

String String::substring(const int& p, const uint32_t& l) {
    String str;
    str.capacity = l;
    str.len = str.capacity;
    str.s = new char[str.capacity];
    for(int i=0; i<l; i++)
        str.s[i] = s[p+i];
    return str;
}

void String::replace(const char& past, const char& now) {
    for(int i=0; i<len; i++){
        if(s[i]==past){
            s[i] = now;
        }
    }
}

int String::length() const{
    return len;
}

void String::insert(const int &p, const String &str) {
    //what if p is greater than len-1?
    char *old = s;
    capacity = capacity+str.len;
    s = new char[capacity];
    for(int i=0; i<=p; i++)
        s[i] = old[i];
    for(int i=0; i<str.len; i++)
        s[p+1+i] = str.s[i];
    for(int i=0; i<len-(p+1); i++)
        s[p+1+str.len+i] = old[p+1+i];
    len = len + str.len;
    delete [] old;
}

String operator +(const String& s1, const String& s2){
    String ans;
    ans.capacity = s1.len + s2.len;
    ans.len = ans.capacity;
    ans.s = new char[ans.capacity];
    for(int i=0; i<s1.len; i++)
        ans.s[i] = s1.s[i];
    for(int i=0; i<s2.len; i++)
        ans.s[s1.len+i] = s2.s[i];
    return ans;
}
