#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

volatile DWORD dwStart;
volatile int global = 0;

double test2(int num_steps) {
	int i;
	global++;
	double x, pi, sum = 0.0, step;

	step = 1.0 / (double) num_steps;

#pragma omp parallel for reduction(+:sum) private(x)
	for (i = 1; i <= num_steps; i++) {
		x = (i - 0.5) * step;
		sum = sum + 4.0 / (1.0 + x*x);
	}

	pi = step * sum;
	return pi;
}

int main(int argc, char* argv[]) {
	typedef struct _matrix Matrix;
	struct _matrix
	{
		double *ptr;
		int m;
		int n;
	};

	Matrix *M = new Matrix();
	printf("%d\n%d\n%d\n%d\n", M, sizeof(double), &(M->n), &(M->m));
	printf("\n");
	M->m = 2;
	M->n = 2;
	M->ptr = new double();
	(M->ptr)[0] = 0.;
	(M->ptr)[1] = 1.;
	(M->ptr)[2] = 2.;
	(M->ptr)[3] = 3.;
	printf("%p\n%p\n%p\n%d\n", M, M, &(M->n), sizeof(M));
	system("pause");
	/*
	double   d;
	int n = 1000000;

#pragma omp parallel
	{
#pragma omp for
		for (int i=0 ; i<n ; i++ )
			printf("thread : %d, loop : %d\n",
			omp_get_thread_num(), i);
	}

	if (argc > 1)
		n = atoi(argv[1]);

	dwStart = GetTickCount();
	d = test2(n);
	printf_s("For %d steps, pi = %.15f, %d milliseconds\n", n, d, GetTickCount() - dwStart);

	dwStart = GetTickCount();
	d = test2(n);
	printf_s("For %d steps, pi = %.15f, %d milliseconds\n", n, d, GetTickCount() - dwStart);

	system("pause");
	*/
}