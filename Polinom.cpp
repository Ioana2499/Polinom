#include "Polinom.h"
#include <iostream>
#include <math.h>

Polinom::Polinom()
{
    grad = 0;
    coef = NULL;
}
//functie de afisare
void Polinom::show()
{
    for(int i=grad; i>=1; i--)
        if(coef[i])
            std::cout<<coef[i]<<"x^"<<i<<" + ";
    std::cout<<coef[0]<<std::endl;
}
//destructorul care dezaloca vectorul de coeficienti si seteaza gradul la 0
Polinom::~Polinom()
{
    grad = 0;
    delete[] coef;
}

Polinom::Polinom(const Polinom& b)
{
    grad = b.grad;
    coef = new float[grad+1];
    for(int i=0; i<=grad; i++)
        coef[i] = b.coef[i];
}
//functie ce returneaza un pointer de tip float ce reprezinta coeficientii polinomului
float* Polinom::getCoef()
{
    return this->coef;
}
//functie ce calculeaza valoarea intr-un punct
float Polinom::valoareInPunct(int val)
{
    float suma = 0;
    for (int i = grad; i >= 0; i--)
    {
        suma = suma + coef[i] * pow(val, i);
    }
    return suma;
}
//functie ce returneaza gradul unui polinom
int Polinom::getGrad()
{
    return this->grad;
}
//functie ce supraincarca operatorul +
Polinom Polinom::operator+(const Polinom &b)
{
    //in polinomul aux voi calcula rezultatul adunarii
    Polinom aux;
    //in min1 si max1 aflu maximul si minimul dintre gradele operanzilor
    int min1, max1;
    if(b.grad > this->grad)
    {
        max1 = b.grad;
        min1 = grad;
    }
    else
    {
        max1 = grad;
        min1 = b.grad;
    }
    //setez gradul rezultatului la gradul celui mai mare dintre operanzi si aloc memoria necesara
    aux.grad = max1;
    aux.coef = new float[max1+1];
    for(int i=0; i<=aux.grad; i++)
    {
        aux.coef[i] = 0;
    }
    //adaug la rezultat suma coeficientilor pentru fiecare grad de gradul minim de ori
    for(int i=0; i<=min1; i++)
    {
        aux.coef[i] = coef[i] + b.coef[i];
    }
    //in functie de polinomul cu gradul mai mare copiez din acesta in rezultat
    if(grad > b.grad)
        for(int i=min1+1; i<=max1; i++)
        {
            aux.coef[i] = coef[i];
        }
    else
        for(int i=min1+1; i<=max1; i++)
        {
            aux.coef[i] = b.coef[i];
        }

    return aux;
}
//suprascrierea operatorului [] pentru a returna coeficientul gradului i
int Polinom::operator[](const int i)
{
    return coef[i];
}
//suprascrierea operatorului * pentru inmultire cu scalar
Polinom Polinom::operator*(const int nr)
{
    //in polinomul aux voi calcula rezultatul inmultirii
    Polinom aux;
    //polinomul rezultat va lua gradul polinomului din inmultire si i se va aloca memorie in functie de acesta
    aux.grad = this->grad;
    aux.coef = new float[this->grad+1];
    for(int i=0; i<=aux.grad; i++)
    {
        aux.coef[i] = 0;
    }
    //fiecare coeficient din polinomul supus inmultirii va fi inmultit cu nr si adaugat la rezultat
    for(int i=this->grad; i>=0; i--)
    {
        aux.coef[i] = coef[i] * nr;
    }

    return aux;
}
//suprascrierea operatorului * pentru inmultirea a doua polinoame
Polinom Polinom::operator*(const Polinom& b)
{
    //in polinomul aux voi calcula rezultatul inmultirii
    Polinom aux;
    int i, j;
    //gradul rezultatului va fi suma gradelor operanzilor
    aux.grad = b.grad + grad;
    aux.coef = new float[aux.grad+1];
    for(i=0; i<=aux.grad; i++)
    {
        aux.coef[i] = 0;
    }
    //gradului i+j din rezultat i se va adauga rezultatul inmultirii gradului i, respectiv j din polinoamele supuse inmultirii
    for(i=grad; i>=0; i--)
        for(j=b.grad; j>=0; j--)
        {
            aux.coef[i+j] += coef[i] * b.coef[j];
        }

    return aux;
}
//suprascrierea operatorului = ce egaleaza gradele si copiaza coeficientii
Polinom& Polinom::operator=(const Polinom &b)
{
    grad = b.grad;
    delete coef;
    coef = new float[grad+1];
    for(int i=0; i<=b.grad; i++)
        coef[i] = b.coef[i];
    return *this;
}
//suprascrierea operatorului /
Polinom Polinom::operator/(Polinom& b)
{
    //in polinomul result voi calcula rezultatul impartirii
    Polinom result;
    //polinomul aux este folosit ca si impartitor dupa initializare
    Polinom aux;
    //setez gradul rezultatului in functie de gradul imp si deimp
    if(grad - b.grad <= 0)
        result.grad = 0;
    else
        result.grad = grad - b.grad;
    //nr va tine cont de gradul urmatorului element din rezultat
    int nr = result.grad;

    //aici incepe partea de initializare a rezultatului
    result.coef = new float[result.grad + 1];
    for(int i=0; i<=result.grad; i++)
        result.coef[i] = 0;
    //adaug la rezultat
    result.adaugare(coef[grad] / b.coef[b.grad], result.grad);
    //ii atribui lui aux rezultatul inmultirii deimpartitului cu rezultatul care in acest moment este alcatuit dintr-un singur coeficient
    aux = result * b;
    //in aux scad din impartitor deimpartitul * rezultatul
    aux = *this + aux * (-1);
    //verific daca au ramas grade cu coeficienti nuli
    while(aux.coef[aux.grad] == 0)
        aux.grad--;
    //noul element din rezultat va avea gradul nr
    nr = aux.grad - b.grad;

    //impartirea continua pana cand gradul impartitorului este mai mic decat cel al deimpartitului
    while(aux.grad >= b.grad)
    {
        //in auxiliar voi calcula ultimul element adaugat in rezultat * deimpartitul
        Polinom auxiliar;
        auxiliar.coef = new float[nr+1];
        //ultimul element adaugat in rezultat are gradul nr
        auxiliar.grad = nr;

        //adaug la rezultat
        result.adaugare(aux.coef[aux.grad] / b.coef[b.grad], nr);
        //si adaug si intr-o variabila auxiliara
        auxiliar.adaugare(aux.coef[aux.grad] / b.coef[b.grad], nr);
        //scriu noul coeficient adaugat in rezultat ca si polinom folosind auxiliar2, pentru a-l putea inmulti cu deimpartitul
        Polinom auxiliar2 = b * auxiliar;
        //in aux scad din impartitor, (deimpartitul * ultimul element adaugat la rezultat) = auxiliar
        aux = aux + auxiliar2 * (-1);
        //verific daca au ramas grade cu coeficienti nuli
        while(aux.coef[aux.grad] == 0)
            aux.grad--;
        //urmatorul element din rezultat va avea gradul nr
        nr = aux.grad - b.grad;
    }
    return result;
}
//functie de adaugare element de gradul i
void Polinom::adaugare(float coeficient, int i)
{
    //daca gradul i este mai mic sau egal decat gradul polinomului, coeficientul gradului va lua valoarea data
    if(i <= grad)
    {
        coef[i] = coeficient;
    }
    //altfel adaug un nou grad
    else
    {
        float *aux = new float[i+1];
        for(int j=0; j<=grad; j++)
            aux[j] = coef[j];
        aux[i] = coeficient;
        for(int j=i-1; j>grad; j--)
            aux[j] = 0;
        grad = i;
        delete coef;
        coef = new float[grad+1];
        for(int j=0; j<=grad; j++)
            coef[j] = aux[j];
    }
}
//functie ce elimina gradul i
void Polinom::eliminare(int i)
{
    //daca gradul nu exista in polinom se va iesi fortat din functie
    if(i > grad)
        return;
    //daca gradul dorit este chiar cel mai mare, atunci se sterge
    else if(grad == i)
    {
        float *aux = new float[i];
        for(int j=0; j<grad; j++)
            aux[j] = coef[j];
        delete coef;
        coef = new float[i];
        for(int j=0; j<grad; j++)
            coef[j] = aux[j];
        grad = i-1;
    }
    //daca gradul este in interior, se va seta la 0
    else
    {
        coef[i] = 0;
    }
}
//functie ce seteaza valoarea gradului
void Polinom::setGrad(int grd)
{
    this->grad = grd;
}
//functie ce seteaza valoarea coeficientilor
void Polinom::setCoef(float *coeficient, int grd)
{
    for(int i=grd; i>=0; i--)
        coef[i] = coeficient[i];
}
//suprascrierea operatorului <<
std::ostream& operator<<(std::ostream &out, const Polinom& b)
{
    //sunt afisati toti coeficientii
    for(int i=b.grad; i>0; i--)
        if(b.coef[i] != 0)
            out << b.coef[i] << "X^" << i << " + ";
    out << b.coef[0] << std::endl;
    return out;
}
//suprascrierea operatorului >>
std::istream& operator>>(std::istream &in, Polinom& b)
{
    delete[] b.coef;
    in >> b.grad;
    b.coef = new float[b.grad+1];
    for(int i=b.grad; i>=0; i--)
        in >> b.coef[i];
    return in;
}
