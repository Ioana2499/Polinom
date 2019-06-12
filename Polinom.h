#ifndef POLINOM_H
#define POLINOM_H
#include <iostream>


class Polinom
{
    float* coef;
    int grad;
public:
    Polinom();
    ~Polinom();
    Polinom(const Polinom&);
    float valoareInPunct(int);
    void setGrad(int);
    void setCoef(float*m, int);
    float* getCoef();
    int getGrad();
    Polinom operator+(const Polinom&);
    int operator[](const int);
    Polinom operator*(const int);
    Polinom operator*(const Polinom&);
    Polinom& operator=(const Polinom&);
    Polinom operator/(Polinom&);
    void show();
    void eliminare(int);
    void adaugare(float, int);
    friend std::ostream & operator<<(std::ostream&, const Polinom&);
    friend std::istream & operator>>(std::istream&, Polinom&);
};

#endif // POLINOM_H
