#pragma once
#include<iostream>
#include<string.h>
using namespace std;

string Encrypt_RailFence(string plainText, int key);
string Decrypt_RailFence(string cipherText, int key);

string removeSpaces(string str);
int Analyse(string plainText, string cipherText);