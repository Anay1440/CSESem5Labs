/*
    S -> UVW
    U -> (S) | aSb | d
    V -> aV | ε
    W -> cW | ε
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void S();
void U();
void V();
void W();

void invalid() {
    printf("Invalid string\n");
    exit(1);
}

void W() {
    if (str[curr] == 'c') {
        curr++;
        W();
    }
}

void V() {
    if (str[curr] == 'a') {
        curr++;
        V();
    }
}

void U() {
    if (str[curr] == '(') {
        curr++;
        S();
        if (str[curr] == ')') {
            curr++;
            return;
        }
        else
            invalid();
    }
    else if (str[curr] == 'a') {
        curr++;
        S();
        if (str[curr] == 'b') {
            curr++;
            return;
        }
        else
            invalid();
    }
    else if (str[curr] == 'd') {
        curr++;
        return;
    }
    else
        invalid();
}

void S() {
    U();
    V();
    W();
}

void main() {

    // Sample strings: dac, (dac), adacccb

    printf("Enter string ");
    scanf("%s", str);
    strcat(str, "$");
    S();
    if (str[curr] == '$')
        printf("Valid string\n");
    else
        invalid();
}