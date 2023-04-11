#include <iostream>
#include <string.h>
#include "RepeatedKey.h"
#include <cstring>

using namespace std;
string ciphertext;
string plaintext;
string assumedkey;
char VigenereTable[26][26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
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

void get_ciphertext(int i, int j)
{
	char mychar;
	mychar = VigenereTable[i][j];
	//cout << i << " " << j << mychar << endl;
	ciphertext.push_back(mychar);
}
int get_char(int i, char ct)
{
	int here = 0;
	for (int j = 0; j < 26; j++)
	{
		if (VigenereTable[i][j] == ct)
		{
			here = j;
			//cout << j << endl;
			break;
		}
		else
		{
			continue;
		}
	}
	return here;
}

string repeatedkey(string pt, string key)
{

	if (pt.length() > key.length())
	{
		int i = 0;
		while (key.length() != pt.length())
		{
			if (pt.length() == i)
				i = 0;
			key.push_back(key[i]);
			i++;
		}
	}
	return key;
}
void indexes(string key, string pt)
{
	int i = 0, j = 0;
	for (int k = 0; k < key.length(); k++)
	{
		i = pt[k] - 'a';
		j = key[k] - 'a';
		get_ciphertext(i, j);
	}
}

string rkencryption(string pt, string key)
{
	string key_pt;
	key_pt = repeatedkey(pt, key);
	indexes(key_pt, pt);
	return ciphertext;
}

void get_plaintext(string ciphertext, string key)
{
	int i = 0;
	char pt;
	for (int k = 0; k < ciphertext.length(); k++)
	{
		i = key[k] - 'a';
		pt = (get_char(i, ciphertext[k]) + 'a');
		plaintext.push_back(pt);
	}
}

string rkdecryption(string ciphertext, string key)
{
	string key_ct;

	key_ct = repeatedkey(ciphertext, key);

	get_plaintext(ciphertext, key_ct);
	return plaintext;
}
string type2(string key) { //key appended by 0-multiple instance of key O(N ^ 2)
	int key_sz = key.size();
	string actual_key;
	for (int i = 1; i <= key_sz; i++) {
		string cur = key.substr(0, i); //pref string of size i
		bool valid = true;
		for (int j = 0; j < key_sz; j++) {
			if (key[j] != cur[j % i])
				valid = false;
		}
		if (valid) {
			actual_key = cur;
			break; //find the smallest key that cycles
		}
	}
	return actual_key;
}

string rkAnalyze(string plaintext, string CipherText)
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
			assumedkey.push_back(x);
		}
		else if (x < 0)
		{
			x += 26 + 'a';
			assumedkey.push_back(x);
		}

	}
	string orginalkey;
	orginalkey = type2(assumedkey);
	return orginalkey;

}
