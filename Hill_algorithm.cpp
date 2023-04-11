#include "Hill_Algorithm.h"
#include "InvalidAnalysisException.h"
#include <Eigen/Dense>
#include <list>
#include <iostream>
#include <algorithm>
#include<numeric>
#include<cmath>
using namespace std;
int hillgcd(int a, int b) {
	if (b == 0)
		return a;
	return hillgcd(b, a % b);
}
int* Hill_Algorithm::Encrypt(int plaintext[], int key[]) {
	int* cipher = new int[Hill_Algorithm::size_of_plain];
	int n = sqrt(Hill_Algorithm::size_of_key);
	Eigen::MatrixXd m(n, n);
	int counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m(i, j) = key[counter];
			cout << m(i, j) << " ";
			counter++;
		}
		cout << endl;
	}
	Eigen::VectorXd v(n);
	Eigen::VectorXd res(n);
	int plain_index = 0;
	int cipher_index = 0;
	int siz = Hill_Algorithm::size_of_plain / n;
	for (int j = 0; j < siz; j++) {

		for (int i = 0; i < n; i++) {
			v(i) = plaintext[plain_index];
			plain_index++;
		}
		
		res = m * v;


		for (int k = 0; k < n; k++) {
			int num = res(k);
			cipher[cipher_index] = num;

			cipher_index++;
		}


	}


	return cipher;
}
int Hill_Algorithm::modInverse(int A, int M)
{
	for (int X = 1; X < M; X++)
		if (((A % M) * (X % M)) % M == 1)
			return X;
}
int Hill_Algorithm::Calc_Det(string word, int n) {
	int det;
	int a2 = word.length();
	for (int i = 0; i < a2; i++) {


		int* arr3 = new int[a2];
		arr3[i] = word[i] - 97;

	}
	Eigen::MatrixXd m(n, n);
	int counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m(i, j) = word[counter];

			counter++;
		}

	}
	det = m.determinant();
	return det;
}
int* Hill_Algorithm::Analysis(int plaintext[], int ciphertext[], int size) {
	int* key = new int[Hill_Algorithm::size_of_key];
	int n = sqrt(Hill_Algorithm::size_of_key);
	Eigen::MatrixXd p(n, n);
	Eigen::MatrixXd c(n, n);
	Eigen::MatrixXd k(n, n);
	Eigen::MatrixXd k2(n, n);
	int counter = 0;
	// K = Pinv * C
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			p(i, j) = plaintext[counter];
			c(i, j) = ciphertext[counter];
			//cout << c(i, j) << " ";
			counter++;
		}
		//cout << endl;

	}

	int det = p.determinant();

	int det2 = det;
	if (det2 < 0) {
		while (det2 < 0) det2 = det2 + 26;
	}
	if (det == 0) {
		InvalidAnalysisException ex;
		cout << ex.what();
		throw ex;
	}

	p = p.inverse();
	int mod_inv = modInverse(det2, 26);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {



			double x = p(i, j);
			p(i, j) = (x * det * mod_inv);
			if (p(i, j) < 0) { while (p(i, j) < 0) p(i, j) += 26; }
			else {
				int y = p(i, j);

				p(i, j) = y % 26;
			}
			//	cout << p(i, j) << " ";


				//p(i, j) = x;


		}
		//cout << endl;
	}

	k = p * c;
	int cnt = 0;
	k2 = k.transpose();
	cout << "keymatix:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {


			double c = k2(i, j);
			key[cnt] = round(k2(i, j));
			key[cnt] %= 26;
			cout << key[cnt] << " ";
			cnt++;
		}
		cout << endl;
	}


	return key;
}

int* Hill_Algorithm::Analyse(int plaintext[], int ciphertext[]) {
	Hill_Algorithm::size_of_key = 4;
	int* key = new int[4];
	key = Analysis(plaintext, ciphertext, 4);
	return key;
}

int* Hill_Algorithm::Analyse3By3Key(int plaintext[], int ciphertext[]) {
	Hill_Algorithm::size_of_key = 9;
	int* key = new int[9];
	key = Analysis(plaintext, ciphertext, 9);
	return key;
}
int* Hill_Algorithm::Decrypt(int cipher[], int key[]) {
	int* plaintext = new int[Hill_Algorithm::size_of_cipher];
	int n = sqrt(Hill_Algorithm::size_of_key);
	Eigen::MatrixXd m(n, n);
	//Eigen::MatrixXd m2(n, n);
	cout << "keymatix: " << endl;
	int counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m(i, j) = key[counter];
			cout << m(i, j) << " ";
			counter++;
		}
		cout << endl;
	}
	int det = round(m.determinant());


	m = m.inverse();

	int mod_inv = modInverse(det, 26);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			cout << m(i, j) << " ";
			if (m(i, j) < 0) m(i, j) += 26;
			double x = m(i, j);
			m(i, j) = (x * det * mod_inv);


		}
		cout << endl;
	}


	Eigen::VectorXd v(n);
	Eigen::VectorXd res(n);
	int plain_index = 0;
	int cipher_index = 0;
	int siz = Hill_Algorithm::size_of_cipher / n;
	for (int j = 0; j < siz; j++) {

		for (int i = 0; i < n; i++) {
			v(i) = cipher[cipher_index];
			cipher_index++;
		}
		res = m * v;



		for (int k = 0; k < n; k++) {
			int num = res(k);


			plaintext[plain_index] = num;

			plain_index++;
		}


	}



	for (int i = 0; i < Hill_Algorithm::size_of_cipher; i++) {
		plaintext[i] = plaintext[i] % 26;
	}
	return plaintext;
}


