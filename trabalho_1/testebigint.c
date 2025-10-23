/* Daniel Santana Souza 2310995 3WC */

#include <stdio.h>
#include "bigint.h"

void big_print(BigInt res){
	int n = 16;
	while(n--)
		printf("%02x", res[n]);
	printf("\n");
}

int main (void){

	long num1 = 258;    // Representação: 0x00...0102
	long num2 = -5;     // Representação: 0xFF...FB
	long num3 = 10;     // Representação: 0x00...0A

	BigInt val1, val2, val3;
	BigInt res_sum, res_sub, res_mul, res_comp2;
	BigInt res_shl, res_shr, res_sar;

	/* ======= Fazendo os bigints ======= */
	big_val(val1, num1);
	big_val(val2, num2);
	big_val(val3, num3);

	/* ======= Testando as funções e imprimindo ======= */

	printf("\n\n_______ SOMA: 258 + (-5) = 253 _______\n");
	big_sum(res_sum, val1, val2);
	printf("Valor 1: "); big_print(val1);
	printf("Valor 2: "); big_print(val2);
	printf("Soma:    "); big_print(res_sum);

	printf("\n\n_______ SUBTRAÇÃO: 258 - 10 = 248 _______\n");
	big_sub(res_sub, val1, val3);
	printf("Valor 1: "); big_print(val1);
	printf("Valor 3: "); big_print(val3);
	printf("Subtr:   "); big_print(res_sub);

	printf("\n\n_______ MULTIPLICAÇÃO: (-5) * 10 = -50 _______\n");
	big_mul(res_mul, val2, val3);
	printf("Valor 2: "); big_print(val2);
	printf("Valor 3: "); big_print(val3);
	printf("Multip:  "); big_print(res_mul);

	printf("\n\n_______ COMPLEMENTO DE 2: -(-5) = 5 _______\n");
	big_comp2(res_comp2, val2);
	printf("Valor 2:      "); big_print(val2);
	printf("Complemento:  "); big_print(res_comp2);

	printf("\n\n_______ SHIFT LEFT: 258 << 9 _______\n");
	big_shl(res_shl, val1, 9);
	printf("Valor 1 (antes):  "); big_print(val1);
	printf("Shift Left por 9: "); big_print(res_shl);

	printf("\n\n_______ SHIFT RIGHT (LÓGICO): 258 >> 2 _______\n");
	big_shr(res_shr, val1, 2);
	printf("Valor 1 (antes):    "); big_print(val1);
	printf("Shift Right por 2:  "); big_print(res_shr);
	
	printf("\n\n_______ SHIFT RIGHT (ARITMÉTICO): -5 >> 1 _______\n");
	big_sar(res_sar, val2, 1);
	printf("Valor 2 (antes):    "); big_print(val2);
	printf("Shift Aritm por 1:  "); big_print(res_sar);

	printf("\n");
	return 0;
}
