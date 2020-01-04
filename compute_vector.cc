
#include <compute_vector.h>


/*
 * Algorithms
 */

double staticPower  = 10 ;
double constant     = 10 ;
double timeInterval = 10 ;

double Pmax = 20 ;  // Pmax_minus_Pmin == constant == 10
double Pmin = 10 ;  // Pmin == P_idle == staticPower

// CUBIC
double calculateConsumption_CUBIC ( int id, int n_eltos, float *utilization )
{
    double consumption = 0 ;
    for (int i=0; i<n_eltos; i++) {
         consumption += (staticPower + constant * pow(utilization[i], 3)) * timeInterval;
    }
    return consumption;
}

// Linear
double calculateConsumption_LINEAR ( int id, int n_eltos, float *utilization )
{
    double consumption = 0 ;
    for (int i=0; i<n_eltos; i++) {
         consumption += (staticPower + constant * utilization[i]) * timeInterval;
    }
    return consumption;
}

// Square
double calculateConsumption_SQUARE ( int id, int n_eltos, float *utilization )
{
    double consumption = 0 ;
    for (int i=0; i<n_eltos; i++) {
         consumption += (staticPower + constant * pow(utilization[i], 2)) * timeInterval;
    }
    return consumption;
}

// SQRT
double calculateConsumption_SQRT ( int id, int n_eltos, float *utilization )
{
    double consumption = 0 ;
    for (int i=0; i<n_eltos; i++) {
         consumption += (staticPower + constant * sqrt(utilization[i])) * timeInterval;
    }
    return consumption;
}

// PM1: SPEC Benchmarking Software (WP7_Slides...)
double calculateConsumption_PM1 ( int id, int n_eltos, float *utilization )
{
    double consumption = 0 ;

    for (int i=0; i<n_eltos; i++)
    {
       consumption += (
                        Pmin +
                        ((Pmax - Pmin) / 100.0) * utilization[i] +
                        (Pmin / 2.0) * sin((2.0 * M_PI / 100.0) * utilization[i])
                      ) * timeInterval ;
    }
    return consumption;
}

// PM2: SPEC Benchmarking Software (WP7_Slides...)
double calculateConsumption_PM2 ( int id, int n_eltos, float *utilization )
{
    double consumption = 0 ;

    for (int i=0; i<n_eltos; i++)
    {
       consumption += (
                        ((11.0/27.0)*Pmax - (7.0/6.0)*Pmin) * pow(2.0*utilization[i]-1.0, 3) +
                        ((2.0)*Pmin       - (2.0/9.0)*Pmax) * pow(utilization[i],         2) +
                        ((11.0/27.0)*Pmax - (2.0/3.0)*Pmin) * utilization[i] +
                         (11.0/27.0)*Pmax - (1.0/6.0)*Pmin
                      ) * timeInterval ;
    }
    return consumption;
}

