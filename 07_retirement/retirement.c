#include <stdio.h>
#include <stdlib.h>

typedef struct _retire_info
{
    int months;
    double contribution;
    double rate_of_return;
} retire_info;

double calculate(int age, double balance, retire_info acc) {
    for (int i = 0; i < acc.months; i++, age++) {
        printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, balance);
        balance += (balance * acc.rate_of_return / 12 + acc.contribution);
    }
    return balance;
}

void retirement(int startAge,        // in months
                double initial,      // initial savings in dollars
                retire_info working, // info about working
                retire_info retired) // info about being retired
{
    calculate(startAge + working.months, calculate(startAge, initial, working), retired);
    return;
}

int main(void)
{
    retire_info working = {489, 1000.0, 0.045};
    retire_info retired = {384, -4000.0, 0.01};
    retirement(327, 21345, working, retired);
    return EXIT_SUCCESS;
}