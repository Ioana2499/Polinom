#include <iostream>
#include "Polinom.h"
using namespace std;

int main()
{
    Polinom P, Q;
    cin >> P;
    cin >> Q;
    cout << P;
    cout << Q;
    Polinom I = P * Q;
    cout << I;
    I = P + Q;
    cout << I;
    I = P / Q;
    cout << I;
    I = Q * 2;
    cout << I;
    cout<<P.valoareInPunct(1)<<endl;
    return 0;
}
