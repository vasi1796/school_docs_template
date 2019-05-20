#include <iostream>

//functia de apartenenta de tip triunghi
float triunghi(float a, float c, float b, float x)
{
    if ((x < a) || (x > b))
    {
        return 0;
    }
    if ((x >= a) && (x < c))
    {
        return ((x - a) / (c - a));
    }
    if ((x >= c) && (x <= b))
    {
        return ((b - x) / (b - c));
    }
}

//se calculeaza activarea fiecarei functii pentru cele 2 variabile de discurs
void fuzificare(float x, float dx, float mx[5], float mdx[3])
{
    mx[0] = triunghi(-1, -0.65, -0.3, x);
    mx[1] = triunghi(-0.4, -0.2, 0, x);
    mx[2] = triunghi(-0.05, 0, 0.05, x);
    mx[3] = triunghi(0, 0.2, 0.4, x);
    mx[4] = triunghi(0.3, 0.65, 1, x);

    mdx[0] = triunghi(-1, -0.5, 0, dx);
    mdx[1] = triunghi(-0.5, 0, 0.5, dx);
    mdx[2] = triunghi(0, 0.5, 1, dx);
}

//se calculeaza minimul dintre functiile de activare ale erorii si derivatei erorii
void inferenta(float mx[5], float mdx[3], float rez[5][3])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rez[i][j] = mx[i] > mdx[j] ? mdx[j] : mx[i];
        }
    }

    //afisare tabel de inferenta
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << rez[i][j] <<" ";
        }
        std::cout << std::endl;
    }
}

//se calculeaza valoarea de iesire din regulator
float defuzificare(float bz_reg[5][3], float val[5][3])
{
    float suma = 0;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            suma += val[i][j] * bz_reg[i][j];
        }
    }
    return suma;
}

void main()
{
    // functiile de activare
    float me[5], mde[3]; 

    //matricea cu ponderi 
    float rez[5][3];
    
    //eroarea si derivata erorii
    float e, de; 
    
    // baza de reguli, fiecare element este o coloana de la NB -> PB
    float reguli[5][3] = { { -0.5, -1, -1 },{ 0, -0.5, -1 },{ 0.5, 0, -0.5 },{ 1, 0.5, 0.5 },{ 1,1,0.5 } };
    
    //citire variabile 
    while (true)
    {
        std::cout << "e = ";
        std::cin >> e;
        std::cout << "de = ";
        std::cin >> de;

        std::cout << "Fuzificare: " << std::endl;
        fuzificare(e, de, me, mde);
        std::cout << "Inferente: " << std::endl;
        inferenta(me, mde, rez);

        std::cout << "Iesirea =  " << defuzificare(reguli, rez) << std::endl;
    }
}






