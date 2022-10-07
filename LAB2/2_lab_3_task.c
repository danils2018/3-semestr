#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>

#define epsilon (0.000000000000001)
#define pi_math (3.1415926535897932384626433)
/*
double eps(){
    double A = 1.0;
    while (A + 1.0 > 1.0){
        A /= 2;
    }
    return A;
}*/

double exponent_with_limit(){
    double exp = 2, _pred = 1;
    int n = 2;
    while(fabs(exp - _pred) > epsilon) {
        _pred = exp;
        exp = pow((1.0 + 1.0 / n), n);
        ++n;
    }
    return exp;
}

double exponent_with_sum(){
    double exp = 0, n = 0, pred_znach = -1;
    unsigned long long factorial = 1;
    while(fabs(exp - pred_znach) > epsilon) {
        pred_znach = exp;
        exp += (1.0 / factorial);
        factorial *= (++n);
    }
    return exp;
}

double bin_search_exp_with_equation(){
    double left = 2.0;
    double rigth = 3.0;
    while (fabs(left - rigth) > epsilon) {
        double middle = (left + rigth) / 2;
        if (log(middle) >= 1.0)
            rigth = middle;
        else
            left = middle;
    }
    return left;
}

double pi_with_limit(){
    double pi = -1, _pred = 0, help = 0;
    int n = 100000000;
    double doub_max = 10000.;
    double eps = epsilon * 100;
    while(/*fabs(pi - _pred) > eps*/ n <= 100000000) {
        _pred = pi;
        int flag = 1;
        help = 1.0 / sqrt(n);
        int ukaz_4 = 1;
        int ukaz_n_fact = 1;
        int ukaz_n2_fact = 1;
        int ukaz_2n_fact = 1;

        while (ukaz_4 <= n || ukaz_n_fact <= n || ukaz_n2_fact <= n ||  ukaz_2n_fact <= 2 * n) {
            while (help <= doub_max && ukaz_4 <= n) {
                help *= 4;
                ukaz_4++;
                flag = 0;
            }
            while (help <= doub_max && ukaz_n_fact <= n) {
                help *= ukaz_n_fact;
                ukaz_n_fact++;
                flag = 0;
            }

            while (help <= doub_max && ukaz_n2_fact <= n) {
                help *= ukaz_n2_fact;
                ukaz_n2_fact++;
                flag = 0;
            }

            while (help >= doub_max && ukaz_2n_fact <= 2 * n) {
                help /= ukaz_2n_fact;
                ukaz_2n_fact++;
                flag = 0;
            }

            if (flag) {
                if (ukaz_2n_fact <= 2 * n)
                {
                    help /= ukaz_2n_fact;
                    ukaz_2n_fact++;
                }
                if (ukaz_4 <= n)
                {
                    help *= 4;
                    ukaz_4++;
                }
                if (ukaz_n_fact <= n)
                {
                    help *= ukaz_n_fact;
                    ukaz_n_fact++;
                }
                if (ukaz_n2_fact <= n)
                {
                    help *= ukaz_n2_fact;
                    ukaz_n2_fact++;
                }


            }
            flag = 1;
            //printf("%d %.20lf %.20lf\n", n, pi, help);
        }
        pi = pow(help, 2);

        ++n;
    }

    return pi;
}

double pi_with_sum(){
    double pi = 1, pred_znach = 0;
    int n = 2;
    double eps = epsilon * 10000000;

    while(fabs(pi - pred_znach) > eps) {
        pred_znach = pi;
        pi += ((n % 2 == 0) ? (-1.0) : (1.0)) / (2.0 * n - 1);
        ++n;
    }
    return 4 * pi;
}

double bin_search_pi_with_equation(){ //через производную
    double left = 3.0;
    double rigth = 3.5;
    while (fabs(left - rigth) > epsilon) {
        double middle = (left + rigth) / 2;
        if (-sin(middle) > 0)
            rigth = middle;
        else
            left = middle;
    }
    return rigth;
}

double ln2_with_limit(){
    double ln2 = 2, _pred = 1;
    int n = 1;
    while(fabs(ln2 - _pred) > epsilon) {
        _pred = ln2;
        ln2 = n * (pow(2, 1./n) - 1);
        ++n;
    }
    return ln2;
}

double ln2_with_sum(){
    double ln2 = 1, pred_znach = 0;
    int n = 2;
    double eps = epsilon * 10000000;
    while(fabs(ln2 - pred_znach) > eps) {
        pred_znach = ln2;
        ln2 += ((n % 2 == 0) ? (-1.0) : (1.0)) / n;
        ++n;
    }
    return ln2;
}

