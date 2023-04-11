#pragma once
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

void get_ciphertext(int i, int j);
string repeatedkey(string pt, string key);
void indexes(string key, string pt);
string rkencryption(string plaintext, string key);
void get_plaintext(string ciphertext, string key);
string rkdecryption(string ciphertext, string key);
string rkAnalyze(string plaintext, string CipherText);
string type2(string key);