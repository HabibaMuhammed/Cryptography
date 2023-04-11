#include <iostream>
#include "playfair.h"

#include <map>


#define N 5

using namespace std;

string prepareKey(string key) {
    string finalKey = "";
    for (auto e : key) {
        if (e != ' ')
            finalKey += (toupper(e));
    }
    return finalKey;
}

char** createKeySquare(string key) {
    map<char, bool> isAddedBefore;
    int rowIdx = 0, colIdx = 0;

    char** keySquare = new char* [N];
    for (int i = 0; i < N; i++)
        keySquare[i] = new char[N];

    string alpha = "ABCDEDFGHIKLMNOPQRSTUVWXYZ";
    for (auto& e : key) {

        if (e == 'J')
            e = 'I';
        if (!isAddedBefore[e]) {
            isAddedBefore[e] = true;
            keySquare[rowIdx][colIdx] = e;
            colIdx = (colIdx + 1) % N;
            if (colIdx == 0)
                rowIdx++;


        }
    }

    for (auto e : alpha) {
        if (!isAddedBefore[e]) {

            isAddedBefore[e] = true;
            keySquare[rowIdx][colIdx] = e;
            colIdx = (colIdx + 1) % N;
            if (colIdx == 0)
                rowIdx++;
        }
    }
    return keySquare;

}

string preparePlainText(string plainText) {

    string finalPlainText, tempPlainText;
    for (auto e : plainText)
        if (e != ' ')
            tempPlainText += toupper(e);

    for (int i = 0; i < tempPlainText.size(); i++) {

        if (i + 1 < tempPlainText.size()) {
            if (tempPlainText[i] == tempPlainText[i + 1]) {
                finalPlainText += tempPlainText[i];
                finalPlainText += 'X';
            }
            else {
                finalPlainText += tempPlainText[i];
                finalPlainText += tempPlainText[i + 1];
                i++;
            }

        }
        else {
            finalPlainText += tempPlainText[i];
        }
    }
    for (auto& e : finalPlainText)
        if (e == 'J')
            e = 'I';

    if (finalPlainText.size() % 2)
        finalPlainText += 'X';
    return finalPlainText;
}

bool isInTheSameRow(char firstLetter, char secondLetter, char** keySquare) {

    for (int i = 0; i < N; i++) {
        int cnt = 0;
        for (int j = 0; j < N; j++) {
            if (keySquare[i][j] == firstLetter)
                cnt++;
            if (keySquare[i][j] == secondLetter)
                cnt++;
        }
        if (cnt == 2)
            return true;
    }
    return false;
}

pair<char, char> encryptSameRow(char firstLetter, char secondLetter, char** keySquare) {

    int row, firstIdx, secondIdx;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (firstLetter == keySquare[i][j])
                firstIdx = j;
            if (secondLetter == keySquare[i][j])
                secondIdx = j, row = i;

        }
    }
    firstLetter = keySquare[row][(firstIdx + 1) % N];
    secondLetter = keySquare[row][(secondIdx + 1) % N];


    return { firstLetter, secondLetter };

}

bool isInTheSameCol(char firstLetter, char secondLetter, char** keySquare) {
    for (int j = 0; j < N; j++) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (keySquare[i][j] == firstLetter)
                cnt++;
            if (keySquare[i][j] == secondLetter)
                cnt++;
        }
        if (cnt == 2)
            return true;
    }
    return false;
}

pair<char, char> encryptSameCol(char firstLetter, char secondLetter, char** keySquare) {

    int col, firstIdx, secondIdx;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (keySquare[i][j] == firstLetter)
                firstIdx = i;
            if (keySquare[i][j] == secondLetter)
                secondIdx = i, col = j;
        }
    }

    firstLetter = keySquare[(firstIdx + 1) % N][col];
    secondLetter = keySquare[(secondIdx + 1) % N][col];
    return { firstLetter, secondLetter };
}

pair<char, char> encryptDiagonal(char firstLetter, char secondLetter, char** keySquare) {
    int firstRow, firstCol, secondRow, secondCol;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (keySquare[i][j] == firstLetter)
                firstRow = i, firstCol = j;
            if (keySquare[i][j] == secondLetter)
                secondRow = i, secondCol = j;
        }
    }
    firstLetter = keySquare[firstRow][secondCol];
    secondLetter = keySquare[secondRow][firstCol];
    return { firstLetter, secondLetter };
}

