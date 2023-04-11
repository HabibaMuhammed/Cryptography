
#ifndef MD5_H
#define MD5_H
#include <iostream>
#include <vector>
using namespace std;
vector <uint8_t > AppendPaddingBits(vector <uint8_t >input);
vector<uint8_t>  AppendLength(vector<uint8_t>ret, int sz);
vector<uint32_t > createM(vector<uint8_t>vec);
void Round1(vector<uint32_t> m);
void Round2(vector<uint32_t> m);
void Round3(vector<uint32_t> m);
void Round4(vector<uint32_t> m);
uint32_t F(uint32_t B, uint32_t C, uint32_t D);
uint32_t G(uint32_t B, uint32_t C, uint32_t D);
uint32_t H(uint32_t B, uint32_t C, uint32_t D);
uint32_t I(uint32_t B, uint32_t C, uint32_t D);
string MD5(string s);
void InitializeMDBuffer();
#endif 