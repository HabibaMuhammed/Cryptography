#include <iostream>
using namespace std;
int gcd(int a, int b);
int mod_inv(int A, int M);
double key_setup(int p, int q, int M, int e);
int fp(int base, int exp, int mod);
int rsaEncrypt(int p, int q, int M, int e);
int rsaDecrypt(int p, int q, int C, int e);