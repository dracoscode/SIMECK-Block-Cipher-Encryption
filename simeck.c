
#include "simeck.h"
#include "rotate.h"


/*
 * key schedule
 * inputKey: the original keys
 * keys: round keys
 */

void speck_32_64_key_schedule(const u8 * inputKey, u8 * keys ) {
	
	u16 *rk = (u16*)keys;
	const u16 *ik = (const u16*)inputKey;
	
	u16 l[SIMECK_ROUNDS_64 + SIMECK_KEY_WORDS_64-2];
	rk[0] = ik[0];
	l[0] = ik[1];
	l[1] = ik[2];
	
	int i;
	for ( i = 0; i < SIMECK_ROUNDS_64-1; i++ ) {
		l[i+SIMECK_KEY_WORDS_64-1] = (rk[i] + ror16(l[i], 5)) ^ (u16)i;
		rk[i+1] = rol16(rk[i], 1) ^ l[i+SIMECK_KEY_WORDS_64-1];
	}
}

void speck_48_96_key_schedule(const u8 * inputKey, u8 * keys ) {
	
	u24 *rk = (u24*)keys;
	const u24 *ik = (const u24*)inputKey;
	
	u24 l[SIMECK_ROUNDS_96 + SIMECK_KEY_WORDS_96-2];
	rk[0] = ik[0];
	l[0] = ik[1];
	l[1] = ik[2];
	
	int i;
	for ( i = 0; i < SIMECK_ROUNDS_96-1; i++ ) {
		l[i+SIMECK_KEY_WORDS_96-1] = (rk[i] + ror24(l[i], 5)) ^ (u24)i;
		rk[i+1] = rol24(rk[i], 1) ^ l[i+SIMECK_KEY_WORDS_96-1];
	}
}

void speck_64_128_key_schedule(const u8 * inputKey, u8 * keys ) {
	
	u32 *rk = (u32*)keys;
	const u32 *ik = (const u32*)inputKey;
	
	u32 l[SIMECK_ROUNDS_128 + SIMECK_KEY_WORDS_128-2];
	rk[0] = ik[0];
	l[0] = ik[1];
	l[1] = ik[2];
    l[2] = ik[3];
	
	int i;
	for ( i = 0; i < SIMECK_ROUNDS_128-1; i++ ) {
		l[i+SIMECK_KEY_WORDS_128-1] = (rk[i] + ror32(l[i], 5)) ^ (u32)i;
		rk[i+1] = rol32(rk[i], 1) ^ l[i+SIMECK_KEY_WORDS_128-1];
	}
}

/*
 * encrypt
 * plainText: plainText has just one block.
 * keys: round keys
 */
static void encrypt(u8 * plainText, const u8 * keys, int ROUNDS) {

	u16 *plain = (u16*)plainText;
	const u16 *rk = (const u16*)keys;

    u16 x = plain[0], y = plain[1];

	for(int i = 0; i < ROUNDS; i++) {
        u16 temp = x;
        x = (y & (temp << 1 | temp >> (16 - 1))) ^ ((temp << 5 | temp >> (16 - 5)) ^ rk[i]);
        y = (temp << 1 | temp >> (16 - 1)) ^ x;
    }

    plain[0] = x;
    plain[1] = y;
}


/*
 * decrypt
 * cipherText: cipherText has just one block.
 * keys: round keys
 */
static void decrypt(u8 * cipherText, const u8 * keys, int ROUNDS) {

	u16 *cipher = (u16*)cipherText;
    const u16 *rk = (const u16*)keys;    
    
    u16 x = cipher[0], y = cipher[1];

    for(int i = ROUNDS - 1; i >= 0; i--) {
        u16 temp = x;
        x = y ^ ((temp << 1 | temp >> (16 - 1)) ^ (temp << 5 | temp >> (16 - 5)) ^ rk[i]);
        y = (temp << 1 | temp >> (16 - 1)) ^ x;
    }

    cipher[0] = x;
    cipher[1] = y;
}

