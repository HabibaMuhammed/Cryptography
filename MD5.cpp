
#include <iostream>
#include <vector>
#include <iomanip>
#include<sstream>
#include<string>
#include <cmath>
#include <algorithm>

using namespace std;
uint32_t A;
uint32_t B;
uint32_t C;
uint32_t D;

void InitializeMDBuffer() {
    A = 0x67452301;
    B = 0xEFCDAB89;
    C = 0x98BADCFE;
    D = 0x10325476;
};
int idx[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 6, 11, 0, 5, 10, 15, 4,
        9, 14, 3, 8, 13, 2, 7, 12, 5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
        0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9

};
int shft[] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20,
        5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21

};
// comes from abs(sin(i+ 1))×2^32
uint32_t K[] = {

        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
        0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
        0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
        0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
        0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
        0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

vector<uint8_t> AppendPaddingBits(vector<uint8_t> input) {
    int bitsCnt = (input.size() + 1) * 8;
    vector<uint8_t> temp;
    input.push_back(0x80);
    while (bitsCnt % 512 != 448) {
        input.push_back(0);
        bitsCnt += 8;
    }
    return input;
}

vector<uint8_t> AppendLength(vector<uint8_t> ret, int sz) {
    uint64_t len = sz;
    uint8_t* p = (uint8_t*)&len;
    vector<uint8_t> temp;
    for (int i = 0; i < 8; i++) {
        temp.push_back(p[i]);
    }
    for (auto e : temp)
        ret.push_back(e);
    return ret;
};

uint32_t F(uint32_t B, uint32_t C, uint32_t D) {
    return (((B) & (C)) | ((~B) & (D)));
};

uint32_t G(uint32_t B, uint32_t C, uint32_t D) {
    return (B & D) | (C & ~D);
};

uint32_t H(uint32_t B, uint32_t C, uint32_t D) {
    return B ^ C ^ D;
};

uint32_t I(uint32_t B, uint32_t C, uint32_t D) {
    return C ^ (B | ~D);
};

vector<uint32_t> createM(vector<uint8_t> vec) {

    vector<uint32_t> M;
    for (int i = 0; i < vec.size(); i += 4) {
        uint32_t temp = vec[i + 3] << 24 | vec[i + 2] << 16 | vec[i + 1] << 8 | vec[i];
        M.push_back(temp);
    }
    return M;

};

string createO(vector<uint32_t> vec) {

    vector<uint8_t> M;

    for (int i = 0; i < vec.size(); i++) {
        //        cout<< hex << vec[i]<< " ";
        M.push_back((uint8_t)(vec[i]));
        M.push_back((uint8_t)(vec[i] >> 8));
        M.push_back((uint8_t)(vec[i] >> 16));
        M.push_back((uint8_t)(vec[i] >> 24));
    }
    //    cout << endl;
    stringstream ss;
    string s;

    for (int i = 0; i < M.size(); i++) {


        if (!(M[i] & 0xf0))
            ss << "0";
        ss << hex << (int)(M[i]);
        s = ss.str();


    }

    return s;

};


uint32_t mod_add(uint32_t a, uint32_t b) {
    return (a + b);
}

uint32_t circularShift(uint32_t num, int shift) {
    int right = 32 - (int)shift;
    uint32_t temp = num;
    uint32_t ret = num >> right;
    temp = temp << shift;
    temp |= ret;
    return temp;
}

void Round4(vector<uint32_t> m) {
    for (int i = 48; i < 64; i++) {
        uint32_t I_Ret = I(B, C, D);
        uint32_t val = mod_add(I_Ret, A);
        val = mod_add(val, m[idx[i]]);
        val = mod_add(val, K[i]);
        val = circularShift(val, shft[i]);
        val = mod_add(val, B);
        A = D;
        D = C;
        C = B;
        B = val;
    }
}

void Round3(vector<uint32_t> m) {
    for (int i = 32; i < 48; i++) {
        uint32_t H_Ret = H(B, C, D);
        uint32_t val = mod_add(H_Ret, A);
        val = mod_add(val, m[idx[i]]);
        val = mod_add(val, K[i]);
        val = circularShift(val, shft[i]);
        val = mod_add(val, B);
        A = D;
        D = C;
        C = B;
        B = val;
    }
}

void Round2(vector<uint32_t> m) {
    for (int i = 16; i < 32; i++) {
        uint32_t G_Ret = G(B, C, D);
        uint32_t val = mod_add(G_Ret, A);
        val = mod_add(val, m[idx[i]]);
        val = mod_add(val, K[i]);
        val = circularShift(val, shft[i]);
        val = mod_add(val, B);
        A = D;
        D = C;
        C = B;
        B = val;
    }
}

void Round1(vector<uint32_t> m) {
    for (int i = 0; i < 16; i++) {

        uint32_t F_Ret = F(B, C, D);
        uint32_t val = mod_add(F_Ret, A);
        val = mod_add(val, m[idx[i]]);
        val = mod_add(val, K[i]);
        val = circularShift(val, (int)shft[i]);
        val = mod_add(val, B);
        A = D;
        D = C;
        C = B;
        B = val;

    }
}

string MD5(string s) {

    vector<uint8_t> vec;

    for (int i = 0; i < s.size(); i++) {
        vec.push_back(s[i]);
    }
    vector<uint8_t> ret;
    InitializeMDBuffer();
    ret = AppendPaddingBits(vec);
    ret = AppendLength(ret, s.size() * 8);
    uint32_t prevA = A, prevB = B, prevC = C, prevD = D;
    for (int y = 0; y < ret.size(); y += 64) {
        vector<uint8_t> temp;
        for (int x = y; x <= y + 63; x++) {
            temp.push_back(ret[x]);
        }
        vector<uint32_t> m = createM(temp);
        //convert to 32-bit words
        Round1(m);
        Round2(m);
        Round3(m);
        Round4(m);

        uint32_t OutputA = A, OutputB = B, OutputC = C, OutputD = D;
        A = mod_add(prevA, OutputA);
        B = mod_add(prevB, OutputB);
        C = mod_add(prevC, OutputC);
        D = mod_add(prevD, OutputD);
        prevA = A, prevB = B, prevC = C, prevD = D;
    }
    vector<uint32_t> finalOutput;
    finalOutput.push_back(A);
    finalOutput.push_back(B);
    finalOutput.push_back(C);
    finalOutput.push_back(D);
    string output = createO(finalOutput);
    return output;

}