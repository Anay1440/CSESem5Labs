/*
    S -> aAcBe
    A -> Ab | b
    B -> d

    After removing left recursion,

    S -> aAcBe
    A -> bAprime
    Aprime -> bAprime | ε
    B -> d
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void S();
void A();
void Aprime();
void B();

void invalid() {
    printf("Invalid string\n");
    exit(1);
}

void B() {
    if (str[curr] == 'd') {
        curr++;
        return;
    }
    else
        invalid();
}

void Aprime() {
    if (str[curr] == 'b') {
        curr++;
        Aprime();
    }
}

void A() {
    if (str[curr] == 'b') {
        curr++;
        Aprime();
    }
    else
        invalid();
}

void S() {
    if (str[curr] == 'a') {
        curr++;
        A();
        if (str[curr] == 'c') {
            curr++;
            B();
            if (str[curr] == 'e') {
                curr++;
                return;
            }
        }
        else
            invalid();
    }
    else
        invalid();
}

void main() {

    // Sample strings: abcde, abbbbbbbcde

    printf("Enter string ");
    scanf("%s", str);
    strcat(str, "$");
    S();
    if (str[curr] == '$')
        printf("Valid string\n");
    else
        invalid();
}