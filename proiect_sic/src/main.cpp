#include <iostream>
using namespace std;

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
    if ((x >= c) && (x <= b))//cin>>e;
    {
        return ((b - x) / (b - c));
    }
}
//fuzificarea -Calculeaza activarile fiecarei functii pentru e si de
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
//inferenta - Calculeaza minimul dintre functiile de activare ale erorii si derivatei erorii
void inferenta(float mx[5], float mdx[3], float rez[5][3])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (mx[i] > mdx[j])
            {
                rez[i][j] = mdx[j];
            }
            else
            {
                rez[i][j] = mx[i];
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << rez[i][j] << " ";
        }
        cout << endl;
    }
}



//defizificarea-Calculeaza valoarea iesirii din rezulatorul fuzzy
float defuzificare(float bz_reg[5][3], float val[5][3])
{
    float suma = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            suma += val[i][j] * bz_reg[i][j];
        }
    }
    return suma;
}

void main()
{
    float me[5], mde[3]; // functiile de activare
    float rez[5][3];//matrice va contine ponderile 
    float e, de; //eroarea si derivata erorii
    float reguli[5][3] = { { -1, -1, -1 },{ 0, -0.5, -1 },{ 0.5, 0, -0.5 },{ 1, 0.5, 0.5 },{ 1,1,0.5 } };// baza de reguli
    cout << "Eroarea = ";
    cin >> e;
    cout << "Derivata erorii = ";
    cin >> de;


    cout << "Fuzificare : " << endl;
    fuzificare(e, de, me, mde);
    cout << "Inferente : " << endl;
    inferenta(me, mde, rez);
    cout << "Defuzificare : " << endl;

    cout << "Iesirea =  " << defuzificare(reguli, rez) << endl;
}






