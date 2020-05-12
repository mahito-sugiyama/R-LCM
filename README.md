# R-LCM
This is an R wrapper for LCM (Linear time Closed itemset Miner) ver.5.

## Usage
First, get LCM 5.3.

1. Download the source code at [http://research.nii.ac.jp/~uno/code/lcm53.zip](http://research.nii.ac.jp/~uno/code/lcm53.zip).
2. Compile it, which is written in C.
3. Put the executable file `lcm` at the same directly 
with `r_lcm.cc`.

In R, load the Rcpp program as:

```
> require(Rcpp)
> sourceCpp("r_lcm.cc")
```

Then you can use the lcm by the function `lcm` in R.

## Example
An input file should be a binary matrix.
For example, 

```
> X_rows <- 10; X_cols <- 5; set.seed(1)
> X <- matrix(sample(c(0, 1), X_rows * X_cols, replace = TRUE, prob = c(.4, .6)), ncol = X_cols)
> X
     [,1] [,2] [,3] [,4] [,5]
 [1,]    1    1    0    1    0
 [2,]    1    1    1    1    0
 [3,]    1    0    0    1    0
 [4,]    0    1    1    1    1
 [5,]    1    0    1    0    1
 [6,]    0    1    1    0    0
 [7,]    0    0    1    0    1
 [8,]    0    0    1    1    1
 [9,]    0    1    0    0    0
[10,]    1    0    1    1    0
```

Each row and column in `X` corresponds to a transaction and an item, respectively, and *x<sub>ij</sub>* = 1 if the *i*th transaction has the item *j*.

Run LCM by the following command, where "tmp" is the file name that is used to prepare input and output files to `lcm` and "freq" is the minimum frequency threshold.

```
> res <- lcm(X, "tmp", freq = 0.3)

```

Frequent itemsets are stored in `res$itemset` as follows, where each vector is a frequent itemset:

```
> res$itemset
[[1]]
integer(0)

[[2]]
[1] 2

[[3]]
[1] 3

[[4]]
[1] 2 3

[[5]]
[1] 0

[[6]]
[1] 0 2

[[7]]
[1] 0 3

[[8]]
[1] 1

[[9]]
[1] 1 2

[[10]]
[1] 1 3

[[11]]
[1] 2 4
```

Their supports are stored in `res$supports`.

```
> res$supports
 [1] 10  7  6  4  5  3  4  5  3  3  4
```

## Arguments
- `X`: An input binary matrix
- `file_name`: A file name for temporary files
- `freq`: minimum frequency threshold (real number from 0 to 1)
- `len_min`: the minimum size of a frequent itemset (default: 0)
- `len_max`: the maximum size of a frequent itemset (default: unlimited)
