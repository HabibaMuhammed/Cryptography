#include "RailFence.h"
#include <cmath>
#include<String>
#include <algorithm>
using namespace std;
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

string Encrypt_RailFence(string plainText, int key)
{
    float tkey = key;
    string newPlainText = removeSpaces(plainText);
    // cout << newPlainText.length() << endl;
    float temp = float(newPlainText.length() / tkey);
    int columns = ceil(temp);
    int rows = key;
    int counter = 0;
    string cipherText = "";

    char** plain_arr = new char* [rows];

    for (int i = 0; i < rows; i++)
    {
        plain_arr[i] = new char[columns];

    }

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (counter == newPlainText.length())
            {
                plain_arr[j][i] = 'x';
                continue;

            }
            else
            {
                plain_arr[j][i] = newPlainText[counter];

                counter++;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)

            cipherText.push_back(plain_arr[i][j]);
    }
    return cipherText;
}

string Decrypt_RailFence(string cipherText, int key)
{
    int columns = cipherText.length() / key;
    int rows = key;
    int counter = 0;
    string plainText = "";

    char** cipher_arr = new char* [rows];

    for (int i = 0; i < rows; i++)
    {
        cipher_arr[i] = new char[columns];

    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {

            cipher_arr[i][j] = cipherText[counter];
            counter++;
        }
    }

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)

            plainText.push_back(cipher_arr[j][i]);
    }
    return plainText;
}

int Analyse(string plainText, string cipherText)
{

    int counter = 0;
    string encryptedText;

    for (int i = 1; i <= cipherText.length(); i++)
    {
        encryptedText = Encrypt_RailFence(plainText, i);
        if (encryptedText == cipherText)
        {
            counter = i;
            break;
        }
    }

    return counter;
}

