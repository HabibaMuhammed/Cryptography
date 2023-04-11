#include "DES.h"
#include <iostream>
#include <string>
#include <cmath>
#include <bitset>
#include <unordered_map>
#include<sstream>
using namespace std;
int IP[64] = {
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7
};
int E_Table[48] = {
    32,1,2,3,4,5,4,5,
    6,7,8,9,8,9,10,11,
    12,13,12,13,14,15,16,17,
    16,17,18,19,20,21,20,21,
    22,23,24,25,24,25,26,27,
    28,29,28,29,30,31,32,1
};
int S_Box[8][4][16] =
{ {
    14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
},
{
    15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
},
{
    10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
},
{
    7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
},
{
    2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
},
{
    12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
},
{
    4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
},
{
    13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
} };

// permutation for the s-box result
int permutation_tab[32] = {
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25
};
int inverse_permutation[64] = {
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25
};
string xoring(string a, string b, int n) {
    string ans = "";
    for (int i = 0; i < n; i++)
    {

        if (a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }
    return ans;
}
int bin_to_dec(string s) {
    int value = 0;
    int indexCounter = 0;
    for (int i = s.length() - 1; i >= 0; i--) {

        if (s[i] == '1') {
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}
string Dec_to_Bin(int n)
{
    string bin = "";
    while (n > 0)
    {
        bin = (char)(n % 2 + '0') + bin;
        n /= 2;
    }
    while (bin.size() < 4)
        bin = '0' + bin;
    return bin;
}

string BinaryKey = "";
string hexatobinary = "";
string test = BinaryKey;
string pc1Key = "";                  // [56] 
string pc2Key[48];
string cKey = "";                    // [28] 
string dKey = "";                    // [28]
string Ks[16];                      // array of 16 pc2Key each of size 48 bits
string c2Key[16];
string d2Key[16];
string CD[16];


int pc1Table[56] = { 57, 49, 41, 33, 25, 17, 9,
                    1, 58, 50, 42, 34, 26, 18,
                    10, 2, 59, 51, 43, 35, 27,
                    19, 11, 3, 60, 52, 44, 36,
                    63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                    14, 6,  61, 53, 45, 37, 29,
                    21, 13, 5, 28, 20, 12, 4 };

int shiftTable[16] = { 1, 1, 2, 2, 2, 2, 2, 2,1, 2, 2, 2, 2, 2, 2, 1 }; //number of round-1

int pc2Table[48] = { 14, 17, 11, 24, 1,  5,
                     3, 28, 15, 6, 21, 10,
                     23, 19, 12, 4, 26, 8,
                     16, 7, 27, 20, 13, 2,
                     41, 52, 31, 37, 47, 55,
                     30, 40, 51, 45, 33, 48,
                     44, 49, 39, 56, 34, 53,
                     46, 42, 50, 36, 29, 32 };

void start()
{
    cout << "Choose The type of the Key Entered" << endl;
    cout << "If the Key Type is Text press 1: " << endl;
    cout << "If the Key Type is Hexadecimal press 2:" << endl;
}
string Text_To_Binary(string EnteredKey)
{
    int len = EnteredKey.length();
    string BinaryKeyChar = "";
    BinaryKey = "";
    for (int i = 0; i < len; i++)
    {

        bitset<8> binaryKey(EnteredKey[i]);
        BinaryKeyChar = binaryKey.to_string();
        cout << EnteredKey[i] << ": string values :" << BinaryKeyChar << endl;
        for (int j = 0; j < 8; j++)
        {
            BinaryKey.push_back(BinaryKeyChar[j]);
        }

    }



    return BinaryKey;
}

string Hexa_To_Binary(string enterkey)
{
    int hexalength = enterkey.length();
    string Binvalue = "";
    int i = 0;
    while (i < hexalength)
    {
        switch (enterkey[i])
        {
        case  '0':
            Binvalue += "0000";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;

        case '1':
            Binvalue += "0001";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;

        case '2':
            Binvalue += "0010";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case '3':
            Binvalue += "0011";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case '4':
            Binvalue += "0100";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case '5':
            Binvalue += "0101";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case '6':
            Binvalue += "0110";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case '7':
            Binvalue += "0111";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case '8':
            Binvalue += "1000";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case '9':
            Binvalue += "1001";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case'A':
        case'a':
            Binvalue += "1010";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case'B':
        case'b':
            Binvalue += "1011";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case'C':
        case'c':
            Binvalue += "1100";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case'D':
        case'd':
            Binvalue += "1101";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case'E':
        case'e':
            Binvalue += "1110";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        case'F':
        case'f':
            Binvalue += "1111";
            //cout << "enterkey[i]" << Binvalue << endl;
            break;
        }
        ++i;
    }
    return Binvalue;

}
string binary_To_hex(string s)
{
    // binary to hexadecimal conversion
    unordered_map<string, string> mp;
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "A";
    mp["1011"] = "B";
    mp["1100"] = "C";
    mp["1101"] = "D";
    mp["1110"] = "E";
    mp["1111"] = "F";
    string hex = "";
    for (int i = 0; i < s.length(); i += 4) {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hex += mp[ch];
    }
    return hex;
}

void pc1(string testBin1)
{

    for (int i = 0; i < 56; i++)
    {
        int val = pc1Table[i];
        pc1Key += testBin1[val - 1];
    }
    cKey = pc1Key.substr(0, 28);
    dKey = pc1Key.substr(28, 28);
}
string left_shift(string testBin1, int shiftVal)
{
    string shifted = "";

    for (int i = shiftVal; i < testBin1.size(); i++)
        shifted += testBin1[i];

    for (int i = 0; i < shiftVal; i++)
        shifted += testBin1[i];

    return shifted;
}
string BinaryStringToText(string binaryString) {
    string text = "";
    stringstream sstream(binaryString);
    while (sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        text += char(bits.to_ulong());
    }
    return text;
}
string T2_DES::Encrypt_DES(string plain, string key[16]) {

    string cipher;
    string plain_after = plain;
    for (int i = 0; i < 64; i++) {
        plain_after[i] = plain[IP[i] - 1];
    }
    plain = plain_after;
    string L = plain.substr(0, 32);
    string R = plain.substr(32, 32);

    for (int i = 0; i < 16; i++) {
        string left = L;
        L = R;
        string expanded = "111111111111111111111111111111111111111111111111";
        for (int k = 0; k < 48; k++) {
            expanded[k] = R[E_Table[k] - 1];
        }
        string xor1;
        xor1 = xoring(expanded, key[i], 48);
        string curr = "111111";
        string r = "00";
        string col = "0000";
        string res;
        int cnt = 0;
        for (int j = 0; j < 8; j++) {
            curr = xor1.substr(cnt, 6);
            r[0] = curr[0];
            r[1] = curr[5];
            for (int l = 0; l < 4; l++) {
                col[l] = curr[l + 1];
            }

            int row = bin_to_dec(r);
            int column = bin_to_dec(col);
            int s_value = S_Box[j][row][column];

            string s_value_bin = "";
            s_value_bin = Dec_to_Bin(s_value);

            res.append(s_value_bin);


            cnt += 6;

        }
        string permuted = res;
        for (int a = 0; a < 32; a++) {
            permuted[a] = res[permutation_tab[a] - 1];
        }
        R = xoring(left, permuted, 32);

        if (i == 15) {
            string final_ip = "1111111111111111111111111111111111111111111111111111111111111111";
            cipher.append(R);
            cipher.append(L);

            for (int b = 0; b < 64; b++) {
                final_ip[b] = cipher[inverse_permutation[b] - 1];
            }
            cipher = final_ip;

        }

    }
    string ciphertext;
    cout << "Cipher is :  " << cipher << endl;
    ciphertext = BinaryStringToText(cipher);
    return ciphertext;

}
string T2_DES::Decrypt_DES(string cipher, string key[16]) {
    string reversed_keys[16] = { "0","0" ,"0" ,"0" ,"0","0" ,"0" ,"0" ,"0","0" ,"0" ,"0" ,"0","0" ,"0" ,"0" };
    for (int i = 0; i < 16; i++) {

        reversed_keys[15 - i] = key[i];


    }
    string plain = Encrypt_DES(cipher, reversed_keys);
    return  plain;


}
void T2_DES::key_generation(string key) {


    pc1(key);


    for (int i = 1; i < 16; i++) // shifting each C and each D
    {

        c2Key[0] = left_shift(cKey, shiftTable[0]);
        c2Key[i] = left_shift(c2Key[i - 1], shiftTable[i]);
        d2Key[0] = left_shift(dKey, shiftTable[0]);
        d2Key[i] = left_shift(d2Key[i - 1], shiftTable[i]);

    }
    for (int i = 0; i < 16; i++)
    {
        CD[i] = c2Key[i] + d2Key[i];
    }

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 48; j++)
        {
            int val = pc2Table[j];
            Ks[i] += CD[i][val - 1];
        }
        sub[i] = Ks[i];
    }
    return;
}
string T2_DES::Plain_Bin(string plain) {
    string bin = Text_To_Binary(plain);
    return bin;


}