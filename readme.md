A quick test of random uint32_ts shows ska_sort to be a pretty good contender to std::sort
```
| relative |               ns/op |                op/s |    err% |     total | benchmark
|---------:|--------------------:|--------------------:|--------:|----------:|:----------
|   100.0% |           40,933.50 |           24,429.87 |    2.1% |      6.31 | `std::sort (1024)`
|   191.9% |           21,330.61 |           46,880.98 |    2.6% |      3.63 | `ska_sort (1024)`
|    45.2% |           90,465.04 |           11,053.99 |    2.9% |     14.27 | `std::sort (2048)`
|   107.9% |           37,949.55 |           26,350.78 |    2.3% |      6.18 | `ska_sort (2048)`
|    20.7% |          197,980.41 |            5,051.00 |    0.9% |     31.42 | `std::sort (4096)`
|    55.8% |           73,383.39 |           13,627.06 |    1.2% |     11.62 | `ska_sort (4096)`
|     9.5% |          429,216.33 |            2,329.83 |    3.6% |     67.30 | `std::sort (8192)`
|    24.5% |          166,805.19 |            5,995.02 |    1.1% |     25.37 | `ska_sort (8192)`
|     4.1% |        1,005,914.29 |              994.12 |    8.8% |    150.00 | :wavy_dash: `std::sort (16384)` (Unstable with ~141.0 iters. Increase `minEpochIterations` to e.g. 1410)
|     9.4% |          436,117.55 |            2,292.96 |    6.2% |     69.67 | :wavy_dash: `ska_sort (16384)` (Unstable with ~141.0 iters. Increase `minEpochIterations` to e.g. 1410)
|     1.8% |        2,290,442.35 |              436.60 |    7.7% |    335.44 | :wavy_dash: `std::sort (32768)` (Unstable with ~141.0 iters. Increase `minEpochIterations` to e.g. 1410)
|     4.0% |        1,011,089.53 |              989.03 |   10.4% |    149.95 | :wavy_dash: `ska_sort (32768)` (Unstable with ~141.0 iters. Increase `minEpochIterations` to e.g. 1410)
```
