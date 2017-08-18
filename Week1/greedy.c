#include <stdio.h>
#include <cs50.h>

void find(int n);

int main(void) {
    printf("O hai! How much change is owed?\n");
    float change = get_float();
    int cents = (change + 0.005) * 100;//to correctly round to the amount of cents
    while (change < 0) {
        printf("How much change is owed?\n");
        change = get_float();
        cents = (change + 0.005) * 100;//to correctly round to the amount of cents
    }
    find(cents);
}

    void find(int n) {
        int x = 0;
        if (n < 25) {//if change due is less than 25c, increases amount of change to be more than  
            n += 25; //25c to run through loop, and takes 1 off the amount of the iterator
            x -= 1;
        }
        while (n > 0)  {
            x++;
            n -= 25;
            if (n - 25 < 0 && n > 0) {
                while (n > 0) {
                    x++;
                    n -= 10;
                    if (n - 10 < 0 && n > 0) {
                        while (n > 0) {
                        x++;
                        n -= 5;
                        if (n - 5 < 0 && n > 0) {
                            while (n > 0) {
                                x++;
                                n -= 1;
                                }
                            }
                        }                
                    }
                }
            }
        }
        printf("%i\n", x);
    }