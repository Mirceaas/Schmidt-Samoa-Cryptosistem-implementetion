#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

long long cmmdc(long long a, long long b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return cmmdc(b, a % b);
    }
}

// Functie pentru calculul exponential modular
long long modExp(long long baza, long long exponent, long long modulo)
{
    long long rezultat = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            rezultat = (rezultat * baza) % modulo;
        }
        baza = (baza * baza) % modulo;
        exponent = exponent / 2;
    }
    return rezultat;
}

// Functie pentru calculul inversului unui numar in modul m folosind algoritmul lui Euclid extins
long long modInvers(long long a, long long m)
{
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1)
    {
        return 0;
    }
    while (a > 1)
    {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
    {
        x += m0;
    }
    return x;
}

int main()
{
    // Alegerea a doua nr mari prime distincte
    long long p = 991;
    long long q = 997;

    // Calculeaza cheia publica cu formula N = p^2*q
    long long N = p * p * q;

    // Calculeaza cheia privata cu formula d = N^(-1) mod cmmmc(p-1, q-1)
    long long cmmmc = (p - 1) * (q - 1) / cmmdc(p - 1, q - 1);
    long long d = modInvers(N, cmmmc);

    // Afiseaza in consola cele 2 chei
    cout << "Cheia publica: N = " << N << endl;
    cout << "Cheia privata: d = " << d << endl;

    // Citirea mesajului din fisierul de intrare 
    ifstream infile("input.txt");
    stringstream buffer;
    buffer << infile.rdbuf();
    string mesaj = buffer.str();

    vector<long long> ciphers;

    // Cripteaza mesajul
    stringstream mesaj_criptat;
    for (char& c : mesaj)
    {
        // Criptare mesaj folosinf formula: c = m^N mod N
        long long m = (long long)c;
        long long cipher = modExp(m, N, N);
        char caracter_criptat = static_cast<char>(cipher % 26 + 'A'); //daca valoarea e mai mare decat 26, facem modulo pentru a l aduce in intervalul respectiv, urmand sa adunam codul ascii a lui A
        mesaj_criptat << caracter_criptat;
        ciphers.push_back(cipher); //pentru a retine nr intregi ce vor fi folosite la decriptare
    }

    stringstream mesaj_decriptat;
    for (long long c : ciphers) {
        long long m = modExp(c, d, p * q);
        char caracter_decriptat = static_cast<char>(m);
    }
    for (long long c : ciphers) {
        long long m = modExp(c, d, p * q);
        char caracter_decriptat;
        /* if (m >= 0 && m <= 13) {
             caracter_decriptat = static_cast<char>(m + 'M');
         }*/
         //else {
        caracter_decriptat = static_cast<char>(m);
        //}
        mesaj_decriptat << caracter_decriptat;
        cout << m << " ";
    }

    // Scrierea mesajului decriptat in fisierul de iesire
    ofstream outfile("criptare.txt");
    outfile << mesaj_criptat.str();

    ofstream outfile2("decriptare.txt");
    outfile2 << mesaj_decriptat.str();

    return 0;
}