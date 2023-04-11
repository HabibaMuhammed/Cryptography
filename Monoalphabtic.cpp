#include <iostream>
#include <String>
#include<vector>
#include <map>
#include <iterator>
#include<algorithm>
#include "Monoalphabtic.h"
using namespace std;

//
// Created by Aisha
//

string Encrypt_Method1(string plaintext, string key)
{
	char check;
	int reminder = 0, i = 0;
	if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
	{
		while (i < plaintext.length())
		{
			check = (key[i] - 'a') + (plaintext[i] - 'a');
			if (check > 26)
			{
				reminder = check % 26;
				check = reminder + 'a';
				plaintext[i] = check;
			}
			else
			{
				plaintext[i] = check + 'a';
			}
			i++;
		}
	}
	return plaintext;
}
string Encrypt_Method2(string plaintext, string key)
{
	string cipher = plaintext;
	map<char, char>mapping;
	char ch = 'a';
	for (int i = 0; i < 26; i++) {
		mapping[ch] = key[i];
		ch++;
		
	}

	for (int i = 0; i < plaintext.length(); i++) {
		if (plaintext[i] < 97 || plaintext[i]>122) {
			cipher[i] = plaintext[i];
		}
		else {
			cipher[i] = mapping[plaintext[i]];
		}

	}

	return cipher;
}

string Decrypt_Method2(string ciphertext, string key)
{
	string plain = ciphertext;
	map<char, char>mapping;
	char ch = 'a';
	for (int i = 0; i < 26; i++) {
		mapping[key[i]] = ch;
		ch++;
	}


	for (int i = 0; i < ciphertext.length(); i++) {
		if (ciphertext[i] < 97 || ciphertext[i]>122) {
			plain[i] = ciphertext[i];
		}
		else {
			plain[i] = mapping[ciphertext[i]];
		}

	}


	return plain;
}


string Decrypt_Method1(string ciphertext, string key)
{
	char check;
	int reminder = 0, i = 0;
	if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z')
	{
		while (i < ciphertext.length())
		{
			check = (ciphertext[i] - 'a') - (key[i] - 'a');
			if (check > 26)
			{
				reminder = check % 26;
				check = reminder + 'a';
				ciphertext[i] = check;
			}
			else if (check < 0)
			{
				reminder = check % 26;
				check = reminder + 26 + 'a';
				ciphertext[i] = check;
			}
			else
			{
				ciphertext[i] = check + 'a';
			}
			i++;
		}
	}
	return ciphertext;
}
bool cmp(pair<char, float>& a,
	pair<char, float>& b)
{
	return a.second < b.second;
}


string AnalyzeUsingCharFrequency(string cipher)
{
	map<char, float>frequen;
	map<char, char>mono;
	map<char, float>::iterator itr;
	map<char, char>::iterator itr2;
	char ch = 'a';
	for (int i = 0; i < 26; i++)
	{
		
		frequen.insert(pair<char, float>(ch, 0));
		ch++;
	}
	for (int i = 0; i < cipher.length(); i++)
	{
		if (cipher[i] >= 'a' && cipher[i] <= 'z')
		{
			frequen[cipher[i]]++;
		}
	}

	vector<pair<char, float> > A;


	for (auto& it : frequen)
	{
		A.push_back(it);
	}

	sort(A.begin(), A.end(), cmp);
	reverse(A.begin(), A.end());
	string frequency_english = "etaoinsrhdlucmfywgpbvkxqjz";

	for (int i = 0; i < 26; i++)
	{
		mono.insert(pair<char, char>(A[i].first, frequency_english[i]));
		ch++;
	}
	//for (auto& it : A) {
	//
	//        cout << it.first << ' '
	//             << it.second << endl;
	//    }
	string plain = cipher;
	for (int i = 0; i < cipher.length(); i++)
	{
		if (cipher[i] < 'a' || cipher[i]>'z')
			plain[i] = cipher[i];
		else
		{
			plain[i] = mono[cipher[i]];

		}
	}
	for (auto& p : A) p.second = (float)(p.second / cipher.length()) * 100;
	for (auto& it : A) {

		cout << it.first << ' '
			<< it.second << endl;
	}

	return plain;

}

