#pragma once
#define DLLEXP   __declspec( dllexport )
namespace Computations{
   DLLEXP void calleuro (double &ic, double &prix, int nb_samples, double T,
              double S0, double K, double sigma, double r); 
}