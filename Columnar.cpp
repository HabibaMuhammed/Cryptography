//
// Created by Hagar on 10/29/2022.
//

#include "columnar.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

string prepareText(string plainText) {
    string finalPlain;
    for (auto e : plainText) {
        if (e == ' ')
            continue;
        finalPlain += toupper(e);
    }
    return finalPlain;
}

char** fillRowByRow(string plainText, int rowsCnt, int colsCnt) {

    char** matrix = new char* [rowsCnt];
    for (int i = 0; i < rowsCnt; i++)
        matrix[i] = new char[colsCnt];

    int idx = 0;
    for (int i = 0; i < rowsCnt; i++) {
        for (int j = 0; j < colsCnt; j++) {
            if (idx < plainText.size()) {
                matrix[i][j] = plainText[idx];
                idx++;
            }
            else {
                matrix[i][j] = 'X';
            }
            //            if (rowsCnt == 4)
            //                cout << matrix[i][j];
        }
        //        cout << endl;
    }
    return matrix;
}

string readColbyCol(char** matrix, int row, int col, vector<int> key) {

    vector<string>s(col);

    for (int i = 0; i < col; i++) {
        string temp;
        for (int j = 0; j < row; j++) {
            temp += matrix[j][i];

        }
        s[key[i] - 1] = temp;

    }

    string ret;
    for (int i = 0; i < col; i++) {
        for (auto e : s[i])
            ret += e;
    }


    return ret;
}

string columnarEncrypt(string plainText, vector<int> key) {
    plainText = prepareText(plainText);
    int colsCnt = key.size();
    int rowsCnt = ((int)plainText.size() + colsCnt - 1) / colsCnt; // make sure

    char** encryptionMatrix = fillRowByRow(plainText, rowsCnt, colsCnt);
    string cipherText = readColbyCol(encryptionMatrix, rowsCnt, colsCnt, key);
    return cipherText;
}

string readRowbyRow(char** matrix, int rowsCnt, int colsCnt) {
    string ret;
    for (int i = 0; i < rowsCnt; i++) {
        for (int j = 0; j < colsCnt; j++) {
            //            cout << matrix[i][j];

            ret += matrix[i][j];
        }
        //        cout << endl;

    }


    return ret;
}

char** decryptionMatrix(string cipher, int rowsCnt, int colsCnt, vector<int> key) {
    vector<string>s(colsCnt);
    for (int i = 0, j = 0; i < cipher.size(); i += rowsCnt, j++) {
        s[j] = cipher.substr(i, rowsCnt);

    }

    char** matrix = new char* [rowsCnt];
    for (int i = 0; i < rowsCnt; i++)
        matrix[i] = new char[colsCnt];
    for (int i = 0; i < colsCnt; i++) {
        for (int j = 0; j < rowsCnt; j++) {
            matrix[j][i] = s[key[i] - 1][j];
        }
    }

    return matrix;

}

string columnarDecrypt(string cipherText, vector<int> key) {
    int colsCnt = key.size();
    int rowsCnt = (cipherText.size() + colsCnt - 1) / colsCnt; // make sure
    char** matrix = decryptionMatrix(cipherText, rowsCnt, colsCnt, key);
    string plain = readRowbyRow(matrix, rowsCnt, colsCnt);
    while (plain.back() == 'X')
        plain.pop_back();
    return plain;
}

vector<int> getKeys(char** matrix, string cipher, int rowsCnt, int colsCnt) {
    map<string, vector<int>> plainOrder;
    set<int> st;
    for (int i = 0; i < colsCnt; i++) {
        string temp;
        for (int j = 0; j < rowsCnt; j++) {
            temp += matrix[j][i];
        }
        plainOrder[temp].push_back(i);
    }
    vector<int> keys(colsCnt);
    int idx = 1;
    for (int i = 0; i < cipher.size(); i += rowsCnt) {
        string s = cipher.substr(i, rowsCnt);
        if (!plainOrder.count(s)) {
            return {};
        }
        if (plainOrder[s].empty())
            return {};
        keys[plainOrder[s].back()] = idx;
        st.insert(plainOrder[s].back());
        plainOrder[s].pop_back();
        idx++;
    }
    if (st.size() != colsCnt)
        return {};
    //    for (auto e:keys) {
    //        cout << e << " ";
    //    }
    //    cout << endl;
    return keys;
}

vector<int>  canalysis(string plainText, string ciphertext) {
    int len = ciphertext.size();
    plainText = prepareText(plainText);
    for (int col = 2; col <= 100; col++) {
        int row = (len + col - 1) / col;
        if (col * row < plainText.size())
            continue;
        char** encryptedMatrix = fillRowByRow(plainText, row, col);
        vector<int> key = getKeys(encryptedMatrix, ciphertext, row, col);

        if (key.size() && ciphertext == columnarEncrypt(plainText, key)) {
            return key;

        }
    }
    return {};
}