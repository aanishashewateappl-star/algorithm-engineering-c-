# algorithm-engineering-cplusplus-
It contains concepts learned in algorithm engineering course, coded in C++

### Union-Find (Disjoint Set Union)
Path compression + union by rank. Includes correctness tests and a
benchmark comparing performance with/without each optimization.

**Result:** on 1M random unite operations over 1M elements:
| Version | Time |
|---|---|
| Both optimizations | 92.6 ms |
| No path compression | 151.7 ms |
| No union by rank | 114.0 ms |
| Neither (adversarial chain input) | Program did not end|

Demonstrates that path compression and union by rank are complementary —
removing either alone causes a moderate slowdown, but removing both leads
to much worse degradation under adversarial input patterns.

## Build

```
g++ union-find.cpp -o test.exe
./test.exe
```