double bin_search_ln2_with_equation(){
    double left = 0.0;
    double rigth = 1.0;
    while (fabs(left - rigth) > epsilon) {
        double middle = (left + rigth) / 2;
        if (exp(middle) >= 2.0)
            rigth = middle;
        else
            left = middle;
    }
    return left;
}

double sqrt2_with_limit(){
    double sqrt2 = -0.5, _pred = -2;

    while(fabs(sqrt2 - _pred) > epsilon) {
        _pred = sqrt2;
        sqrt2 = _pred - (_pred * _pred) / 2 + 1;
    }
    return sqrt2;
}

double sqrt2_with_proizv(){
    double sqrt2 = pow(2, pow(2, -2)), pred_znach = 0;
    int k = 3;
    while(fabs(sqrt2 - pred_znach) > epsilon) {
        pred_znach = sqrt2;
        sqrt2 *= pow(2, pow(2, -k));
        ++k;
    }
    return sqrt2;
}

double bin_search_sqrt2_with_equation(){
    double left = 1.0;
    double rigth = 2.0;
    while (fabs(left - rigth) > epsilon) {
        double middle = (left + rigth) / 2;
        if (middle * middle >= 2.0)
            rigth = middle;
        else
            left = middle;
    }
    return left;
}



double gamma_with_sum(){
    double gamma = 0, pred_znach = -1, sum_prom;
    int k = 2, flag = 1;
    double eps = epsilon / 10000;
    while(fabs(gamma - pred_znach) > eps || flag == 0) {
        pred_znach = gamma;
        sum_prom = (1.0 / (pow(floor(sqrt(k)), 2)) - 1. / k);
        if(sum_prom < eps) {
            flag = 0;
        } else {
            flag = 1;
        }
        gamma += sum_prom;
        ++k;
        //printf("%.18lf %.18lf\n", gamma, (- pi_math * pi_math) / 6 + gamma);
    }
    return (- pi_math * pi_math) / 6 + gamma;
}
/*
unsigned long long sochetania(int m, int k) {
    unsigned long long result = 1;
    int l = m - k;

    if (m - l > m - k) {
        for (int i = k + 1; i <= m; i++)
            result *= i;

        for (int i = 2; i <= l; i++)
            result /= i;
    } else {
        for (int i = l + 1; i <= m; i++)
            result *= i;

        for (int i = 2; i <= k; i++)
            result /= i;
    }

    return result;
}*/
/*
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}*/

double ln_factorial_(int k) {
    double mass_znach[] = {
            0.0,
            0.0,
            0.6931471805599453,
            1.791759469228055,
            3.1780538303479458,
            4.787491742782046,
            6.579251212010101,
            8.525161361065415,
            10.60460290274525,
            12.801827480081469,
            15.104412573075516,
            17.502307845873887,
            19.987214495661885,
            22.552163853123425,
            25.19122118273868,
            27.89927138384089,
            30.671860106080672,
            33.50507345013689,
            36.39544520803305,
            39.339884187199495,
            42.335616460753485,
            45.38013889847691,
            48.47118135183523,
            51.60667556776438,
            54.78472939811232,
            58.00360522298052,
            61.261701761002,
            64.55753862700634,
            67.88974313718154,
            71.25703896716801,
            74.65823634883016,
            78.0922235533153,
            81.55795945611504,
            85.05446701758152,
            88.58082754219768,
            92.1361756036871,
            95.7196945421432,
            99.33061245478743,
            102.96819861451381,
            106.63176026064346,
            110.32063971475739,
            114.0342117814617,
            117.77188139974507,
            121.53308151543864,
            125.3172711493569,
            129.12393363912722,
            132.95257503561632,
            136.80272263732635,
            140.67392364823425,
            144.5657439463449,
            148.47776695177302,
            152.40959258449735,
            156.3608363030788,
            160.3311282166309,
            164.32011226319517,
            168.32744544842765,
            172.3527971391628,
            176.39584840699735,
            180.45629141754378,
            184.53382886144948,
            188.6281734236716,
            192.7390472878449,
            196.86618167289,
            201.00931639928152,
            205.1681994826412,
            209.34258675253685,
            213.53224149456327,
            217.73693411395422,
            221.95644181913033,
            226.1905483237276,
            230.43904356577696,
            234.70172344281826,
            238.97838956183432,
            243.2688490029827,
            247.57291409618688,
            251.8904022097232,
            256.22113555000954,
            260.5649409718632,
            264.9216497985528,
            269.2910976510198,
            273.6731242856937,
            278.0675734403661,
            282.4742926876304,
            286.893133295427,
            291.3239500942703,
            295.76660135076065,
            300.22094864701415,
            304.6868567656687,
            309.1641935801469,
            313.65282994987905,
            318.1526396202093,
            322.66349912672615,
            327.1852877037752,
            331.7178871969285,
            336.26118197919845,
            340.815058870799,
            345.37940706226686,
            349.95411804077025,
            354.5390855194408,
            359.1342053695754
    };
    return mass_znach[k];
}

