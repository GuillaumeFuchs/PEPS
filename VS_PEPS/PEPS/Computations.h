#pragma once
#define DLLEXP __declspec ( dllexport ) 
namespace Moteur{
	DLLEXP void priceOption(double &ic, double &prix, int M, double T, double S0, double K, double sigma, double r, int size, int timeStep);
	DLLEXP void couvOption(double &pl, int M, double T, double S0, double K, double sigma, double r, int size, int timeStep);
}