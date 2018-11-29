#include "Fraction.hh"

using namespace std;
Fraction::Fraction(int n, int d): num(n), den(d) { // TODO: finish initializer list :

}

//friend
Fraction operator +(Fraction a, Fraction b) {
    //  a. b.
    return Fraction(a.num*b.den+a.den*b.num, a.den*b.den);
}

// member operator
Fraction Fraction::operator -(Fraction f) {
    return Fraction(this->num*f.den-this->den*f.num, this->den*f.den);
}

ostream& operator <<(ostream& s, Fraction b) {
    return s<<b.num<<"/"<<b.den;
}

//just here for illustration, you do not have to do anything
void Fraction::simplify() {
}
