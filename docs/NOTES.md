
= User defined types and literals

http://en.cppreference.com/w/cpp/language/operators
http://en.cppreference.com/w/cpp/language/user_literal


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
