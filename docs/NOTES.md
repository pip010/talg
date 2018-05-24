
= User defined types and literals

http://en.cppreference.com/w/cpp/language/operators
http://en.cppreference.com/w/cpp/language/user_literal

= Units based types ( compile time dimensional analysis)

Barton’s and Nackman’s approach to dimensional analysis:
http://se.ethz.ch/~meyer/publications/OTHERS/scott_meyers/dimensions.pdf

Boost.units
https://www.codeproject.com/Articles/988932/Boost-Units-Library

Current implementation derived from:
https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/

Alternative yet modern c++ approach:
https://github.com/nholthaus/units/blob/master/include/units.h

= TODO in order to support larger static/dynamic matrices

http://functionspace.com/articles/40/Cache-aware-Matrix-Multiplication---Naive-isn--039;t-that-bad-

```
n = 4096;
for(i=0;i<n;i++)
{
  for(k=0;k<n;k++)
  {
  for(j=0;j<n;j++)
    C[i][j]+=A[i][k]*B[k][j];
  }
}
```
