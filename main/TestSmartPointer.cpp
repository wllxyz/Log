#include "SmartPointer.h"

int main()
{
    SmartPointer<char> cp1(new char('a'));
    SmartPointer<char> cp2(cp1);
    SmartPointer<char> cp3;
    cp3 = cp2;
    cp3 = cp1;
    cp3 = cp3;
    SmartPointer<char> cp4(new char('b'));
    cp3 = cp4;
    return 0;
}

