#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * How to identify minium changes:
 *      for over-paid, they should firstly reach to avg+1 level
 *      for low-paid, they should reach to avg level
 *      consider that total money = avg*n+r, r is how many people should reach avg+1 level
 *      if over-paid persons number is x, if x > r, then low-paid only need to avg level,
 *      if x < r, means low-paid some ones should pay 1 more cent to others
 *      Optimization: use a bucket to store put-in(low-paid) and put-out(over-paid) money,
 *                    if bucket > 0, means low-paid should pay more
 */

int main(int argc, char* argv[])
{
    int students[1000];
    int i, n;
    double temp;
    int avg;
    int local, ret;

    while (scanf("%d", &n) != EOF) {
        if (n == 0)
            break;

        for (i = 0; i < n; i++) {
            scanf("%lf", &temp);
            temp *= 100;
            students[i] = (int)(temp+0.5);
            /*tricky way to convert double to int, double is approximately accurate
             * if use (int)(temp) may get wrong answer, need roundup, or use internal function. ex, 278.78
             */
        }

        local = 0;
        for (i = 0; i < n; i++)
            local += students[i];

        avg = local/n;

        local = 0;
        ret = 0;
        for (i = 0; i < n; i++) {
            if (students[i] < avg) {
                local += (avg-students[i]);
            }
            else if(students[i] > avg+1) {
                local -= (students[i]-avg-1);
                ret += (students[i]-avg-1);
            }
        }
        if (local > 0)
            ret += local;

        printf("$%.2lf\n", (double)ret/100);
    }

    return 0;
}
