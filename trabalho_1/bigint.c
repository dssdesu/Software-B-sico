/* Daniel Santana Souza 2310995 3WC */

#include "bigint.h"

/* função auxiliar usada em big_val*/
void dump(void *p, int n, BigInt res) {	/* para atribuir valor analisado a res */
	unsigned char *p1 = p;
	unsigned int a = 0;

	while (n--) {
		res[a] = *p1;						
		a++;
		p1++;
	}
}

/* Atribuição (com extensão) */
void big_val(BigInt res, long val) {
	unsigned int x = 8, y;		
				
	dump(&val, sizeof(val), res);	
	y = val >> 63; /* valor do último bit salvo em y*/
							
	while (x < 16){  /* bigint possui 16 bytes*/						
		res[x] = y;			
		x++;
	}
	return;
}

/* Operações Aritméticas ----------------------------------------------------------- */

/* res = -a */
void big_comp2(BigInt res, BigInt a) {
	unsigned int n = 0;
	BigInt n1, inverso;
	big_val(n1, 1);						
	
	while (n < 16){
		inverso[n] = ~a[n]; /* faz o complemento de todos os numeros */ 
		n++;
	}

	big_sum(res, inverso, n1); /* soma n (1) no inverso */
	return ;
}

/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b) {
	unsigned int soma, resto = 0, n = 0;			

	while (n < 16){
		soma = a[n] + b[n] + resto; /* soma dos bytes de a, b e resto */
		res[n] = soma % 256;						
		resto = (soma/256); /* salva o resto da soma seguinte */
		n++;
	}

	return;
}	

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b) {
	BigInt b_n; /* inicia um Bigint para comp2 de b (efetuar soma de a + (-b)) */

	big_comp2(b_n, b); /* comp 2 de b */
	big_sum(res, a, b_n);	/* a + (-b) */
	return;
}

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b) {
	int n = 0, n1 = 0, mult, resto, sh = 0;			
	BigInt x, y; /* Bigints auxiliares */
	big_val(res, 0); /* res = 0 */

	while (n < 16) { /* passa pelo y */								 
		resto = 0; /* resto = 0 em cada ciclo novo */
		n1 = 0;
		while(n1 < 16){ /* passa pelo x */
			mult = (a[n1]*b[n]) + resto; /* multiplica o a e o b e soma com o resto */
			resto = mult/256; /* resto = resto da multiplicacao */
			x[n1] = mult % 256; /* salva em x */
			n1++;
		}

		big_shl(y, x, sh); /* shift left para 'multiplicar por 10' cada multiplicacao */
		big_sum(res, res, y); /* soma a anterior com a nova multiplicacao */
		sh += 8; /* adiciona 8 para o proximo shift */
		n++;
	}
	
	return;
}

/* Operações de Deslocamento  */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n) {
	int x, y = 0, i = 0, j = 0;

	while(n > 8) { /* completa com zero a cada 8 bytes */
		res[i] = 0;
		i++;
		n -= 8; /* subtrai ja preenchidas */
	}

	while(i < 16) {								
		x = a[j] << (n); /* x guarda os n bits que vao ser delocados*/
		res[i] = x + y;	/* soma os bits de c e b ( b = sobra da soma anterior) */
		y = a[j] >> (8 - n); /* pego a sobra de a[i] para a proxima interacao */
		j++;
		i++;
	}

	return;
}

/* res = a >> n (lógico)*/
void big_shr (BigInt res, BigInt a, int n){
	int x, y = 0, i = 15, j = 15;

	while (n > 8) {	/* completa com zero de 8 em 8 bytes */
		res[i] = 0;
		i--;
		n -= 8; /* subtrai ja preenchidas */
	}

	while (i >= 0) {
		x = a[j] >> (n); /* x salva n bits que serao delocados*/
		res[i] = x + y;	/* soma os bits de x e y (y = resto da soma anterior) */
		y = a[j] << (8 - n); /* salva resto de a[j]*/
		i--;
		j--;
	}

	return;
}

/* res = a >> n (aritmético)*/
void big_sar (BigInt res, BigInt a, int n){
	int x, y = 0, a_ms, b_ms = 0, i = 15, j = 15;
	a_ms = a[15] >> 7; /* shift ate o ultimo bit para descobrir o mais significativo */
	if (a_ms == 1) {/* se o bit mais significativo for igual a 1 completa-se com FF */
		b_ms = 0xFF;
	}
	
	while (n > 8) { /* completa com ms de 8 em 8 bytes */
		res[i] = b_ms;
		i--;
		n -= 8; /* subtrai ja preenchidas */
	}

	y = b_ms << (8 - n);
	
	while ( i > -1) {
		x = a[j] >> (n); /* x salva n bits que serao delocados*/
		res[i] = x + y;	 /* soma os bits de x e y (y = resto da soma anterior) */
		y = a[j] << (8 - n); /* salva resto de a[j]*/
		i--;
		j--;
	}

	return;
}
