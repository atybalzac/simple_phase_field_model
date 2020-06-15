#pragma once
#define XSIZE 100
#define YSIZE 100

extern const double Gh;
extern const double Gdt;

extern const double GM;
extern const double GW;
extern const double GT;
extern const double Geps2;

extern double Gphi[XSIZE][YSIZE];

int checkbc(int i, int lambda);
double dfdphi(int i, int j);
double laplac(int i, int j);

