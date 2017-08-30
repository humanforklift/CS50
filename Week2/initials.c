#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(void) {
    string fullName = get_string();
    if (fullName != NULL) {
        printf("%c", toupper(fullName[0]));//print first letter of name
        for (int i = 0, n = strlen(fullName); i < n; i++) {
            if (fullName[i] == (char)32) {//if the ith character is a space
                printf("%c", toupper(fullName[i + 1]));//convert to upper case and print the 1st character after the space
            }
        }
        printf("\n");
    }
}