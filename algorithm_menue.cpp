
#include <iostream>
#include <string>
#include <vector>
#include <memory.h>
#include <sstream>
#include <iomanip>
#include "Ceaser.h"
#include "algorithm_menue.h"
#include "Monoalphabtic.h"
#include "Playfair.h"
#include "RSA.h"
#include "MD5.H"
#include "AES.h"
#include "AutoKey.h"
#include "RepeatedKey.h"
#include "RailFence.h"
#include "Columnar.h"
#include "DES.h"
#include "Hill_algorithm.h"
/*#include "AutoKey.cpp"
#include "Ceaser.cpp"
#include "Monoalphabtic.cpp"
#include "Playfair.cpp"
#include "RSA.cpp"
#include "MD5.cpp"
#include "AES.cpp"
#include "RepeatedKey.cpp"
#include "RailFence.cpp"
#include "Columnar.cpp"
#include "DES.cpp"
*/
int Hill_Algorithm::size_of_cipher = 0;
int Hill_Algorithm::size_of_plain = 0;
int Hill_Algorithm::size_of_key = 0;
using namespace std;
vector<string> v{ {"encryption"}, {"decryption"}, {"analysis"}, {"quit"} };
uint8_t** roundarray = new uint8_t * [4];
uint8_t** roundarray2 = new uint8_t * [4];
uint8_t subkeys[12][4][4];
vector<uint8_t> sub;
string T2_DES::sub[16] = {};

T2_DES des;
int ch = 0;
void start1()
{
    puts("*******************************************************");
    cout << "what do you want to make?" << endl;
    cout << "1-encryption" << endl;
    cout << "2-decryption" << endl;
    cout << "0-Quit" << endl;
    puts("*******************************************************");
    cout << "Please enter your choice" << endl;
}

void start2()
{
    puts("*******************************************************");
    cout << "what do you want to make ?" << endl;
    for (int i = 0; i < v.size(); i++)
    {
        if (i == 3)
        {
            cout << 0 << "->" << v[i] << endl;
            break;
        }
        cout << i + 1 << "->" << v[i] << endl;
    }
    puts("*******************************************************");
    cout << "Please enter your choice" << endl;
}
void CeaserEncryption()
{
    string plaintext;

    int enckey;
    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    //cin >> plaintext;
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());

    int valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < plaintext.length(); i++) {
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                plaintext[i] = tolower(plaintext[i]);
            }
            else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                plaintext[i] = plaintext[i];
            }

            else {

                cout << "Invalid plaintext" << endl;
                cout << "Please Enter plaintext : " << endl;
                cin >> plaintext;
                valid = 0;

            }

        }
    } while (valid == 0);


    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
            cout << "Enter the required Key: " << endl;
            cin >> enckey;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);

    int valid_key = 1;
    do {
        valid_key = 1;



        if (enckey <= 0 || enckey >= 26)
        {
            valid_key = 0;
            cout << "Enter the required Key: ";
            cin >> enckey;


        }
    } while (valid_key == 0);
    Encrypt_Caesar(plaintext, enckey);
    cout << "The ciphertext is: " << Encrypt_Caesar(plaintext, enckey) << endl;
    cout << "------------------" << endl;
}

void CeaserDecryption()
{
    string ciphertext;

    int deckey;
    cout << "Enter the cipher : ";
    cin.ignore();
    getline(cin, ciphertext);
    ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace),
        ciphertext.end());
    int valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < ciphertext.length(); i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                ciphertext[i] = tolower(ciphertext[i]);
            }
            else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                ciphertext[i] = ciphertext[i];
            }
            else {

                cout << "Invalid ciphertext" << endl;
                cout << "Please Enter ciphertext : " << endl;
                cin >> ciphertext;
                valid = 0;

            }

        }
    } while (valid == 0);


    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
            cout << "PLEASE INSERT VALUE:" << endl;
            cin >> deckey;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);

    int valid_key = 1;
    do {
        valid_key = 1;


        if (deckey <= 0 || deckey >= 26)
        {
            valid_key = 0;
            cout << "Enter the required Key: ";
            cin >> deckey;

        }
    } while (valid_key == 0);
    Decrypt_Caesar(ciphertext, deckey);
    cout << "The Decrypted text is: " << Decrypt_Caesar(ciphertext, deckey) << endl;
    cout << "------------------" << endl;
}

