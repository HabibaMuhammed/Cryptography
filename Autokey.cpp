#include <iostream>
#include <string.h>
#include "AutoKey.h"
using namespace std;

string CipherText;
string PlainText;
string C_Autokey, assumedAutokey;
char Vigenere_Table[26][26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
								'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A',
								'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B',
								'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C',
								'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D',
								'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E',
								'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F',
								'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G',
								'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H',
								'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I',
								'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J',
								'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K',
								'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L',
								'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M',
								'O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
								'P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
								'Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
								'R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
								'S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
								'T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S',
								'U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
								'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
								'W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
								'X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W',
								'Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X',
								'Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y' };

string AutoKey(string plaintext, string key)
{

	if (plaintext.length() > key.length())
	{
		int i = 0;

		while (key.length() != plaintext.length())
		{
			if (plaintext.length() == i)
				i = 0;
			key.push_back(plaintext[i]);
			i++;
		}
	}

	return key;
}

void index(string key, string pt)
{
	int i = 0, j = 0;
	for (int k = 0; k < key.length(); k++)
	{
		i = pt[k] - 'a';
		j = key[k] - 'a';
		GetCipherText(i, j);
	}
}

void GetCipherText(int plaintext_index, int key_index)
{
	char mychar;
	mychar = Vigenere_Table[plaintext_index][key_index];
	cout << plaintext_index << " " << key_index << "refers to the character: " << mychar << endl;
	CipherText.push_back(mychar);
}

string AKEncrypt(string plaintext, string Key)
{
	string P_autokey;
	P_autokey = AutoKey(plaintext, Key);
	index(P_autokey, plaintext);
	return CipherText;
}

int character(char cipher_char, int j)
{
	int CipherPosition = 0;
	for (int row = 0; row < 26; row++)
	{
		if (Vigenere_Table[row][j] == cipher_char)
		{
			CipherPosition = row;
			cout << row << " " << j << endl;
			break;
		}
		else
		{
			continue;
		}
	}
	return CipherPosition;
}

void GetAutoKey(string ciphertext, string key)
{
	int j = 0;
	char pt;
	int len = ciphertext.length() - key.length();
	if (ciphertext.length() > key.length())
	{
		int i = 0;

		while (key.length() != ciphertext.length())
		{
			if (ciphertext.length() == i)
				i = 0;
			for (int k = 0; k < len; k++)
			{
				j = key[k] - 'a';
				pt = character(ciphertext[k], j) + 'a';
				PlainText.push_back(pt);
				key.push_back(pt);
			}
		}
	}
	C_Autokey = key;
}

string AKDecrypt(string ciphertext, string key) // ciphertext = HLKEK & key = hey
{
	int leng = ciphertext.length() - key.length(); // length = 5 - 3 = 2 
	GetAutoKey(ciphertext, key);
	cout << "AutoKey: " << C_Autokey << endl; // AutoKey = heyah
	int j = leng;
	char pt;
	for (int k = leng; k < ciphertext.length(); k++)//k=2
	{
		j = C_Autokey[k] - 'a'; // j = 121-97=24
		pt = (character(ciphertext[k], j) + 'a'); //pt = character (ct,24)+'a'
		PlainText.push_back(pt);
	}
	return PlainText;
}


string type(string key, string ptext) { //key appended by pref. of text  O(N ^ 2)
	int key_sz = key.size(), ptext_sz = ptext.size();

	string actual_key;
	for (int i = 1; i <= min(key_sz, ptext_sz); i++) {
		string suf = key.substr(key_sz - i); //suffix string of size i in key
		string pref = ptext.substr(0, i);
		//prefix string of size i in text
		if (pref == suf)
		{

			actual_key = key.substr(0, key_sz - i); //string of size key - the common suffix that found
			break;
		}
	}
	if (actual_key.empty())
		return key;
	else
		return actual_key;
}


string AKAnalyzeAutoKey(string plaintext, string CipherText)
{
	int l = CipherText.length();
	for (int i = 0; i < l; i++)
	{
		char ct = CipherText[i];
		CipherText[i] = tolower(ct);
	}
	cout << CipherText << endl;

	for (int i = 0; i < l; i++)
	{
		char x = ((CipherText[i] - 'a') - (plaintext[i] - 'a')) % 26;
		if (x >= 0 && x < 26)
		{
			x += 'a';
			assumedAutokey.push_back(x);
		}
		else if (x < 0)
		{
			x += 26 + 'a';
			assumedAutokey.push_back(x);
		}

	}
	string orginalkey;
	orginalkey = type(assumedAutokey, plaintext);
	return orginalkey;
}