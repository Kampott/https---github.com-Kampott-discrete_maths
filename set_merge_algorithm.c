#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>

typedef struct Set {
    int data;
    struct Set* next;
} Set;

int main() {
    setlocale(LC_CTYPE, "Russian");
	system("chcp 1251");

    return 0;
}
