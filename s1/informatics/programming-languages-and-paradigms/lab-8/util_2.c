#include <stdio.h>
#include <stdlib.h>

double *DajWekt (int n)
{
	double *wekt = (double *)malloc(n * sizeof(double));

	if (wekt == NULL)
    {
		perror("Błąd alokacji pamięci");
		exit(1);
	}

	return wekt;
}

void CzytWekt (FILE *fd, double *we, int n)
{
	for (int i = 0; i < n; i++)
  	{
		fscanf(fd, "%lf", &we[i]);
	}
}

void PiszWekt (FILE *fw, double *we, int n)
{
	for (int i = 0; i < n; i++)
  	{
		fprintf(fw, "%lf ", we[i]);

		if ((i + 1) % 5 == 0)
        {
			fprintf(fw, "\n");
		}
	}
}
