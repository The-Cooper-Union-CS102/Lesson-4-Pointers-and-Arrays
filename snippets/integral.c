#include <stdio.h> 
#include <math.h> 

double integral(double (*f)(double), double start, double end) {
    double eps = 1e-6;
    double result = 0;
    double x;
    for (x = start; x < end; x += eps) {
        result += f(x) * eps;
    }
    return result;
}

double inverse(double x) {
    return 1 / x;
}

int main() {
    double result = integral(&inverse, 1, 2);
    printf("Integral of 1/x from 1 to 2: %f\n", result);
    printf("ln(2): %f\n", log(2));
} 
