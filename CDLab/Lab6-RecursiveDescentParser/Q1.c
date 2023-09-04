/*
    S-> a | > | ( T )
    T-> T,S | S

    After removing left recursion,

    S-> a | > | ( T )
    T -> STprime
    Tprime -> ,STprime | ε
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void S();
void Tprime();
void T();

void invalid() {
    printf("Invalid string\n");
    exit(1);
}

void Tprime() {
    if (str[curr] == ',') {
        curr++;
        S();
        Tprime();
    }
}

void T() {
    S();
    Tprime();
}

void S() {
    if (str[curr] == 'a') {
        curr++;
        return;
    }
    else if (str[curr] == '>') {
        curr++;
        return;
    }
    else if (str[curr] == '(') {
        curr++;
        T();
        if (str[curr] == ')') {
            curr++;
            return;
        }
        else
            invalid();
    }
    else
        invalid();
}

void main() {

    // Sample strings: a, (a), ((a)), ((a),(a))

    printf("Enter string ");
    scanf("%s", str);
    strcat(str, "$");
    S();
    if (str[curr] == '$')
        printf("Valid string\n");
    else
        invalid();
}