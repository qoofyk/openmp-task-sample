/*
 * Description:
 *
 * First created: 2018 Aug 07
 * Last modified: 2018 Aug 07
 *
 * Author: Yuankun Fu
 * e-mail: qoofyk@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "eval_tools.h"
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
   
    double *src, *dest;
    int i, N, loop_cnt;
    double s_initial, s_elapsed;
    int n, iterations;
    n = iterations = N = 256;

    //parse command line
    for (i = 1; i < argc; i++) {
      if (!strcmp(argv[i], "-size")) {
         N = atoi(argv[++i]);
      }
      if (!strcmp(argv[i], "-cnt")) {
         loop_cnt = atoi(argv[++i]);
      }
    }    

    printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
            " performance \n\n");
    src  = (double *)malloc( N*N*sizeof( double ));
    dest = (double *)malloc( N*N*sizeof( double ));
 
    printf (" Intializing matrix data \n\n");
    for (i = 0; i < (N*N); i++) {
        src[i] = (double)(i+1);
    }

    for (i = 0; i < (N*N); i++) {
        dest[i] = (double)(-i-1);
    }

    printf (" Measuring performance of Jacobi via OpenMP task interface");

    s_initial = get_cur_time();
#pragma omp parallel
{
#pragma omp single
{
    for(int i=0; i<iterations; i++) {
        for(int y=1; y<(n-1); ++y) {
#pragma omp task depend(in: src[x], src[x+n], src[x-n]) depend(out: dest[x])
            for(int x=(y*n)+1; x<(y*n)+n-1; ++x) {
                dest[x]=(src[x-n]+src[x+n]+src[x]+src[x-1]+src[x+1])*0.2;
            }
        }
        std::swap(dest, src);
    }
}
}

    s_elapsed = (get_cur_time() - s_initial);

        printf (" == Jacobi completed ==\n"
                " == %.2f seconds\n", s_elapsed);

    printf (" Example completed. \n\n");
    return 0;
}
