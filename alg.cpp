#include "alg.h"

double sqr (double x) {
    return x*x;
}

std::vector <double> solveLinear (matrix& x) {
    int n = x.size();
    int m = x[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (x[i][i] == 0) continue;
            double d = -x[j][i] / x[i][i];
            for (int k = 0; k < m; ++k) {
                x[j][k] += x[i][k] * d;
            }
        }
    }

    for (int i = n-1; i >= 0; --i) {
        for (int j = i-1; j >= 0; --j) {
            if (x[i][i] == 0) continue;
            double d = -x[j][i] / x[i][i];
            for (int k = 0; k < m; ++k) {
                x[j][k] += x[i][k] * d;
            }
        }
    }
    std::vector <double> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = x[i][m-1] / x[i][i];
    }
    return res;
}
