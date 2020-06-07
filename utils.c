//
// Created by aayush on 6/7/20.
//

#include "utils.h"

void printLine(char *s) {
    printf("%s\n", s);
}

int scanInt(char *prompt) {
    printf("%s:\n", prompt);
    int result;
    scanf("%d", &result);
    return result;
}

