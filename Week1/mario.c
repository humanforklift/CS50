#include <stdio.h>
#include <cs50.h>

void hash(int n);
void space(int n);

int main(void) {
    printf("Height: ");
    int height = get_int();
    
    while (height < 0 || height > 23) {
        printf("Height: ");
        height = get_int();
    }
   
    if (height > 0  && height < 24) {
        if (height == 0) {
            printf("");
        } else {
            for (int i = 0; i < height; i++) {
                space((height - 1) - i);
                hash(i);
                printf("##\n");
            }
        }
    }
}

    void space(int n) {
        int x = 0;
        while (n > x) {
            printf(" ");
            n--;
        }
    }
    
    void hash(int n) {
        int x = 1;
        while (n >= x) {
            printf("#");
            x++;
        }    
    }
