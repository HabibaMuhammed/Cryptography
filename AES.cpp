#include "AES.h"
#include <iostream>
#include <memory.h>
#include<stdlib.h>
#include<vector>
vector<uint8_t> HexToBytes(string hex) {
    vector<uint8_t> bytes;
    for (unsigned int i = 2; i < hex.length() + 2; i += 2) {
        string byteString = hex.substr(i, 2);
        uint8_t byte = (uint8_t)strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

using namespace std;
unsigned char Inv_sub_box[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
unsigned char Inv_MixMatrix[4][4] = {
    {0x0E, 0x0B, 0x0D, 0x09},
    {0x09, 0x0E, 0x0B, 0x0D},
    {0x0D, 0x09, 0x0E, 0x0B},
    {0x0B, 0x0D, 0x09, 0x0E} };

static uint8_t MixMatrix[4][4] = {
    0x02, 0x03, 0x01, 0x01,
    0x01, 0x02, 0x03, 0x01,
    0x01, 0x01, 0x02, 0x03,
    0x03, 0x01, 0x01, 0x02
};

static uint8_t sub_box[256] = {

    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87,0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};
#define KEYS_CNT 11


static uint8_t rcon[10][4] = {
        {0x01, 0x00, 0x00, 0x00},
        {0x02, 0x00, 0x00, 0x00},
        {0x04, 0x00, 0x00, 0x00},
        {0x08, 0x00, 0x00, 0x00},
        {0x10, 0x00, 0x00, 0x00},
        {0x20, 0x00, 0x00, 0x00},
        {0x40, 0x00, 0x00, 0x00},
        {0x80, 0x00, 0x00, 0x00},
        {0x1b, 0x00, 0x00, 0x00},
        {0x36, 0x00, 0x00, 0x00},

};

void rotWord(uint8_t* col1) {
    for (int i = 0; i < 3; i++) {
        swap(col1[i], col1[i + 1]);
    }
}

void subkeyByte(uint8_t* col1) {
    for (int i = 0; i < 4; i++) {
        col1[i] = sub_box[col1[i]];
    }
}
void Inv_subkeyByte(uint8_t* col1) {
    for (int i = 0; i < 4; i++) {
        col1[i] = Inv_sub_box[col1[i]];
    }
}

void tripleXor(uint8_t* res, uint8_t* col1, uint8_t* col2, int colNo) {
    for (int i = 0; i < 4; i++) {
        res[i] = col1[i] ^ col2[i] ^ rcon[colNo][i];
    }

}

void doubleXor(uint8_t* res, uint8_t* col1, uint8_t* col2) {
    for (int i = 0; i < 4; i++)
        res[i] = col1[i] ^ col2[i];
}

uint8_t*** keyExpansion(uint8_t key[4][4]) {
    uint8_t*** subkey = new uint8_t * *[11];

    for (int i = 0; i < 11; i++) {
        subkey[i] = new uint8_t * [4];
        for (int col = 0; col < 4; col++) {
            subkey[i][col] = new uint8_t[4];
        }
    }


    for (int k = 0; k < KEYS_CNT; k++) {
        if (!k) {
            for (int i = 0; i < 4; i++) {
                for (int col = 0; col < 4; col++) {
                    subkey[k][i][col] = key[i][col];
                }
            }
        }
        else {

            for (int col = 0; col < 4; col++) {

                if (!col) {

                    uint8_t col1[4] = { subkey[k - 1][0][3], subkey[k - 1][1][3], subkey[k - 1][2][3],
                                       subkey[k - 1][3][3] };
                    uint8_t col2[4] = { subkey[k - 1][0][0], subkey[k - 1][1][0], subkey[k - 1][2][0],
                                       subkey[k - 1][3][0] };
                    uint8_t res[4];
                    rotWord(col1);

                    subkeyByte(col1);

                    tripleXor(res, col1, col2, k - 1);
                    for (int row = 0; row < 4; row++) {
                        subkey[k][row][col] = res[row];
                    }

                }
                else {
                    uint8_t col1[4] = { subkey[k - 1][0][col], subkey[k - 1][1][col], subkey[k - 1][2][col],
                                       subkey[k - 1][3][col] };
                    uint8_t col2[4] = { subkey[k][0][col - 1], subkey[k][1][col - 1],
                                       subkey[k][2][col - 1],
                                       subkey[k][3][col - 1] };
                    uint8_t res[4];
                    doubleXor(res, col1, col2);
                    for (int row = 0; row < 4; row++) {
                        subkey[k][row][col] = res[row];
                    }
                }

            }
        }
    }
    return subkey;

}
uint8_t Inv_get_sbox(uint8_t x)
{
    return Inv_sub_box[x];
}
void Inv_substitute_bytes(uint8_t** state)
{
    uint8_t ind;
    for (uint8_t row = 0; row < 4; row++)
    {
        for (uint8_t coloum = 0; coloum < 4; coloum++)
        {
            ind = state[row][coloum];

            state[row][coloum] = Inv_get_sbox(ind);



        }




    }


}
uint8_t get_sbox(uint8_t x)
{
    return sub_box[x];
}
void substitute_bytes(uint8_t** state)
{
    uint8_t ind;
    for (uint8_t row = 0; row < 4; row++)
    {
        for (uint8_t coloum = 0; coloum < 4; coloum++)
        {
            ind = state[row][coloum];

            state[row][coloum] = get_sbox(ind);



        }




    }


}

void Inv_shiftRows(uint8_t** state)
{
    int i, j;
    int t, count;
    for (i = 1; i < 4; i++)
        for (count = 0; count < i; count++) {
            t = state[i][3];
            for (j = 3; j > 0; j--)
                state[i][j] = state[i][j - 1];
            state[i][j] = t;
        }

}
void shiftRows(uint8_t** state)
{
    uint8_t newArray[4][4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            newArray[i][j] = state[i][j];

        }


    }



    state[0][0] = newArray[0][0];
    state[0][1] = newArray[0][1];
    state[0][2] = newArray[0][2];
    state[0][3] = newArray[0][3];
    state[1][0] = newArray[1][1];
    state[1][1] = newArray[1][2];
    state[1][2] = newArray[1][3];
    state[1][3] = newArray[1][0];
    state[2][0] = newArray[2][2];
    state[2][1] = newArray[2][3];
    state[2][2] = newArray[2][0];
    state[2][3] = newArray[2][1];
    state[3][0] = newArray[3][3];
    state[3][1] = newArray[3][0];
    state[3][2] = newArray[3][1];
    state[3][3] = newArray[3][2];




}
uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    

    for (int counter = 0; counter < 8; counter++) {
      
        if ((b & 1) != 0) {
            p ^= a;
        }
      
        bool hi_bit_set = (a & 0x80) != 0;
        a <<= 1;
        if (hi_bit_set) {
            a ^= 0x1B; //Galois Field Reduction (like mod)
        }

        b >>= 1;
    }

    return p;
}
uint8_t* mixSingleColumn(uint8_t* r) {


    unsigned char a[4];
    unsigned char b[4];
    unsigned char c;
    unsigned char h;

    for (c = 0; c < 4; c++) {
        a[c] = r[c];

        h = (unsigned char)((signed char)r[c] >> 7);
        b[c] = r[c] << 1;
        b[c] ^= 0x1B & h;
    }
    /*
    02 03 01 01
    01 02 03 01
    01 01 02 03
    03 01 01 02
    */
    r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
    r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
    r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
    r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
    return r;

}

uint8_t* Inv_mixSingleColumn(uint8_t* r) {


    unsigned char a[4];
    unsigned char c;
    for (c = 0; c < 4; c++) {
        a[c] = r[c];
    }
    /*
    0e 0b 0d 09
    09 0e 0b 0d
    0d 09 0e 0b
    0b 0d 09 0e
    
    */
    r[0] = gmul(a[0], 14) ^ gmul(a[3], 9) ^ gmul(a[2], 13) ^ gmul(a[1], 11);
    r[1] = gmul(a[1], 14) ^ gmul(a[0], 9) ^ gmul(a[3], 13) ^ gmul(a[2], 11);
    r[2] = gmul(a[2], 14) ^ gmul(a[1], 9) ^ gmul(a[0], 13) ^ gmul(a[3], 11);
    r[3] = gmul(a[3], 14) ^ gmul(a[2], 9) ^ gmul(a[1], 13) ^ gmul(a[0], 11);
    return r;

}



void MixColumns(uint8_t** state) {
    uint8_t col[16];
    int ind = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            col[ind] = state[j][i];

            ind++;
        }
    }
    uint8_t temp[4];
    uint8_t* out = new uint8_t[4];
    uint8_t output[16];
    int index = 0;
    for (int i = 0; i < 16; i += 4) {
        temp[0] = col[i];
        temp[1] = col[i + 1];
        temp[2] = col[i + 2];
        temp[3] = col[i + 3];
        out = mixSingleColumn(temp);
        for (int k = 0; k < 4; k++) {
            output[index] = out[k];
            //cout <<hex<<(int)output[index]<<" ";
            index++;

        }

    }
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = output[cnt];
            cnt++;
        }
    }



}
void Inv_MixColumns(uint8_t** state) {
    uint8_t col[16];
    int ind = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            col[ind] = state[j][i];

            ind++;
        }
    }
    uint8_t temp[4];
    uint8_t* out = new uint8_t[4];
    uint8_t output[16];
    int index = 0;
    for (int i = 0; i < 16; i += 4) {
        temp[0] = col[i];
        temp[1] = col[i + 1];
        temp[2] = col[i + 2];
        temp[3] = col[i + 3];
        out = Inv_mixSingleColumn(temp);
        for (int k = 0; k < 4; k++) {
            output[index] = out[k];
            //cout <<hex<<(int)output[index]<<" ";
            index++;

        }

    }
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = output[cnt];
            cnt++;
        }
    }



}
void AddRoundKey(uint8_t** state, uint8_t** subkey) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {



            state[r][c] = state[r][c] ^ subkey[r][c];




        }




    }

}

