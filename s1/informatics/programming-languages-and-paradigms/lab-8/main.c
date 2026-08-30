#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

#define LL 20

FILE *fw, *fd;
extern void error (int, char *);
extern double *DajWekt (int);
extern double **DajMac_1 (int, int);
extern void DodMac (double **, double **, double **, int, int);
extern void Mac_x_Wekt (double **, double *, double *, int, int);
extern void CzytMac (FILE *, double **, int, int);
extern void PiszMac (FILE *, double **, int, int);
extern void PiszWekt (FILE *, double *, int);
extern void CzytWekt (FILE *, double *, int);

void argumenty(int argc, char *argv[]);

void calculateSumBelowDiagonal(int n, int B[n][n], int a, int b, int *sum)
{
	*sum = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (B[i][j] >= a && B[i][j] <= b)
			{
				*sum += B[i][j];
			}
		}
	}
}

int main (const int argc, char *argv[])
{
	int n, m;

	argumenty(argc, argv);

	if (!(fd = fopen(argv[1], "r")))
	{
		error(2, "dane");
	}

	if (!(fw = fopen(argv[2], "w")))
	{
		error(2, "wyniki");
	}

	fscanf(fd, "%d %d", &n, &m);

	double * x = DajWekt(m);
	double * y = DajWekt(m);

	double ** a = DajMac_1(n, m);
	double ** b = DajMac_1(n, m);
	double ** c = DajMac_1(n, m);

	CzytMac(fd, a, n, m);
	CzytMac(fd, b, n, m);
	CzytWekt(fd, x, m);

	DodMac(a, b, c, n, m);
	Mac_x_Wekt(a, x, y, n, m);

	printf("Macierz\n");
	PiszMac(stdout, c, n, m);
	fprintf(fw, "Macierz\n");
	PiszMac(fw, c, n, m);

	printf("Wektor\n");
	PiszWekt(stdout, y, n);
	fprintf(fw, "Wektor\n");
	PiszWekt(fw, y, n);

	int lower_limit, upper_limit;
	printf("Podaj przedział [a, b]:\n");
	printf("a = ");
	scanf("%d", &lower_limit);
	printf("b = ");
	scanf("%d", &upper_limit);

	auto int_matrix = malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		int_matrix[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
		{
			int_matrix[i][j] = (int)a[i][j];
		}
	}

	int sum = 0;
	calculateSumBelowDiagonal(n, int_matrix, lower_limit, upper_limit, &sum);

	printf("Suma elementów poniżej głównej przekątnej w przedziale [%d, %d] wynosi: %d\n", lower_limit, upper_limit, sum);

	double sum2 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((i == j && sin(a[i][j]) >= 0) || (j == n - i && sin(a[i][j]) >= 0.5))
			{
				sum2 += a[i][j];
			}
		}
	}

	printf("Suma elementów spełniających dziwny warunek wynosi: %f\n", sum2);

	for (int i = 0; i < n; i++)
	{
		free(int_matrix[i]);
	}
	free(int_matrix);

	fclose(fd);
	fclose(fw);
	return 0;
}

void argumenty(const int argc, char *argv[])
{
	if (argc != 3)
	{
		char *usage;
		int len = strlen(argv[0]) + 19;

		if (!(usage = (char*)malloc((unsigned)len * sizeof(char))))
		{
			error(3, "tablica usage");
		}

		strcpy(usage, argv[0]);
		strcat(usage, " file_in file_out");
		error(4, usage);
	}
}
