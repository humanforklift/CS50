#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int convert(char c);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Error: Check command-line arguments\n");//return error if not 2 command line args
        return 1;
    }
    string k = argv[1];
    int arr[strlen(k)];
    for (int i = 0, n = strlen(k); i < n; i++) {
        if (!isalpha(k[i])) {//returns error if any character in the key is not alphabetical
            printf("Keyword must only contain letters A-Z and a-z\n");
            return 1;
        } else {
            if (k[i] >= 'A' && k[i] <= 'Z') {//if i'th character of key is uppercase,
                arr[i] = k[i] - 'A';        //arr[i] is worth the value of i'th character minus 'A'
            } 
            if (k[i] >= 'a' && k[i] <= 'z') {//if i'th character of key is lowercase,
                arr[i] = k[i] - 'a';         //arr[i] is worth the value of i'th character minus 'a'
            }
        }
    }
        printf("plaintext: ");
    string p = get_string();
    int x = 0, y = 0, z = strlen(p), len = strlen(k);//create iterators to count loops of p & k
    while (x < z) {
        while (isalpha(p[x])) {
            if (y >= len) {                 //if y is more than the length of the key, 
                while ((y - (len)) > -1) {  //continue removing the length of the key from y
                    y -= (len);             //while the value of y remains positive.
                }
            }
            if (p[x] >= 'a' && p[x] <= 'z') {//if letter is lowercase
            while (p[x] + arr[y] > 'z') {//check that adding key to each letter doesn't take it past the ASCII value for z. 
                p[x] -= 26;             //keep removing 26 until it is within appropriate ASCII value range
            }
            p[x] += arr[y];//add value of key to each letter
            x++;
            y++;
        }  
            if (p[x] >= 'A' && p[x] <= 'Z') {//if letter is uppercase
            while (p[x] + arr[y] > 'Z') {//check that adding key to each letter doesn't take it past the ASCII value for z. 
                p[x] -= 26;              //keep removing 26 until it is within appropriate ASCII value range
            }
            p[x] += arr[y];//add value of key to each letter
            x++;
            y++;
            }
        }
        if (!isalpha(p[x])) {
            x++;
        }
    }
    printf("ciphertext: %s\n", p);
    return 0;
}
