#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;

namespace stat_mod_1 {

    const long double PI = acos(-1);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> urd(0, 1);

    double uniform() {
        return urd(gen);
    }

    int random_value() {
        long double u = uniform();
        long double p = 90 / pow(PI, 4);
        int n = 1;

        while (u > p) {
            u -= p;
            long double k = n;
            p *= pow(k / (k + 1), 4);
            n++;
        }

        return n;
    }


    double calculated_value_1() {
        double eps = 0.01;
        double D = 15 / (PI * PI) - 1;
        int N = ceil(9 * D / (eps * eps));
        double sum = 0;

        for (int i = 0; i < N; i++) {
            sum += random_value();
        }

        return sum / N;
    }

    double calculated_value_2() {
        double eps = 0.01;
        double M = pow(PI, 4) / 180;
        double D = M * M / 4;
        int N = ceil(9 * D / (eps * eps));
        double sum = 0;

        for (int i = 0; i < N; i++) {
            double n = random_value();
            sum += pow(PI, 4) / (90 * (n * n + 1));
        }

        return sum / N;
    }

    double multiple_integral_value(double a, double b) {
        double eps = 0.001;
        double d = sqrt(a) - 1;

        double sum = 0;
        double square_sum = 0;
        double n = 0;
        double estimated_N = 10000;

        while (n <= estimated_N) {
            double u = uniform();
            double z = (1 + d * u) * (1 + d * u);
            double value = 4 * PI * d * cos(b * z);

            sum += value;
            square_sum += value * value;
            n++;

            if (n < 10000) {
                continue;
            }

            double D = square_sum / (n - 1) - sum * sum / (n * (n - 1));
            estimated_N = 9 * D / (eps * eps);
        }

        return sum / n;
    }

}

int main() {
    double a, b;

    cout << "Введите a и b (1 < a, b < 10): ";
    cin >> a >> b;


    cout << fixed << setprecision(6);
    cout << "Задание 1.4.1: " << stat_mod_1::calculated_value_1() << '\n';
    cout << "Задание 1.4.2: " << stat_mod_1::calculated_value_2() << '\n';
    cout << "Задание 2.4: " << stat_mod_1::multiple_integral_value(a, b) << '\n';
    cout << "Выполнил Саар Т.В. МП-402" << '\n';
    return 0;
}
