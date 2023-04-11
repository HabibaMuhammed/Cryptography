#ifndef CRYPTOGRAPHY_COLUMNAR_H
#define CRYPTOGRAPHY_COLUMNAR_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string prepareText(string plainText);

char** fillRowByRow(string plainText, int rowsCnt, int colsCnt);

string columnarEncrypt(string plainText, vector<int> key);

string readColbyCol(char** matrix, int row, int col, vector<int> key);

string columnarDecrypt(string cipherText, vector<int> key);

char** decryptionMatrix(string cipher, int rowsCnt, int colsCnt, vector<int> key);

vector<int> canalysis(string plainText, string ciphertext);

vector<int> getKeys(char** matrix, string cipher, int rowsCnt, int colsCnt);

#endif