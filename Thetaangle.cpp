#include <stdio.h>
#include <math.h>

	int n = 100, m = 100;

	double integral (double alfa, double int_fi, double int_cos, double M[101][100]);
	double cosseno_teta (double alfa, double cos1, double beta);
	double angulo_fi (double alfa, double cos1, double fi1, double beta);
	double intervalo_cos (void);
	double intervalo_fi (void);
	void leitura (double M[101][100]);

int main (void) {
	
	int i;
	double C, alfa, int_alfa;
	double int_fi, int_cos;
	double M[101][100];
	FILE *fw = fopen("Ctheta100.txt", "w");		//Ctheta_n.txt
	
	int_fi = intervalo_fi();
	int_cos = intervalo_cos();
	int_alfa = M_PI/n;
	leitura(M);

	for (i = 0; i <= n; i++) {
		alfa = i*M_PI/n;
		C = integral(alfa, int_fi, int_cos, M);
		printf("%.20e\t%.20e\n", alfa, C);
		fprintf(fw, "%.20e\t%.20e\n", alfa, C);
	}
	fclose(fw);
	return 0;
}

double integral (double alfa, double int_fi, double int_cos, double M[101][100]) {

	int i, j, k;
	double cos1, fi1, T1;
	double cos2, fi2, T2;
	double beta, C = 0.0, C_aux;
	FILE *fr = fopen("fort.99", "r");

	for (i = 1; i <= 101; i++) {
		for (j = 1; j <= 100; j++) {
			
			C_aux = 0.0;
			fscanf(fr, "%lf %lf %lf", &cos1, &fi1, &T1);

			for (k = 0; k <= m; k++) {
				beta = k*2.0*M_PI/m;

				if (alfa == 0.0)
					T2 = T1;
				else {
					cos2 = cosseno_teta(alfa, cos1, beta);
					fi2 = angulo_fi(alfa, cos1, fi1, beta);
					T2 = M[(int)round((cos2 + 1.0)/int_cos)][(int)round(fi2/int_fi)];
				}

				if (k == 0 || k == m)
					C_aux += T2/2.0;
				else
					C_aux += T2;
			}

			if (i == 1 || i == 101) {
				if (j == 1 || j == 100)
					C += C_aux*T1/4.0;
				else
					C += C_aux*T1/2.0;
			}
			else {
				if (j == 1 || j == 100)
					C += C_aux*T1/2.0;
				else
					C += C_aux*T1;
			}
		}
	}
	fclose(fr);
	C = C*int_cos*int_fi/(4.0*M_PI*m);
	return C;
}

void leitura (double M[101][100]) {

	FILE *fr = fopen("fort.99", "r");
	double cos, fi, T;
	int i, j;

	for (i = 0; i < 101; i++) {
		for (j = 0; j < 100; j++) {
			fscanf(fr, "%lf %lf %lf", &cos, &fi, &T);
			M[i][j] = T;
		}
	}
	fclose(fr);
}

double cosseno_teta (double alfa, double cos1, double beta) {

	double z;
	double cos2, tan_alfa;
	
	if (alfa > M_PI/2.0 - 0.0001 && alfa < M_PI/2.0 + 0.0001)
		cos2 = (-1)*cos(beta)*sqrt(1.0 - cos1*cos1);
	else if (alfa > M_PI - 0.0001)
		return -cos1;
	else {
		tan_alfa = fabs(tan(alfa));
		z = cos1 - tan_alfa*cos(beta)*sqrt(1.0 - cos1*cos1);
		cos2 = z/(sqrt(1.0 + tan_alfa*tan_alfa));
	}

	if (alfa <= M_PI/2.0)
		return cos2;
	else
		return -cos2;
}

double angulo_fi (double alfa, double cos1, double fi1, double beta) {
	
	double x, y;
	double fi2, tan_alfa;

	if (alfa > M_PI/2.0 - 0.0001 && alfa < M_PI/2.0 + 0.0001) {
		x = cos(beta)*cos1*cos(fi1) - sin(beta)*sin(fi1);
		y = cos(beta)*cos1*sin(fi1) + sin(beta)*cos(fi1);
	}
	else if (alfa > M_PI - 0.0001) {
		fi2 = M_PI + fi1;
		if (fi2 < 2.0*M_PI)
			return fi2;
		else
			return fi2 - 2.0*M_PI;
	} 
	else {
		tan_alfa = fabs(tan(alfa));
		x = sqrt(1.0 - cos1*cos1)*cos(fi1) + tan_alfa*(cos(beta)*cos1*cos(fi1) - sin(beta)*sin(fi1));
		y = sqrt(1.0 - cos1*cos1)*sin(fi1) + tan_alfa*(cos(beta)*cos1*sin(fi1) + sin(beta)*cos(fi1));
	}
	fi2 = atan(y/x);
	
	if (x >= 0.0) {
		if (y < 0.0)
			fi2 += 2.0*M_PI;
	}
	else
		fi2 += M_PI;

	if (alfa <= M_PI/2.0)
		return fi2;
	else {
		fi2 += M_PI;
		if (fi2 < 2.0*M_PI)
			return fi2;
		else
			return fi2 - 2.0*M_PI;
	}
}

double intervalo_fi (void) {

	double cos, fi1, fi2, T;
	FILE *fr = fopen("fort.99", "r");
	
	fscanf(fr, "%lf %lf %lf", &cos, &fi1, &T);
	fscanf(fr, "%lf %lf %lf", &cos, &fi2, &T);
	fclose(fr);

	return fi2 - fi1;
}

double intervalo_cos (void) {

	double cos1, cos2, fi, T;
	FILE *fr = fopen("fort.99", "r");

	fscanf(fr, "%lf %lf %lf", &cos1, &fi, &T);
	fscanf(fr, "%lf %lf %lf", &cos2, &fi, &T);

	while (cos2 == cos1) 
		fscanf(fr, "%lf %lf %lf", &cos2, &fi, &T);
	fclose(fr);

	return cos2 - cos1;
}
