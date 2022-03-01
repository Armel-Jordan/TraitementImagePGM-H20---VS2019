#pragma once
class Util : public CDialog
{
public:
	Util();
	~Util();

	double** matrix(int nrl, int nrh, int ncl, int nch);
	void nrerror(char* m);
	void free_matrix(double** m, int nrl, int nrh, int ncl, int nch);
	double* vector(int nl, int nh);
	void free_vector(double* v, int nl, int nh);
	void svbksb(double** u, double w[], double** v, int m, int n, double b[], double x[]);
	void svdcmp(double** a, int m, int n, double* w, double** v);
};

