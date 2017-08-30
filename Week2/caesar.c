#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Error: Missing command-line argument\n");//return error if not 2 command line args
        return 1;
    }
    int k = atoi(argv[1]);//converts key from a string to an integer
    if (k < 0) {
        printf("Key must be a non-negative integer.\n");//return error if key is negative
        return 1;
    }
    printf("plaintext: ");
    string p = get_string();
    for (int i = 0, n = strlen(p); i < n; i++) {
        if (isalpha(p[i]) && (p[i] >= 'a' && p[i] <= 'z')) {//if letter is lowercase
            while (p[i] + k > 'z') {//check that adding key to each letter doesn't take it past the ASCII value for z. 
                p[i] -= 26;         //keep removing 26 until it is within appropriate ASCII value range
            }
            p[i] += k;//add value of key to each letter
        } 
        if (isalpha(p[i]) && (p[i] >= 'A' && p[i] <= 'Z')) {//if letter is uppercase
            while (p[i] + k > 'Z') {//check that adding key to each letter doesn't take it past the ASCII value for z. 
                p[i] -= 26;         //keep removing 26 until it is within appropriate ASCII value range
            }
            p[i] += k;//add value of key to each letter
        }
    }
    printf("ciphertext: %s\n", p);
}