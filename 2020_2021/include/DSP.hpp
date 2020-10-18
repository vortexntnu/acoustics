/**
 * @file
 * @brief Small library that implements some
 * DSP-functions to the acoustics for Vortex NTNU
 */
#ifndef ACOUSTICS_DSP_HPP
#define ACOUSTICS_DSP_HPP

//#include "../include/fourier.hpp" //Outdated
#include "../alglib/src/fasttransforms.h"

/**
 * @brief Namespace/wrapper for basic DSP
 * (digital signal processing) functions. 
 */
namespace DSP{

/**
 * @brief Constants. 
 * The frequencie (in robosub) will be 
 * in the range 20 KHz - 40 KHz.
 * The minimum sampling-frequency is therefore
 * 80 KHz, but increased to 100 KHz for safety.
 * 
 * The MAX_FREQUENCY and MIN_FREQUENCY are used 
 * for filtering the data in software. Every 
 * frequency above max or below min is noise
 */
const int SAMPLE_FREQUENCY = 100000;
const int MAX_FREQUENCY = SAMPLE_FREQUENCY / 2;
const int MIN_FREQUENCY = SAMPLE_FREQUENCY / 10;

/**
 * @brief Constants for estimating the frequency
 * spectrum. If the total number of samples is N,
 * N = num_freq_intervals * len_freq_intervals. 
 * 
 * @warning Increasing num_freq_intervals reduces 
 * the noise, however it decreases the spectral 
 * information. If the method is implemented, it 
 * is required to find a sweet-spot between noise 
 * and spectral information.
 */
const int num_freq_intervals = 128;
const int len_freq_intervals = 1024;
const int interval_total_len = num_freq_intervals 
            * len_freq_intervals;

/**
 * @brief Function to calculate the correlation
 * coeffisient between two different signals.
 * Runs in O(n) time.
 * Small modifications from 
 * https://www.geeksforgeeks.org/program-find-correlation-coefficient/
 * 
 * @param x_arr Array of signal 1
 * 
 * @param y_arr Array of signal 2
 * 
 * @param n Number of elements in each array
 * 
 * @warning Unsure if the function handles
 * complex values
 * 
 * @warning Must make sure that the lengths of
 * each array are identical
 * 
 * @warning outdated!
 */
double correlation_coefficient(
    int x_arr, int y_arr, int n);


/**
 * @brief Function to calculate the correlation
 * between to different signals
 * 
 * @param x_arr Array of signal 1
 * 
 * @param y_arr Array of signal 2
 * 
 * @param n Number of elements in each array
 * 
 * @warning Must be updated to apprehend 
 * lists of different lengths
 * 
 * @warning Not implemented as of 12.10.2020
 */
double correlation(double x_arr, double y_arr);


/**
 * @brief Function to calculate the lag of an
 * array. Finds the lag by detecting the highest
 * value in the argument. 
 * 
 * @param x_arr Discrete time array of a signal.
 * 
 * @warning Assumes that the array is of length
 * interval_total_len
 */
int find_lag(const alglib::complex_1d_array& x_arr);


/**
 * @brief Function to filter the signal between
 * the min and max frequency. Will therefore 
 * implement a band-pass filter in SW.
 * 
 * @param x_arr Reference to an array to be BP-
 * filtered
 */
void freq_filtering(alglib::complex_1d_array& x_arr);


/**
 * @brief Function to transfer a C-array of data 
 * and then transfer it to a complec_1d_array
 * for future DSP.
 * 
 * @param c_arr Pointer to a C-array to be transferred
 * 
 * @warning Assuming that the C-array has exactly 
 * interval_total_len length.
 */
void transfer_C_arr_to_alglib(int* c_arr, 
        alglib::complex_1d_array& x_arr);


} //DSP

#endif //ACOUSTICS_DSP_HPP