pair<char, char> decryptSameRow(char firstLetter, char secondLetter, char** keySquare) {

    int row, firstIdx, secondIdx;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (firstLetter == keySquare[i][j])
                firstIdx = j;
            if (secondLetter == keySquare[i][j])
                secondIdx = j, row = i;

        }
    }
    firstLetter = keySquare[row][((firstIdx - 1) + N) % N];
    secondLetter = keySquare[row][((secondIdx - 1) + N) % N];


    return { firstLetter, secondLetter };

}

pair<char, char> decryptSameCol(char firstLetter, char secondLetter, char** keySquare) {

    int col, firstIdx, secondIdx;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (keySquare[i][j] == firstLetter)
                firstIdx = i;
            if (keySquare[i][j] == secondLetter)
                secondIdx = i, col = j;
        }
    }

    firstLetter = keySquare[((firstIdx - 1) + N) % N][col];
    secondLetter = keySquare[((secondIdx - 1) + N) % N][col];
    return { firstLetter, secondLetter };
}

pair<char, char> decryptDiagonal(char firstLetter, char secondLetter, char** keySquare) {
    int firstRow, firstCol, secondRow, secondCol;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (keySquare[i][j] == firstLetter)
                firstRow = i, firstCol = j;
            if (keySquare[i][j] == secondLetter)
                secondRow = i, secondCol = j;
        }
    }
    firstLetter = keySquare[firstRow][secondCol];
    secondLetter = keySquare[secondRow][firstCol];
    return { firstLetter, secondLetter };
}

string encrypt(string plainText, char** keySquare) {
    string cipher;

    for (int i = 0; i < plainText.size(); i += 2) {
        if (isInTheSameRow(plainText[i], plainText[i + 1], keySquare)) {
            pair<char, char> encryptedLetters = encryptSameRow(plainText[i], plainText[i + 1], keySquare);
            cipher += encryptedLetters.first;
            cipher += encryptedLetters.second;
        }
        else if (isInTheSameCol(plainText[i], plainText[i + 1], keySquare)) {
            pair<char, char> encryptedLetters = encryptSameCol(plainText[i], plainText[i + 1], keySquare);
            cipher += encryptedLetters.first;
            cipher += encryptedLetters.second;
        }
        else {
            pair<char, char> encryptedLetters = encryptDiagonal(plainText[i], plainText[i + 1], keySquare);
            cipher += encryptedLetters.first;
            cipher += encryptedLetters.second;
        }

    }
    return cipher;
}

string decrypt(string cipherText, char** keySquare) {
    string plainText;
    for (int i = 0; i < cipherText.size(); i += 2) {
        if (isInTheSameRow(cipherText[i], cipherText[i + 1], keySquare)) {
            pair<char, char> encryptedLetters = decryptSameRow(cipherText[i], cipherText[i + 1], keySquare);
            plainText += encryptedLetters.first;
            plainText += encryptedLetters.second;

        }
        else if (isInTheSameCol(cipherText[i], cipherText[i + 1], keySquare)) {
            pair<char, char> encryptedLetters = decryptSameCol(cipherText[i], cipherText[i + 1], keySquare);
            plainText += encryptedLetters.first;
            plainText += encryptedLetters.second;
        }
        else {
            pair<char, char> encryptedLetters = decryptDiagonal(cipherText[i], cipherText[i + 1], keySquare);
            plainText += encryptedLetters.first;
            plainText += encryptedLetters.second;
        }
    }
    return plainText;
}

string playfairEncryption(string plainText, string key) {
    key = prepareKey(key);
    plainText = preparePlainText(plainText);
    char** keySquare = createKeySquare(key);
    string cipher = encrypt(plainText, keySquare);
    return cipher;



}


string playFairDecryption(string cipherText, string key) {
    key = prepareKey(key);
    char** keySquare = createKeySquare(key);
    string plain = decrypt(cipherText, keySquare);
    return plain;
}