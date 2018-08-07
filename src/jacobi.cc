/*
 * Description:
 *
 * First created: 2018 Aug 07
 * Last modified: 2018 Aug 07
 *
 * Author: Yuankun Fu
 * e-mail: qoofyk@gmail.com
 */

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
}}