void CeaserAnalyzer()
{
    string ciphertext, plaintext;

    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    //cin >> plaintext;
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());

    int valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < plaintext.length(); i++) {
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                plaintext[i] = tolower(plaintext[i]);
            }
            else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                plaintext[i] = plaintext[i];
            }

            else {

                cout << "Invalid plaintext" << endl;
                cout << "Please Enter plaintext : " << endl;
                cin >> plaintext;
                valid = 0;

            }

        }
    } while (valid == 0);
    cout << "Enter the ciphertext: ";


    getline(cin, ciphertext);
    ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace),
        ciphertext.end());
    valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < ciphertext.length(); i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                ciphertext[i] = tolower(ciphertext[i]);
            }
            else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                ciphertext[i] = ciphertext[i];
            }
            else {

                cout << "Invalid ciphertext" << endl;
                cout << "Please Enter ciphertext : " << endl;
                cin >> ciphertext;
                valid = 0;

            }

        }
    } while (valid == 0);

    cout << "The key is: " << Analyze(plaintext, ciphertext) << endl;
    cout << "------------------" << endl;
}
void CeaserAlgo()
{
    cout << "CEASER ALGO" << endl;
    start2();
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> ch;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (ch)
    {
    case 1:
    {
        CeaserEncryption();

        break;
    }
    case 2:
    {
        CeaserDecryption();
        break;
    }
    case 3:
    {
        CeaserAnalyzer();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void EncryptionMonoalphabetic()
{
    string plaintext, enckey;

    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    //cin >> plaintext;
    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = tolower(plaintext[i]);
        }
    }
    cout << "Enter the used Key: ";
    cin >> enckey;
    enckey.erase(std::remove_if(enckey.begin(), enckey.end(), ::isspace),
        enckey.end());
    while (enckey.length() != 26) {


        cout << "Invalid key length , must be 26" << endl;
        cout << "Please Enter key  : " << endl;
        cin >> enckey;


    }

    //cin >> plaintext;


    int valid = 1;
    do {
        valid = 1;

        for (int i = 0; i < enckey.length(); i++) {

            if (enckey[i] >= 'A' && enckey[i] <= 'Z') {
                enckey[i] = tolower(enckey[i]);
            }
            else if (enckey[i] >= 'a' && enckey[i] <= 'z') {
                enckey[i] = enckey[i];
            }

            else {

                cout << "Invalid key" << endl;
                cout << "Please Enter key  : " << endl;
                cin >> enckey;
                valid = 0;

            }

        }
    } while (valid == 0);

    cout << "The CipherText is: " << Encrypt_Method2(plaintext, enckey) << endl;
    cout << "------------------" << endl;
}

void DecryptionMonoalphabetic()
{
    string deckey, ciphertext;

    cout << "Enter the ciphertext: ";
    cin.ignore();
    getline(cin, ciphertext);
    //cin >> plaintext;

    for (int i = 0; i < ciphertext.length(); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            ciphertext[i] = tolower(ciphertext[i]);
        }
    }
    cout << "Enter the used Key: ";
    cin >> deckey;
    deckey.erase(std::remove_if(deckey.begin(), deckey.end(), ::isspace),
        deckey.end());
    while (deckey.length() != 26) {


        cout << "Invalid key length , must be 26" << endl;
        cout << "Please Enter key  : " << endl;
        cin >> deckey;


    }

    //cin >> plaintext;


    int valid = 1;
    do {
        valid = 1;

        for (int i = 0; i < deckey.length(); i++) {

            if (deckey[i] >= 'A' && deckey[i] <= 'Z') {
                deckey[i] = tolower(deckey[i]);
            }
            else if (deckey[i] >= 'a' && deckey[i] <= 'z') {
                deckey[i] = deckey[i];
            }

            else {

                cout << "Invalid key" << endl;
                cout << "Please Enter key  : " << endl;
                cin >> deckey;
                valid = 0;

            }

        }
    } while (valid == 0);
    cout << "The Decrypted CipherText is: " << Decrypt_Method2(ciphertext, deckey) << endl;
    cout << "------------------" << endl;
}
void Analyze_Frequency()
{
    string ciphertext;

    cout << "Enter the cipher text";
    cin.ignore();
    getline(cin, ciphertext);
    cout << "The frequency analysis is : \n";
    string plain = AnalyzeUsingCharFrequency(ciphertext);
    cout << "plain text based on frequency analysis is close to "
        << "\n";
    cout << plain;

    cout << endl;
}

