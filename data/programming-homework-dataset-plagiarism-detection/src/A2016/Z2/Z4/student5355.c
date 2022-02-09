#include <stdio.h>
#include <math.h>
#define vel 100
int main() {
	int M =1, N = 1, t = 1, c = 1, i = 0, j = 0;
	double mat[vel][vel] = {} ;
	do {
		printf ("Unesite M i N: ");
		scanf ("%d %d", &M, &N);
		if (M < 1 || M > 100 || N < 1 || N > 100) printf ("Pogresan unos!\n");
	} while (M < 1 || M > 100 || N < 1 || N > 100);
	printf ("Unesite elemente matrice: ");
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			scanf ("%lf", &mat[i][j]);
		}
	}
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			if (mat[i][j] != mat[i+1][j+1] && i != M-1 && j != N-1) t = 0; 
		}
	}
	if (t == 1) {
		for (i = 0; i < M; i++) {
			for (j = 0; j < N; j++) {
				if (mat[i][N-1] != mat[i+1][0] && i != M-1 && j != N-1) c = 0; 
			}
		}
	}
	if (t == 1 && c == 0) printf ("Matrica je Teplicova");
	else if (c == 1 && t == 1) printf ("Matrica je cirkularna");
	else if (t == 0) printf ("Matrica nije ni cirkularna ni Teplicova");
	return 0;
}
