#include <iostream>
#ifndef CRYPTOGRAPHY_Ceaser_H
#define CRYPTOGRAPHY_Ceaser_H
#include <string.h>
using namespace std;

string Encrypt_Caesar(string plaintext, int key);
string Decrypt_Caesar(string ciphertext, int key);
int Analyze(string plaintext, string ciphertext);

#endif