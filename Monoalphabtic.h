#include <iostream>
#ifndef CRYPTOGRAPHY_Monoalphabetic_H
#define CRYPTOGRAPHY_Monoaalphabetic_H
#include <string.h>
using namespace std;

string Encrypt_Method1(string plaintext, string key);
string Encrypt_Method2(string plaintext, string key);
string Decrypt_Method1(string ciphertext, string key);
string Decrypt_Method2(string ciphertext, string key);

string AnalyzeUsingCharFrequency(string cipher);


#endif