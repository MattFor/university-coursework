#include <stdio.h>
#include <stdlib.h>

double **DajMac_1 (int n, int m)
{
	double **ma = (double**) malloc(n * sizeof(double*));

	for (int i = 0; i < n; i++)
    {
		ma[i] = (double*) malloc(m * sizeof(double));
	}

	return ma;
}

void CzytMac (FILE *fd, double **ma, int n, int m)
{
	for (int i = 0; i < n; i++)
  	{
		for (int j = 0; j < m; j++)
        {
			fscanf(fd, "%lf", &ma[i][j]);
		}
	}
}

void PiszMac (FILE *fw, double **ma, int n, int m)
{
	for (int i = 0; i < n; i++)
  	{
		for (int j = 0; j < m; j++)
        {
			fprintf(fw, "%lf ", ma[i][j]);
		}

		fprintf(fw, "\n");
	}
}