uint8_t** AES_Encrypt(string plain, string key) {

    vector<uint8_t>bytes;

    uint8_t** state = new uint8_t * [4];
    for (int col = 0; col < 4; col++) {
        state[col] = new uint8_t[4];
    }


    bytes = HexToBytes(plain);

    int ind = 0;
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
            uint8_t byte = bytes[ind];

            state[j][i] = byte;

            ind++;

        }

    }


    vector<uint8_t>sub;
    uint8_t subkey[4][4];
    sub = HexToBytes(key);
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            subkey[j][i] = sub[index];
            index++;
        }
    }
    uint8_t*** subkeys = new uint8_t * *[11];
    subkeys = keyExpansion(subkey);



    AddRoundKey(state, subkeys[0]);

    uint8_t arr[4] = { 1,2,3,4 };
    mixSingleColumn(arr);
    //for (int i = 0; i < 16; i++) {

    //}


    for (int i = 1; i < 10; i++) {




        substitute_bytes(state);

        shiftRows(state);


        MixColumns(state);

        AddRoundKey(state, subkeys[i]);



    }
    substitute_bytes(state);
    shiftRows(state);
    AddRoundKey(state, subkeys[10]);


    return state;
}
uint8_t** AES_Decrypt(string cipher, string key) {

    vector<uint8_t>bytes;

    uint8_t** state = new uint8_t * [4];
    for (int col = 0; col < 4; col++) {
        state[col] = new uint8_t[4];
    }


    bytes = HexToBytes(cipher);

    int ind = 0;
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
            uint8_t byte = bytes[ind];

            state[j][i] = byte;

            ind++;

        }

    }
    vector<uint8_t>sub;
    uint8_t subkey[4][4];
    sub = HexToBytes(key);
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            subkey[j][i] = sub[index];
            index++;
        }
    }
    uint8_t*** subkeys = new uint8_t * *[11];
    subkeys = keyExpansion(subkey);



    AddRoundKey(state, subkeys[10]);



    /*
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << (int)state[i][j]<<" ";
        }
        cout << endl;
    }
    */



    for (int i = 9; i > 0; i--) {



        Inv_shiftRows(state);

        Inv_substitute_bytes(state);
        AddRoundKey(state, subkeys[i]);
        Inv_MixColumns(state);

    }
    Inv_shiftRows(state);
    Inv_substitute_bytes(state);
    AddRoundKey(state, subkeys[0]);


    return state;
}
