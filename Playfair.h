#pragma once
//
// Created by Hajar on 10/21/2022.
//
#include <iostream>

#ifndef CRYPTOGRAPHY_PLAYFAIR_H
#define CRYPTOGRAPHY_PLAYFAIR_H



using namespace std;

string prepareKey(string key);

char** createKeySquare(string key);

string preparePlainText(string plainText);

bool isInTheSameRow(char firstLetter, char secondLetter, char** keySquare);

pair<char, char> encryptSameRow(char firstLetter, char secondLetter, char** keySquare);

bool isInTheSameCol(char firstLetter, char secondLetter, char** keySquare);

pair<char, char> encryptSameCol(char firstLetter, char secondLetter, char** keySquare);

pair<char, char> encryptDiagonal(char firstLetter, char secondLetter, char** keySquare);

pair<char, char> decryptSameRow(char firstLetter, char secondLetter, char** keySquare);

pair<char, char> decryptSameCol(char firstLetter, char secondLetter, char** keySquare);

pair<char, char> decryptDiagonal(char firstLetter, char secondLetter, char** keySquare);

string encrypt(string plainText, char** keySquare);

string decrypt(string cipherText, char** keySquare);

string playfairEncryption(string plainText, string key);

string playFairDecryption(string cipherText, string key);
#endif 