double sochetania_pascal(int m, int l) {
    ++m;
    long long** table_pascal = (long long **)malloc(sizeof(long long*) * m);
    int k = 1;
    for (int i = 0; i < m; ++i) {
        table_pascal[i] = (long long*)malloc(sizeof(long long) * k);
        for (int j = 0; j < k; ++j)
        {
            table_pascal[i][j] = (j == 0 || j == k - 1) ? (1) : (table_pascal[i - 1][j] + table_pascal[i - 1][j - 1]);
            //printf("%lld ", table_pascal[i][j]);
        }
        //printf("\n");
        ++k;
    }
    double x = (double)table_pascal[m - 1][l];

    for (int i = 0; i < m; ++i) {
        free(table_pascal[i]);
    }
    free(table_pascal);

    return x;
}

double gamma_with_limit(){
    double gamma = 0, _pred = -1, prom_znach;
    int m = 2;

    while(m < 47) {
        _pred = gamma;
        gamma = 0;
        for (int k = 1; k <= m; ++k)
        {
            prom_znach = sochetania_pascal(m, k);
            prom_znach *= ((k % 2 == 0) ? (1.0) : (-1.0));
            prom_znach /= k;
            prom_znach *= ln_factorial_(k);
            gamma += prom_znach;
        }
        ++m;
        //if (gamma - max_znach > epsilon && gamma - 1 < epsilon) max_znach = gamma;
        //printf("%d %.20lf\n",m ,  gamma);
    }
    return gamma;
}

double gamma_with_equation(){
    int* a = (int*)calloc(100000000, sizeof(int));
    for (int i = 2; i < 100000000; ++i) {
        if(!a[i])
            for (int j = i + i; j < 100000000; j += i) {
                a[j] = 1;
            }
    }

    double result_limit = 1, _pred_res_lim = 0, res_p = 0.5;
    int t = 3;
    while(t < 100000000) {
        _pred_res_lim = result_limit;

        if (!a[t])
            res_p *= ((double)t - 1.0) / (double)t;

        ++t;

    }
	result_limit = log(t) * res_p;
    free(a);

    return -log(result_limit);
}

int main(int argc, char *argv[]) {
    int l = 16;
    //printf("%lld\n", sochetania_pascal(30, 15));

    printf("Exponent with limit = %.*lf\n", l, exponent_with_limit());
    printf("Exponent with sum ryada = %.*lf\n", l, exponent_with_sum());
    printf("Exponent bin search = %.*lf\n", l, bin_search_exp_with_equation());
    printf("\n");
    printf("Pi with limit = %.*lf\n", l, pi_with_limit());
    printf("Pi with sum ryada = %.*lf\n", l, pi_with_sum());
    printf("Pi bin search = %.*lf\n", l, bin_search_pi_with_equation());
    printf("\n");
    printf("ln(2) with limit = %.*lf\n", l, ln2_with_limit());
    printf("ln(2) with sum ryada = %.*lf\n", l, ln2_with_sum());
    printf("ln(2) bin search = %.*lf\n", l, bin_search_ln2_with_equation());
    printf("\n");
    printf("sqrt(2) with limit = %.*lf\n", l, sqrt2_with_limit());
    printf("sqrt(2) with proizv ryada = %.*lf\n", l, sqrt2_with_proizv());
    printf("sqrt(2) bin search = %.*lf\n", l, bin_search_sqrt2_with_equation());
    printf("\n");
    printf("gamma with limit = %.*lf\n", l, gamma_with_limit());
    printf("gamma with sum ryada = %.*lf\n", l, gamma_with_sum());
    printf("gamma with equation = %.*lf\n", l, gamma_with_equation());
    printf("\n");
    return 0;

}
