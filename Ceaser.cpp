#include <iostream>
#include <String>
#include "Ceaser.h"

using namespace std;
string Encrypt_Caesar(string plaintext, int key)
{
	char check1 = 0;
	int i = 0;

	if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
	{
		do
		{
			plaintext[i] = 'a' + ((plaintext[i] - 'a') + key) % 26;
			i++;
		} while (i < plaintext.length());
	}
	else
	{
		cout << "Enter a valid plaintext.";
	}
	return plaintext;
}

string Decrypt_Caesar(string ciphertext, int key)
{
	int i = 0;
	char check2 = 0;
	if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
	{
		do
		{
			ciphertext[i] = 'a' + ((ciphertext[i] - 'a') - key + 26) % 26;
			i++;
		} while (i < ciphertext.length());
	}
	else
	{
		cout << "Enter a valid ciphertext.";
	}
	return ciphertext;
}

int Analyze(string plaintext, string ciphertext) // brute force attack
{
	int keyattempt = 0;
	string test;
	if (plaintext == ciphertext)
	{
		return keyattempt;
	}
	for (int i = 1; i < 26; i++)
	{
		test = Encrypt_Caesar(plaintext, i);
		if (test == ciphertext)
		{
			keyattempt = i;
			break;
		}


	}
	return keyattempt;
}