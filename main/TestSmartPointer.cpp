#include "SmartPointer.h"

int main()
{
    SmartPointer<char> cp1(new char('a'));
    SmartPointer<char> cp2(cp1);
    SmartPointer<char> cp3 = new char('c');
    cp3 = cp2;
    cp3 = cp1;
    cp3 = cp3;
    SmartPointer<char> cp4(new char('b'));
    cp3 = cp4;
    SmartPointer<char> cp5;
    SmartPointer<char> cp6 = cp5;

    return 0;
}