void MonoalphabticAlgo()
{
    cout << "mono ALGO" << endl;

    start2();
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> ch;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (ch)
    {
    case 1:
    {
        EncryptionMonoalphabetic();

        break;
    }
    case 2:
    {
        DecryptionMonoalphabetic();
        break;
    }
    case 3:
    {
        Analyze_Frequency();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void Playfair_encryption()
{
    string plain, key;
    cout << "Please enter the plain text";
    // cout<<"press 0 quit"<<endl;
    cin.ignore();
    getline(cin, plain);
    cout << "Please enter the key";
    cin >> key;
    string cipher = playfairEncryption(plain, key);

    cout << "Cipher: " << cipher << endl;
}
void Playfair_decryption()
{
    string cipher, key;
    cout << "Please enter the cipher text";
    // cout<<"press 0 quit"<<endl;
    cin.ignore();
    getline(cin, cipher);
    cout << "Please enter the key";
    cin >> key;
    string plainTany = playFairDecryption(cipher, key);
    // cout << "Plain: " << plain << endl;
    cout << "Decrypted Plain: " << plainTany << endl;
    cout << "------------------" << endl;
}
void PlayfairAlgo()
{
    cout << "play Algo" << endl;
    start1();
    int ch = 1;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> ch;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);

    switch (ch)
    {
    case 1:
    {

        Playfair_encryption();

        break;
    }
    case 2:
    {
        Playfair_decryption();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void RSA_Encryption()
{
    int a;
    int b;
    int c;
    int d;
    cout << "Please enter the value of p : ";
    cin >> a;
    cout << "Please enter the value of q : ";
    cin >> b;
    cout << "Please enter the plain text : ";
    cin >> c;
    cout << "Please enter the value of e (public key): ";
    cin >> d;

    int enc;
    enc = rsaEncrypt(a, b, c, d);
    cout << "Encrypted message = " << enc << endl;
}
void RSA_Decryption()
{
    int a;
    int b;
    int c;
    int d;
    cout << "Please enter the value of p : ";
    cin >> a;
    cout << "Please enter the value of q : ";
    cin >> b;
    cout << "Please enter the cipher text : ";
    cin >> c;
    cout << "Please enter the value of e (public key): ";
    cin >> d;

    int dec;
    dec = rsaDecrypt(a, b, c, d);
    cout << "Decrypted message = " << dec << endl;
}
void RSAAlgo()
{
    int choice;
    cout << "RSA Algo" << endl;

    start1();
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> choice;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (choice)
    {
    case 1:
    {

        RSA_Encryption();

        break;
    }
    case 2:
    {
        RSA_Decryption();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void AES_Encryption()
{
    string p;
    string k;
    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, p);
    //cin >> plaintext;
    p.erase(std::remove_if(p.begin(), p.end(), ::isspace),
        p.end());
 

    int valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < p.length(); i++) {
            if (p[i] >= 'a' && p[i] <= 'f') {
                p[i] = p[i];
            }
            else if (p[i] >= '0' && p[i] <= '9') {
                p[i] = p[i];
            }
            else if (p[i] >= 'A' && p[i] <= 'F') {
                p[i] = p[i];
            }
            else if (p[i] == 'x') {
                p[i] = p[i];
            }

            else {

                cout << "Invalid plaintext " << endl;
                cout << "Plaintext must be in hexadecimal form 0x(A-F||0-9)" << endl;
                cout << "Please Enter plaintext : " << endl;
                cin >> p;
                valid = 0;

            }

        }
    } while (valid == 0);

     valid = 1;
    do {
        valid = 1;
        if (p.length() != 34) {
            cout << "Invalid plaintext" << endl;
            cout << "Plaintext must be of size 32 hexa digits" << endl;
            cout << "Please Enter plaintext : " << endl;
            cin >> p;
            valid = 0;
        
        }

    } while (valid == 0);

    cout << "Please enter the key : ";
    cin >> k;
    k.erase(std::remove_if(k.begin(), k.end(), ::isspace),
        k.end());


     valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < k.length(); i++) {
            if (k[i] >= 'a' && k[i] <= 'f') {
                k[i] = k[i];
            }
            else if (k[i] >= '0' && k[i] <= '9') {
                k[i] = k[i];
            }
            else if (k[i] >= 'A' && k[i] <= 'F') {
                k[i] = k[i];
            }
            else if (k[i] == 'x') {
                k[i] = k[i];
            }

            else {

                cout << "Invalid key " << endl;
                cout << "Key must be in hexadecimal form 0x(A-F||0-9)" << endl;
                cout << "Please Enter key : " << endl;
                cin >> k;
                valid = 0;

            }

        }
    } while (valid == 0);

    valid = 1;
    do {
        valid = 1;
        if (k.length() != 34) {
            cout << "Invalid Key" << endl;
            cout << "Key must be of size 32 hexa digits" << endl;
            cout << "Please Enter key : " << endl;
            cin >> k;
            valid = 0;

        }

    } while (valid == 0);

    roundarray = AES_Encrypt(p, k);
    cout << "Cipher text is : ";
    stringstream ss;
    string s;
    ss << "0x";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            ss << hex << (int)roundarray[j][i];
            s = ss.str();
            ss.str("");
            if (s.size() == 1)
                cout << "0" << s;
            else
                cout << s;
        }
    }
}
void AES_Decryption()
{
    string cip;
    string k2;
    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, cip);
    //cin >> plaintext;
    cip.erase(std::remove_if(cip.begin(), cip.end(), ::isspace),
        cip.end());


    int valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < cip.length(); i++) {
            if (cip[i] >= 'a' && cip[i] <= 'f') {
                cip[i] = cip[i];
            }
            else if (cip[i] >= '0' && cip[i] <= '9') {
                cip[i] = cip[i];
            }
            else if (cip[i] >= 'A' && cip[i] <= 'F') {
                cip[i] = cip[i];
            }
            else if (cip[i] == 'x') {
                cip[i] = cip[i];
            }

            else {

                cout << "Invalid ciphertext " << endl;
                cout << "Ciphertext must be in hexadecimal form 0x(A-F||0-9)" << endl;
                cout << "Please Enter ciphertext : " << endl;
                cin >> cip;
                valid = 0;

            }

        }
    } while (valid == 0);

    valid = 1;
    do {
        valid = 1;
        if (cip.length() != 34) {
            cout << "Invalid ciphertext" << endl;
            cout << "Ciphertext must be of size 32 hexa digits" << endl;
            cout << "Please Enter ciphertext : " << endl;
            cin >> cip;
            valid = 0;

        }

    } while (valid == 0);

    cout << "Please enter the key : ";
    cin >> k2;
    k2.erase(std::remove_if(k2.begin(), k2.end(), ::isspace),
        k2.end());


     valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < k2.length(); i++) {
            if (k2[i] >= 'a' && k2[i] <= 'f') {
                k2[i] = k2[i];
            }
            else if (k2[i] >= '0' && k2[i] <= '9') {
                k2[i] = k2[i];
            }
            else if (k2[i] >= 'A' && k2[i] <= 'F') {
                k2[i] = k2[i];
            }
            else if (k2[i] == 'x') {
                k2[i] = k2[i];
            }

            else {

                cout << "Invalid key " << endl;
                cout << "Key must be in hexadecimal form 0x(A-F||0-9)" << endl;
                cout << "Please Enter key : " << endl;
                cin >> k2;
                valid = 0;

            }

        }
    } while (valid == 0);

    valid = 1;
    do {
        valid = 1;
        if (k2.length() != 34) {
            cout << "Invalid Key" << endl;
            cout << "Key must be of size 32 hexa digits" << endl;
            cout << "Please Enter key : " << endl;
            cin >> k2;
            valid = 0;

        }

    } while (valid == 0);

    roundarray2 = AES_Decrypt(cip, k2);

    stringstream ss;
    ss << "0x";
    string s;
    cout << "Plain text is : ";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ss << hex << (int)roundarray2[j][i];
            s = ss.str();
            ss.str("");
            if (s.size() == 1)
                cout << "0" << s;
            else
                cout << s;
        }
    }
}
void AESAlgo()
{
    int choice;
    cout << "AES Algo" << endl;
    start1();

    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> choice;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (choice)
    {
    case 1:
    {

        AES_Encryption();

        break;
    }
    case 2:
    {
        AES_Decryption();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void MD5Algo()
{
    cout << "MD5 Algo" << endl;
    cout << "Please enter a string" << endl;
    string s;

    getline(cin, s);
    string hashtext;
    hashtext = MD5(s);
    cout << "HASHED text :" << hashtext;
}
void Repeatedkey_Encryption()
{
    int valid = 1;
    string plaintext, enckey;

    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());
    //cin >> plaintext;
    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = tolower(plaintext[i]);
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = plaintext[i];
        }

        else {

            cout << "Invalid plaintext" << endl;
            cout << "Please Enter a valid plaintext  : " << endl;
            cin >> plaintext;
            valid = 0;

        }
    }
    cout << "Enter the used Key: ";
    cin >> enckey;
    enckey.erase(std::remove_if(enckey.begin(), enckey.end(), ::isspace),
        enckey.end());


    //cin >> plaintext;


    valid = 1;
    do {
        valid = 1;

        for (int i = 0; i < enckey.length(); i++) {

            if (enckey[i] >= 'A' && enckey[i] <= 'Z') {
                enckey[i] = tolower(enckey[i]);
            }
            else if (enckey[i] >= 'a' && enckey[i] <= 'z') {
                enckey[i] = enckey[i];
            }

            else {

                cout << "Invalid key" << endl;
                cout << "Please Enter a valid key  : " << endl;
                cin >> enckey;
                valid = 0;

            }

        }
    } while (valid == 0);


   
    cout << rkencryption(plaintext, enckey);
}
void Repeatedkey_Decryption()
{
    string cipher_text, Dec_key;

    int valid = 1;


    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, cipher_text);
    cipher_text.erase(std::remove_if(cipher_text.begin(), cipher_text.end(), ::isspace),
        cipher_text.end());
    //cin >> plaintext;
    for (int i = 0; i < cipher_text.length(); i++) {
        if (cipher_text[i] >= 'A' && cipher_text[i] <= 'Z') {
            cipher_text[i] = tolower(cipher_text[i]);
        }
        else if (cipher_text[i] >= 'a' && cipher_text[i] <= 'z') {
            cipher_text[i] = cipher_text[i];
        }

        else {

            cout << "Invalid ciphertext" << endl;
            cout << "Please Enter a valid ciphertext  : " << endl;
            cin >> cipher_text;
            valid = 0;

        }
    }
    cout << "Enter the used Key: ";
    cin >> Dec_key;
    Dec_key.erase(std::remove_if(Dec_key.begin(), Dec_key.end(), ::isspace),
        Dec_key.end());


    //cin >> plaintext;


    valid = 1;
    do {
        valid = 1;

        for (int i = 0; i < Dec_key.length(); i++) {

            if (Dec_key[i] >= 'A' && Dec_key[i] <= 'Z') {
                Dec_key[i] = tolower(Dec_key[i]);
            }
            else if (Dec_key[i] >= 'a' && Dec_key[i] <= 'z') {
                Dec_key[i] = Dec_key[i];
            }

            else {

                cout << "Invalid key" << endl;
                cout << "Please Enter a valid key  : " << endl;
                cin >> Dec_key;
                valid = 0;

            }

        }
    } while (valid == 0);
    
    cout << rkdecryption(cipher_text, Dec_key);
}
void Repeatedkey_Analysis()
{
    int valid = 1;
    string plaintext, ciphertext;

    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());
    //cin >> plaintext;
    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = tolower(plaintext[i]);
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = plaintext[i];
        }

        else {

            cout << "Invalid plaintext" << endl;
            cout << "Please Enter a valid plaintext  : " << endl;
            cin >> plaintext;
            valid = 0;

        }
    }


    cout << "Enter the ciphertext: ";
    cin.ignore();
    getline(cin, ciphertext);
    ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace),
        ciphertext.end());
    //cin >> plaintext;
    for (int i = 0; i < ciphertext.length(); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            ciphertext[i] = tolower(ciphertext[i]);
        }
        else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            ciphertext[i] = ciphertext[i];
        }

        else {

            cout << "Invalid ciphertext" << endl;
            cout << "Please Enter a valid ciphertext  : " << endl;
            cin >> ciphertext;
            valid = 0;

        }
    }

    
    cout << rkAnalyze(plaintext, ciphertext);
}
void RepeatedkeyAlgo()
{
    cout << "REPEATED KEY Algo" << endl;
    start2();
    int num = 0;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> num;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (num)
    {
    case 1:
    {
        Repeatedkey_Encryption();
        break;
    }
    case 2:
    {
        Repeatedkey_Decryption();
        break;
    }
    case 3:
    {
        Repeatedkey_Analysis();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void Autokey_Encryption()
{
    int valid = 1;
    string plaintext, enckey;

    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());
    //cin >> plaintext;
    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = tolower(plaintext[i]);
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = plaintext[i];
        }

        else {

            cout << "Invalid plaintext" << endl;
            cout << "Please Enter a valid plaintext  : " << endl;
            cin >> plaintext;
            valid = 0;

        }
    }
    cout << "Enter the used Key: ";
    cin >> enckey;
    enckey.erase(std::remove_if(enckey.begin(), enckey.end(), ::isspace),
        enckey.end());


    //cin >> plaintext;


    valid = 1;
    do {
        valid = 1;

        for (int i = 0; i < enckey.length(); i++) {

            if (enckey[i] >= 'A' && enckey[i] <= 'Z') {
                enckey[i] = tolower(enckey[i]);
            }
            else if (enckey[i] >= 'a' && enckey[i] <= 'z') {
                enckey[i] = enckey[i];
            }

            else {

                cout << "Invalid key" << endl;
                cout << "Please Enter a valid key  : " << endl;
                cin >> enckey;
                valid = 0;

            }

        }
    } while (valid == 0);
    cout << "The encryption is: " << AKEncrypt(plaintext, enckey);
}
void Autokey_Decryption()
{
    string cipher_text, Dec_key;

    int valid = 1;


    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, cipher_text);
    cipher_text.erase(std::remove_if(cipher_text.begin(), cipher_text.end(), ::isspace),
        cipher_text.end());
    //cin >> plaintext;
    for (int i = 0; i < cipher_text.length(); i++) {
        if (cipher_text[i] >= 'A' && cipher_text[i] <= 'Z') {
            cipher_text[i] = tolower(cipher_text[i]);
        }
        else if (cipher_text[i] >= 'a' && cipher_text[i] <= 'z') {
            cipher_text[i] = cipher_text[i];
        }

        else {

            cout << "Invalid ciphertext" << endl;
            cout << "Please Enter a valid ciphertext  : " << endl;
            cin >> cipher_text;
            valid = 0;

        }
    }
    cout << "Enter the used Key: ";
    cin >> Dec_key;
    Dec_key.erase(std::remove_if(Dec_key.begin(), Dec_key.end(), ::isspace),
        Dec_key.end());


    //cin >> plaintext;


    valid = 1;
    do {
        valid = 1;

        for (int i = 0; i < Dec_key.length(); i++) {

            if (Dec_key[i] >= 'A' && Dec_key[i] <= 'Z') {
                Dec_key[i] = tolower(Dec_key[i]);
            }
            else if (Dec_key[i] >= 'a' && Dec_key[i] <= 'z') {
                Dec_key[i] = Dec_key[i];
            }

            else {

                cout << "Invalid key" << endl;
                cout << "Please Enter a valid key  : " << endl;
                cin >> Dec_key;
                valid = 0;

            }

        }
    } while (valid == 0);
    cout << "Decryption is :" << AKDecrypt(cipher_text, Dec_key);
}
void Autokey_Analysis()
{
    int valid = 1;
    string plaintext, ciphertext;

    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());
    //cin >> plaintext;
    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = tolower(plaintext[i]);
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = plaintext[i];
        }

        else {

            cout << "Invalid plaintext" << endl;
            cout << "Please Enter a valid plaintext  : " << endl;
            cin >> plaintext;
            valid = 0;

        }
    }


    cout << "Enter the ciphertext: ";
    cin.ignore();
    getline(cin, ciphertext);
    ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace),
        ciphertext.end());
    //cin >> plaintext;
    for (int i = 0; i < ciphertext.length(); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            ciphertext[i] = tolower(ciphertext[i]);
        }
        else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            ciphertext[i] = ciphertext[i];
        }

        else {

            cout << "Invalid ciphertext" << endl;
            cout << "Please Enter a valid ciphertext  : " << endl;
            cin >> ciphertext;
            valid = 0;

        }
    }
    cout << AKAnalyzeAutoKey(plaintext, ciphertext) << endl;
}
void AutokeyAlgo()
{
    cout << "AUTO KEY Algo" << endl;
    start2();
    int num = 1;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> num;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (num)
    {
    case 1:
    {
        Autokey_Encryption();
        break;
    }
    case 2:
    {
        Autokey_Decryption();
        break;
    }
    case 3:
    {
        Autokey_Analysis();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void RailFence_Encryption()
{
    string plaintext;
    int key3;
    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    //cin >> plaintext;
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());

    int valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < plaintext.length(); i++) {
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
                plaintext[i] = tolower(plaintext[i]);
            }
            else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
                plaintext[i] = plaintext[i];
            }

            else {

                cout << "Invalid plaintext" << endl;
                cout << "Please Enter plaintext : " << endl;
                cin >> plaintext;
                valid = 0;

            }

        }
    } while (valid == 0);

    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
            cout << "Enter the required Key: " << endl;
            cin >> key3;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);

    int valid_key = 1;
    do {
        valid_key = 1;



        if (key3 < 1 || key3 > plaintext.length())
        {
            valid_key = 0;
            cout << "Invalid Key: \n";
            cout << "Enter the required Key: ";
            cin >> key3;


        }
    } while (valid_key == 0);
    cout << "The encryption is: " << Encrypt_RailFence(plaintext, key3);
}
void RailFence_Decryption()
{
    string ciphertext;
    int key3;

    cout << "Enter the ciphertext : ";
    cin.ignore();
    getline(cin, ciphertext);
    //cin >> plaintext;
    ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace),
        ciphertext.end());

    int valid = 1;
    do {
        valid = 1;
        for (int i = 0; i < ciphertext.length(); i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                ciphertext[i] = tolower(ciphertext[i]);
            }
            else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                ciphertext[i] = ciphertext[i];
            }

            else {

                cout << "Invalid ciphertext" << endl;
                cout << "Please Enter ciphertext : " << endl;
                cin >> ciphertext;
                valid = 0;

            }

        }
    } while (valid == 0);

    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {
            cout << "Enter the required Key: " << endl;
            cin >> key3;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);

    int valid_key = 1;
    do {
        valid_key = 1;



        if (key3 < 1 || key3 > ciphertext.length())
        {
            valid_key = 0;
            cout << "Invalid Key: \n";
            cout << "Enter the required Key: ";
            cin >> key3;


        }
    } while (valid_key == 0);
    cout << Decrypt_RailFence(ciphertext, key3);
}
void RailFence_Analysis()
{
    int valid = 1;
    string plaintext, ciphertext;

    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plaintext);
    plaintext.erase(std::remove_if(plaintext.begin(), plaintext.end(), ::isspace),
        plaintext.end());
    //cin >> plaintext;
    for (int i = 0; i < plaintext.length(); i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = tolower(plaintext[i]);
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = plaintext[i];
        }

        else {

            cout << "Invalid plaintext" << endl;
            cout << "Please Enter a valid plaintext  : " << endl;
            cin >> plaintext;
            valid = 0;

        }
    }


    cout << "Enter the ciphertext: ";
    cin.ignore();
    getline(cin, ciphertext);
    ciphertext.erase(std::remove_if(ciphertext.begin(), ciphertext.end(), ::isspace),
        ciphertext.end());
    //cin >> plaintext;
    for (int i = 0; i < ciphertext.length(); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            ciphertext[i] = tolower(ciphertext[i]);
        }
        else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            ciphertext[i] = ciphertext[i];
        }

        else {

            cout << "Invalid ciphertext" << endl;
            cout << "Please Enter a valid ciphertext  : " << endl;
            cin >> ciphertext;
            valid = 0;

        }
    }
    cout << "The Key Depth is: " << Analyse(plaintext, ciphertext) << endl;
}
void RailFenceAlgo()
{
    cout << "Rail Fence Algo" << endl;
    start2();
    int num = 1;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> num;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (num)
    {
    case 1:
    {
        RailFence_Encryption();
        break;
    }
    case 2:
    {
        RailFence_Decryption();
        break;
    }
    case 3:
    {
        RailFence_Analysis();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void Columnar_Encryption()
{
    string plaintext;
    cout << "enter plain text" << endl;
    cin >> plaintext;
    cout << "please enter key : " << endl;
    string k;
    cin.ignore();
    getline(cin, k);
    k.erase(std::remove_if(k.begin(), k.end(), ::isspace),
        k.end());

    vector<int> key;
    for (int i = 0; i < k.length(); i++)
    {
        int c;
        c = k[i] - '0';
        key.push_back(c);
    }

    string s = columnarEncrypt(plaintext, key);
    cout << "ciphertext: " << s << endl;
}
void Columnar_Decryption()
{

    string ciphertext;
    cout << "enter cipher text" << endl;
    cin >> ciphertext;
    cout << "please enter size of key list" << endl;
    int ks;
    cin >> ks;
    vector<int> key;
    for (int i = 0; i < ks; i++)
    {
        int c;
        cin >> c;
        key.push_back(c);
    }
    string plain = columnarDecrypt(ciphertext, key);
    cout << "plaintext: " << plain << endl;
}
void Columnar_Analysis()
{
    string plaintext;
    cout << "enter plain text" << endl;
    cin >> plaintext;
    string ciphertext;
    cout << "enter cipher text" << endl;
    cin >> ciphertext;

    vector<int> vec = canalysis(plaintext, ciphertext);
    //cout<<vec.size();
    for (auto e : vec)
    {
        cout << e << " ";
    }
    cout << endl;
}
void ColumnarAlgo()
{

    cout << "Columnar Algo" << endl;
    start2();
    int num = 1;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> num;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    switch (num)
    {
    case 1:
    {
        Columnar_Encryption();
        break;
    }
    case 2:
    {
        Columnar_Decryption();
        break;
    }
    case 3:
    {
        Columnar_Analysis();
        break;
    }
    case 0:
    {
        return;
    }
    }
}
void DES_keygeneration()
{
    string key[16];

    string key_DES;
    cout << "Enter the key :" << endl;
    
    int valid_key = 1;
    /*
    do {
        valid_key = 1;



        if (key_DES.length() != 8)
        {
            valid_key = 0;
            cout << "Invalid Key: \n";
            cout << "Enter the required Key: ";
            cin >> key_DES;


        }
    } while (valid_key == 0);
    
    */
    //key_bin = des.Plain_Bin(key_DES);
    string key_bin;
    cin >> key_bin;

    des.key_generation(key_bin);
}
void DES_encryption()
{
    string plain = "";
    string binary = "";
    cout << "Enter Plaintext ";

    //cin.ignore();
    //getline(cin, plain);
    cin >> binary;
    /*new 
    int rem = 0;
    rem = plain.size() % 8; 
    if (rem != 0)
    {
        rem = 8 - rem;
        for (int i = 0; i < rem; i++)
        {
            plain += 'X';
        }
    }
    new */
    // cout << plain<<endl;
    // new binary = des.Plain_Bin(plain);
    // cout <<"Plain :" << binary << endl;
    
    int num_blocks = binary.size() / 64;
    int index = 0;
    cout << "Encrypted : ";
    for (int i = 0; i < num_blocks; i++)
    {
        string current = "";
        current = binary.substr(index, 64);
        index += 64;
        string cipher;
        cipher = des.Encrypt_DES(current, des.sub);
        cout << cipher;
    }
    cout << endl;
}
void DES_decryption()
{
    string ciphertext;
    string decrypted;
    cout << "Enter the cipher: ";
    cin.ignore();

    getline(cin, ciphertext);

    string bin_cipher = "";
    bin_cipher = des.Plain_Bin(ciphertext);

    //cout << bin_cipher << endl;

    int num_blocks_2 = bin_cipher.size() / 64;
    cout << num_blocks_2 << endl;
    int index_2 = 0;
    for (int i = 0; i < num_blocks_2; i++)
    {
        string current_2 = "";
        current_2 = bin_cipher.substr(index_2, 64);
        index_2 += 64;
        string plain_dec = des.Decrypt_DES(current_2, des.sub);
        cout << plain_dec;
    }
    cout << endl;
}
void Des_Algo()
{
    cout << "DES Algo" << endl;
    start1();
    int num = 1;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> num;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    DES_keygeneration();
    switch (num)
    {
    case 1:
    {
        DES_encryption();
        break;
    }
    case 2:
    {
        DES_decryption();
        break;
    }

    case 0:
    {
        return;
    }
    }
}
Hill_Algorithm hill;
void Hill_Encryption()
{

    string p;
    string k;

    int valid = 1;


    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, p);
    p.erase(std::remove_if(p.begin(), p.end(), ::isspace),
        p.end());
    //cin >> plaintext;
    for (int i = 0; i < p.length(); i++) {
        if (p[i] >= 'A' && p[i] <= 'Z') {
            p[i] = tolower(p[i]);
        }
        else if (p[i] >= 'a' && p[i] <= 'z') {
            p[i] = p[i];
        }

        else {

            cout << "Invalid plaintext" << endl;
            cout << "Enter the plaintext: ";
            
            getline(cin, p);
            p.erase(std::remove_if(p.begin(), p.end(), ::isspace),
                p.end());
            valid = 0;

        }
    }
    cout << "Enter the key: ";
   
    getline(cin, k);
    k.erase(std::remove_if(k.begin(), k.end(), ::isspace),
        k.end());


    //cin >> plaintext;


    valid = 1;
    do {
        valid = 1;

        for (int i = 0; i < k.length(); i++) {

            if (k[i] >= 'A' && k[i] <= 'Z') {
                k[i] = tolower(k[i]);
            }
            else if (k[i] >= 'a' && k[i] <= 'z') {
                k[i] = k[i];
            }

            else {

                cout << "Invalid key contains invalid characters" << endl;
                
                cout << "Enter the key: ";
               
                getline(cin, k);
                k.erase(std::remove_if(k.begin(), k.end(), ::isspace),
                    k.end());
                valid = 0;

            }

        }
    } while (valid == 0);
    int siz_of_key = k.length();
    int n = sqrt(siz_of_key);
    
 
        long long sr = sqrt(siz_of_key);
        if (sr * sr != siz_of_key) {
            int num1 = pow(round(sqrt(siz_of_key)), 2);
            int num2 = sqrt(num1);
            int rem = siz_of_key - num2;
            char ch = 'a';
            for (int i = 0; i < rem; i++) {
                k+=ch;
                ch++;
            }
        }

    
   
    Hill_Algorithm hillex;
    int determin = hillex.Calc_Det(k, n);
    /*
    do {
        valid = 1;
        if (determin == 0 || gcd(determin, 26) != 1) {
            valid = 0;
            cout << "Det =0 || gcd != 1" << endl;
            cout << "Please Enter a valid key  : " << endl;
            cin >> k;

        }

    } while (valid == 0);

    */
    int siz_key = sqrt(k.length());
    int mod = p.length() % siz_key;
    if (mod != 0) {
        int rem = siz_key - mod;
        for (int i = 0; i < rem; i++) {
            p.append("x");
        }
    }

    string cip = p;
    int a = p.length();
    int b = k.length();
    
    int* arr = new int[a];
    int* arr2 = new int[b];
    for (int i = 0; i < a; i++) {
        arr[i] = p[i] - 97;
    }
    for (int i = 0; i < b; i++) {
        arr2[i] = k[i] - 97;
    }


    hill.size_of_plain = a;
    hill.size_of_cipher = a;
    hill.size_of_key = b;
    int* result = new int[Hill_Algorithm::size_of_plain];
    result = hill.Encrypt(arr, arr2);
    for (int i = 0; i < hill.size_of_plain; i++) {
        cip[i] = char((result[i] % 26) + 97);
    }
    cout << "Encrypted : " << cip << endl;

}
void Hill_Decryption()
{
    
			string cipher;
			string key;


			int valid = 1;


			cout << "Enter the ciphertext: ";
			cin.ignore();
			getline(cin, cipher);
			cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
				cipher.end());
			//cin >> plaintext;
			for (int i = 0; i < cipher.length(); i++) {
				if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
					cipher[i] = tolower(cipher[i]);
				}
				else if (cipher[i] >= 'a' && cipher[i] <= 'z') {
					cipher[i] = cipher[i];
				}

				else {

					cout << "Invalid ciphertext" << endl;
                    cout << "Enter the ciphertext: ";
                    
                    getline(cin, cipher);
                    cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
                        cipher.end());
					valid = 0;

				}
			}
            cout << "Enter the key: ";
            
            getline(cin, key);
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace),
                key.end());
            int siz_of_key = key.length();
            int n = sqrt(siz_of_key);


            long long sr = sqrt(siz_of_key);
            if (sr * sr != siz_of_key) {
                int num1 = pow(round(sqrt(siz_of_key)), 2);
                int num2 = sqrt(num1);
                int rem = siz_of_key - num2;
                char ch = 'A';
                for (int i = 0; i < rem; i++) {
                    key += ch;
                    ch++;
                }
            }
			valid = 1;
			Hill_Algorithm hillex;
			int determin = hillex.Calc_Det(key, n);
            /*
			do {
				valid = 1;
				if (determin == 0 || gcd(determin, 26) != 1) {
					valid = 0;
                  
                    cout << " det =0 ";
                    cout << "Enter the key: ";
                    
                    getline(cin, key);
                    key.erase(std::remove_if(key.begin(), key.end(), ::isspace),
                        key.end());
                    siz_of_key = key.length();
                    n = sqrt(siz_of_key);
                    determin = hillex.Calc_Det(key, n);

				}

			} while (valid == 0);


            */
			//cin >> plaintext;


			valid = 1;
			do {
				valid = 1;

				for (int i = 0; i < key.length(); i++) {

					if (key[i] >= 'A' && key[i] <= 'Z') {
						key[i] = tolower(key[i]);
					}
					else if (key[i] >= 'a' && key[i] <= 'z') {
						key[i] = key[i];
					}

					else {

						cout << "Invalid key" << endl;
                        cout << "Enter the key: ";
                        
                        getline(cin, key);
                        key.erase(std::remove_if(key.begin(), key.end(), ::isspace),
                            key.end());
						valid = 0;

					}

				}
			} while (valid == 0);



			int siz_key = sqrt(key.length());
			
			int mod = cipher.length() % siz_key;
			if (mod != 0) {
				int rem = siz_key - mod;
				for (int i = 0; i < rem; i++) {
					cipher.append("x");
				}
			}



		
			string plain = cipher;
			int a2 = cipher.length();
			int b2 = key.length();
			int* arr3 = new int[a2];
			int* arr4 = new int[b2];
			for (int i = 0; i < a2; i++) {

				arr3[i] = cipher[i] - 97;
			}
			for (int i = 0; i < b2; i++) {
				arr4[i] = key[i] - 97;
			}


			hill.size_of_cipher = a2;
			hill.size_of_plain = a2;
			hill.size_of_key = b2;
			int* result2 = new int[hill.size_of_cipher];
			result2 = hill.Decrypt(arr3, arr4);
			for (int i = 0; i < hill.size_of_cipher; i++) {
				//cout << fmod(result2[i], 26) << " ";

				//cout << result2[i]<<" ";
				plain[i] = char(result2[i] + 97);
			}
			cout << "Decrypted : " << plain;


}
void Hill_Analysis()
{
    int choice;
    cout << "Press 1 for 2x2 Analysis " << endl;
    cout << "Press 2 for 3x3 Analysis" << endl;
    cin >> choice;

    if (choice == 1)
    {
        string cipher;
        string plain;
        int valid = 1;


        cout << "Enter the plaintext: ";
        cin.ignore();
        getline(cin, plain);
        plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
            plain.end());
        //cin >> plaintext;
        do {
            valid = 1;
            for (int i = 0; i < plain.length(); i++) {
                if (plain[i] >= 'A' && plain[i] <= 'Z') {
                    plain[i] = tolower(plain[i]);
                }
                else if (plain[i] >= 'a' && plain[i] <= 'z') {
                    plain[i] = plain[i];
                }

                else {

                    cout << "Invalid plaintext" << endl;
                    cout << "Plaintext contains invalid characters" << endl;
                    cout << "Enter the plaintext: ";

                    getline(cin, plain);
                    plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                        plain.end());
                    valid = 0;

                }
            }
        } while (valid == 0);

        int siz_of_plain = plain.length();
        int n = sqrt(siz_of_plain);
        int valid_plain = 1;
        do {
            valid_plain = 1;


            long long sr = sqrt(siz_of_plain);


            if (n != 2) {
                valid_plain = 0;
                cout << "Invalid plaintext" << endl;
                cout << "Size of plaintext must be 4 (2x2)" << endl;
                cout << "Enter the plaintext: ";

                getline(cin, plain);
                plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                    plain.end());
                valid = 0;

                siz_of_plain = plain.length();
                n = sqrt(siz_of_plain);

            }


        } while (valid_plain == 0);
        valid = 1;
        Hill_Algorithm hillex;
        int determin = hillex.Calc_Det(plain, n);
        do {
            valid = 1;
            if (determin == 0) {
                valid = 0;


                cout << "Invalid plaintext" << endl;
                cout << "Determinant of plain text equals to 0 (not invertible)";
                cout << "Enter the plaintext: ";
                cin.ignore();
                getline(cin, plain);
                plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                    plain.end());
                determin = hillex.Calc_Det(plain, n);


            }

        } while (valid == 0);

        cout << "Enter the ciphertext: " << endl;


        getline(cin, cipher);
        cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
            cipher.end());

        //cin >> plaintext;
        do {
            valid = 1;
            for (int i = 0; i < cipher.length(); i++) {
                if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
                    cipher[i] = tolower(cipher[i]);
                }
                else if (cipher[i] >= 'a' && cipher[i] <= 'z') {
                    cipher[i] = cipher[i];
                }

                else {

                    cout << "Invalid ciphertext" << endl;
                    cout << "Ciphertext contains invalid characters" << endl;
                    cout << "Enter the ciphertext: ";

                    getline(cin, cipher);
                    cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
                        cipher.end());
                    valid = 0;


                }
            }

        } while (valid == 0);
        int siz_of_cipher = cipher.length();
        n = sqrt(siz_of_cipher);
        int valid_cipher = 1;
        do {
            valid_cipher = 1;


            long long sr = sqrt(siz_of_cipher);


            if (n != 2) {
                valid_cipher = 0;
                cout << "Invalid ciphertext" << endl;
                cout << "Size of ciphertext must be 4 (2x2)" << endl;
                cout << "Enter the ciphertext: ";

                getline(cin, cipher);
                cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
                    cipher.end());
                siz_of_cipher = cipher.length();
                n = sqrt(siz_of_cipher);

            }


        } while (valid_cipher == 0);

        int valid_input = 1;
        do {
            valid_input = 1;
            if (plain.length() != cipher.length()) {
                valid_input = 0;
                cout << "Plaintext and ciphertext are of different size" << endl;
                cout << "Enter the plaintext : ";

                getline(cin, plain);
                plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                    plain.end());

                cout << "Enter the ciphertext : ";

                getline(cin, cipher);
                cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
                    cipher.end());

            }


        } while (valid_input == 0);
        string key = cipher;
        int a2 = plain.length();
        int b2 = cipher.length();
        int* arr3 = new int[a2];
        int* arr4 = new int[b2];
        for (int i = 0; i < a2; i++) {

            arr3[i] = plain[i] - 97;
        }
        for (int i = 0; i < b2; i++) {
            arr4[i] = cipher[i] - 97;
        }


        hill.size_of_cipher = a2;
        hill.size_of_plain = a2;
        hill.size_of_key = 4;
        int* result2 = new int[hill.size_of_cipher];
        result2 = hill.Analyse(arr3, arr4);
        for (int i = 0; i < hill.size_of_cipher; i++) {
            //cout << fmod(result2[i], 26) << " ";

            //cout << result2[i]<<" ";
            key[i] = char(result2[i] + 97);
        }
        cout << "key  : " << key;

    }
    else if (choice == 2)
    {
    string cipher;
    string plain;
    int valid = 1;


    cout << "Enter the plaintext: ";
    cin.ignore();
    getline(cin, plain);
    plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
        plain.end());
    //cin >> plaintext;
    do {
        valid = 1;
        for (int i = 0; i < plain.length(); i++) {
            if (plain[i] >= 'A' && plain[i] <= 'Z') {
                plain[i] = tolower(plain[i]);
            }
            else if (plain[i] >= 'a' && plain[i] <= 'z') {
                plain[i] = plain[i];
            }

            else {

                cout << "Invalid plaintext" << endl;
                cout << "Plaintext contains invalid characters" << endl;
                cout << "Enter the plaintext: ";

                getline(cin, plain);
                plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                    plain.end());
                valid = 0;

            }
        }
    } while (valid == 0);

    int siz_of_plain = plain.length();
    int n = sqrt(siz_of_plain);
    int valid_plain = 1;
    do {
        valid_plain = 1;


        long long sr = sqrt(siz_of_plain);


        if (n != 3) {
            valid_plain = 0;
            cout << "Invalid plaintext" << endl;
            cout << "Size of plaintext must be 9 (3x3)" << endl;
            cout << "Enter the plaintext: ";

            getline(cin, plain);
            plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                plain.end());
            valid = 0;
            siz_of_plain = plain.length();
            n = sqrt(siz_of_plain);

        }


    } while (valid_plain == 0);
    valid = 1;
    Hill_Algorithm hillex;
    int determin = hillex.Calc_Det(plain, n);
    do {
        valid = 1;
        if (determin == 0) {
            valid = 0;


            cout << "Invalid plaintext" << endl;
            cout << "Determinant of plain text equals to 0 (not invertible)";
            cout << "Enter the plaintext: ";
            cin.ignore();
            getline(cin, plain);
            plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                plain.end());
            determin = hillex.Calc_Det(plain, n);


        }

    } while (valid == 0);

    cout << "Enter the ciphertext: " << endl;


    getline(cin, cipher);
    cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
        cipher.end());

    //cin >> plaintext;
    do {
        valid = 1;
        for (int i = 0; i < cipher.length(); i++) {
            if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
                cipher[i] = tolower(cipher[i]);
            }
            else if (cipher[i] >= 'a' && cipher[i] <= 'z') {
                cipher[i] = cipher[i];
            }

            else {

                cout << "Invalid ciphertext" << endl;
                cout << "Ciphertext contains invalid characters" << endl;
                cout << "Enter the ciphertext: ";

                getline(cin, cipher);
                cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
                    cipher.end());
                valid = 0;


            }
        }

    } while (valid == 0);
    int siz_of_cipher = cipher.length();
    n = sqrt(siz_of_cipher);
    int valid_cipher = 1;
    do {
        valid_cipher = 1;


        long long sr = sqrt(siz_of_cipher);


        if (n != 3) {
            valid_cipher = 0;
            cout << "Invalid ciphertext" << endl;
            cout << "Size of ciphertext must be 9 character (3x3)" << endl;
            cout << "Enter the ciphertext: ";

            getline(cin, cipher);
            cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
                cipher.end());
            siz_of_cipher = cipher.length();
            n = sqrt(siz_of_cipher);

        }


    } while (valid_cipher == 0);

    int valid_input = 1;
    do {
        valid_input = 1;
        if (plain.length() != cipher.length()) {
            valid_input = 0;
            cout << "Plaintext and ciphertext are of different size" << endl;
            cout << "Enter the plaintext : ";

            getline(cin, plain);
            plain.erase(std::remove_if(plain.begin(), plain.end(), ::isspace),
                plain.end());

            cout << "Enter the ciphertext : ";

            getline(cin, cipher);
            cipher.erase(std::remove_if(cipher.begin(), cipher.end(), ::isspace),
                cipher.end());

        }


    } while (valid_input == 0);



    string key = cipher;
    int a2 = plain.length();
    int b2 = cipher.length();
    int* arr3 = new int[a2];
    int* arr4 = new int[b2];
        for (int i = 0; i < a2; i++) {

            arr3[i] = plain[i] - 97;
        }
        for (int i = 0; i < b2; i++) {
            arr4[i] = cipher[i] - 97;
        }


        hill.size_of_cipher = a2;
        hill.size_of_plain = a2;
        hill.size_of_key = 9;
        int* result2 = new int[hill.size_of_cipher];
        result2 = hill.Analyse3By3Key(arr3, arr4);
        for (int i = 0; i < hill.size_of_cipher; i++) {
            //cout << fmod(result2[i], 26) << " ";

            //cout << result2[i]<<" ";
            key[i] = char(result2[i] + 97);
        }
        cout << "key :  " << key;

    }

}
void HillAlgo()
{
    int ch;
    //Hill_Algorithm hill;
    cout << "Press 1 for Encryption" << endl;
    cout << "Press 2 for Decryption" << endl;
    cout << "press 3 Analysis" << endl;
    cout << "press 0 to quit" << endl;
    bool aux = true;
    cin.exceptions(std::istream::failbit);
    do {
        try {

            cin >> ch;
            aux = true;
        }
        catch (std::ios_base::failure& fail) {
            aux = false;
            cout << "PLEASE INSERT A VALID OPTION." << endl;
            cin.clear();
            std::string tmp;
            getline(cin, tmp);
        }
    } while (aux == false);
    if (ch == 1) {
        Hill_Encryption();


    }
    else if (ch == 2) {


        Hill_Decryption();

    }
    else if (ch == 3) {
        Hill_Analysis();
    }
    else if (ch == 0) {
        return;
    }




}

