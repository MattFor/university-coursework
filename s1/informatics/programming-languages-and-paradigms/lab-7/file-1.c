//
// Created by MattFor on 19.12.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LL 200

extern void error( int, char *);
extern void argumenty (int, char **);
extern double *DajWekt (int n);
extern void CzytWekt (FILE *fd, double *we, int n);
extern void PiszWekt (FILE *fw, double *we, int n);
extern void DodWekt (double *w1, double *w2, double *w3, int n);
extern double IloczynSkal (double *w1, double *w2, int n);
extern double MaxElem (double *w, int n);

int main (int argc, char *argv[])
{
	FILE *fw, *fd;
	int n;

	argumenty(argc, argv);

	if (!(fd = fopen(argv[1], "r"))) error(2, "dane");
	if (!(fw = fopen(argv[2], "w"))) error(2, "wyniki");

	fscanf(fd, "%d", &n);

	double *x = DajWekt(n);
	double *y = DajWekt(n);
	double *z = DajWekt(n);

	CzytWekt(fd, x, n);
	CzytWekt(fd, y, n);

	DodWekt(x, y, z, n);

	double s = IloczynSkal(x, y, n);

	double mx = MaxElem(x, n);
	double my = MaxElem(y, n);

	PiszWekt(fw, z, n);
	fprintf(fw, "\nilocz.skal=%lf mx=%lf my=%lf\n", s, mx, my);

	free(x);
	free(y);
	free(z);

	fclose(fd);
	fclose(fw);

	return 0;
}
