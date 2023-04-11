#pragma once
#include <iostream>
#include <string.h>

using namespace std;

void GetCipherText(int plaintext_index, int key_index);
string AutoKey(string plaintext, string key);
void index(string key, string pt);
string AKEncrypt(string plaintext, string key);
void GetAutoKey(string ciphertext, string key);
string AKDecrypt(string ciphertext, string key);
int character(char cipher_char, int j);
string AKAnalyzeAutoKey(string PlainText, string CipherText);
string type(string key, string ptext);