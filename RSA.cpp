#include <iostream>
#include "RSA.h"
#include<math.h>
using namespace std;
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int mod_inv(int a, int n)
{
    for (int i = 1; i < n; i++)
        if (((a % n) * (i % n)) % n == 1)
            return i;

    return 0;
}
int fp(int base, int exp, int mod)
{
    if (exp == 0)
        return 1;
    int  ans = fp(base, exp / 2, mod);
    ans = (ans * ans) % mod;
    if (exp % 2 != 0)
        ans = (ans * (base % mod)) % mod;
    return ans;
}
double e1;
double d;
double key_setup(int p, int q, int M, int e)
{
    double n = p * q;
    double totient = (p - 1) * (q - 1);
    e1 = e;
    while (e < totient) {

        if (gcd(e, totient) == 1)
            break;
        else
            e++;
    }
    e1 = e;
    d = mod_inv(e, totient);


    return n;
}


int rsaEncrypt(int p, int q, int M, int e) {
    double n = key_setup(p, q, M, e);
    double cipher = fp(M, e, n);
    int c = (double)cipher;
    return c;
}
int rsaDecrypt(int p, int q, int C, int e) {
    double n = key_setup(p, q, C, e);

    double plain = fp(C, d, n);
    int pt = ceil(plain);
    return pt;
}
