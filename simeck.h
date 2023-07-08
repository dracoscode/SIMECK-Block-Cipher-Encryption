/*
 *
 * The input is from right to left. 
 * The rightmost byte is the least significant byte.
 * The leftmost byte is the most significant byte.
 */

#ifndef SIMECK_H
#define SIMECK_H

#define SIMECK32_BLOCK_SIZE          (32)
#define SIMECK32_WORD_SIZE           (16)
#define SIMECK_KEY_WORDS_64        (4)
#define SIMECK_ROUNDS_64           (32)
#define SIMECK_KEY_WORDS_96        (6)
#define SIMECK_ROUNDS_96           (32)
#define SIMECK_KEY_WORDS_128       (8)
#define SIMECK_ROUNDS_128          (44)

#include "types.h"

/*
 * key schedule
 * inputKey: the original keys
 * keys: round keys
 */
void simeck_32_64_key_schedule(const u8 * inputKey, u8 * keys );

void simeck_48_96_key_schedule(const u8 * inputKey, u8 * keys );

void simeck_64_128_key_schedule(const u8 * inputKey, u8 * keys );

/*
 * encrypt
 * plainText: plainText has just one block.
 * keys: round keys
 */
void simeck_32_64_encrypt(u8 * plainText, const u8 * keys );

void simeck_48_96_encrypt(u8 * plainText, const u8 * keys );

void simeck_64_128_encrypt(u8 * plainText, const u8 * keys );

/*
 * decrypt
 * cipherText: cipherText has just one block.
 * keys: round keys
 */
void simeck_32_64_decrypt(u8 * cipherText, const u8 * keys );

void simeck_48_96_decrypt(u8 * cipherText, const u8 * keys );

void simeck_64_128_decrypt(u8 * cipherText, const u8 * keys );

#endif