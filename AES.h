#include <iostream>
#include <memory.h>
using namespace std;
uint8_t get_sbox(uint8_t x);
void substitute_bytes(uint8_t** state);
void shiftRows(uint8_t** state);
void MixColumns(uint8_t** state);
uint8_t** AES_Encrypt(string plain, string key);
uint8_t** AES_Decrypt(string cipher, string key);
void AddRoundKey(uint8_t**, uint8_t** subkey);
void Inv_AddRoundKey(uint8_t** state, uint8_t** subkey);
void Inv_substitute_bytes(uint8_t** state);
void Inv_shiftRows(uint8_t** state);
void Inv_MixColumns(uint8_t state[][4]);
