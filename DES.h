#pragma once
#include<string>
#include<iostream>
using namespace std;
class T2_DES
{
public:
	static string sub[16];
	string Decrypt_DES(string plain, string key[16]);
	string Encrypt_DES(string cipher, string key[16]);
	void key_generation(string key);
	string Plain_Bin(string plain);

};

