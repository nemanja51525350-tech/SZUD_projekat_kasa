#include <stdio.h>
#include <time.h>

#define MAX 50

typedef struct {
    char naziv[30];
    int kolicina;
    float cena;
} Artikal;

int main() {
    FILE *f;
    Artikal a[MAX];
    int n, i;
    float ukupno = 0;
    char kes;
    float uplata = 0, kusur = 0;
    time_t t;

    f = fopen("Fisk.txt", "a");
    if (f == NULL) {
        printf("Greska pri otvaranju fajla!\n");
        return 1;
    }
