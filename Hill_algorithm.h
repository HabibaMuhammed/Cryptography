#include <iostream>
using namespace std;
class Hill_Algorithm
{
public:
	static int size_of_plain;
	static int size_of_cipher;
	static int size_of_key;

	int* Decrypt(int cipher[], int key[]);
	int* Encrypt(int plain[], int key[]);
	int* Analyse3By3Key(int plaintext[], int ciphertext[]);
	int* Analyse(int plaintext[], int ciphertext[]);
	int* Analysis(int plaintext[], int ciphertext[], int size);
	int modInverse(int A, int M);
	int Calc_Det(string s, int n);
	

};
