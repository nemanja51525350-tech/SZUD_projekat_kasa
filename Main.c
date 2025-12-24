#include <stdio.h>
#include <time.h>

#define MAX 50

typedef struct {
    char naziv[30];
    int kolicina;
    float cena;
} Artikal;

int main() {
    char tipKartice;
    float stanjeRacuna;
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

    printf("=== FISKALNA KASA ===\n");
    printf("Unesite broj artikala: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nArtikal %d\n", i + 1);
        printf("Naziv: ");
        scanf("%s", a[i].naziv);
        printf("Kolicina: ");
        scanf("%d", &a[i].kolicina);
        printf("Cena: ");
        scanf("%f", &a[i].cena);

        ukupno += a[i].kolicina * a[i].cena;
    }

    do {
        printf("\nDa li kupac placa kesom? (y/n): ");
        scanf(" %c", &kes);   // razmak ispred %c je bitan
    } while (kes != 'y' && kes != 'n');

    if (kes == 'y') {
        do {
            printf("Unesite koliko je kupac platio (RSD): ");
            scanf("%f", &uplata);

            if (uplata < ukupno)
                printf("Nedovoljno novca! Ukupno je %.2f RSD\n", ukupno);

        } while (uplata < ukupno);

        kusur = uplata - ukupno;
    }
    if (kes == 'n') {
        do {
            printf("Da li je kartica debitna ili kreditna? (d/k): ");
            scanf(" %c", &tipKartice);
        } while (tipKartice != 'd' && tipKartice != 'k');

        if (tipKartice == 'd') {
            do {
                printf("Unesite stanje na racunu (RSD): ");
                scanf("%f", &stanjeRacuna);

                if (stanjeRacuna < ukupno)
                    printf("Nedovoljno sredstava na racunu!\n");

            } while (stanjeRacuna < ukupno);

            stanjeRacuna -= ukupno;
        }
    }
    time(&t);

    fprintf(f, "\n=============================\n");
    fprintf(f, "FISKALNI RACUN\n");
    fprintf(f, "Datum: %s", ctime(&t));
    fprintf(f, "-----------------------------\n");
    fprintf(f, "Naziv\tKol\tCena\tIznos\n");

    for (i = 0; i < n; i++) {
        fprintf(f, "%s\t%d\t%.2f\t%.2f\n",
                a[i].naziv,
                a[i].kolicina,
                a[i].cena,
                a[i].kolicina * a[i].cena);
    }

    fprintf(f, "-----------------------------\n");
    fprintf(f, "UKUPNO: %.2f RSD\n", ukupno);

    if (kes == 'y') {
        fprintf(f, "Placanje: Kes\n");
        fprintf(f, "Placeno: %.2f RSD\n", uplata);
        fprintf(f, "Kusur: %.2f RSD\n", kusur);
    } else {
            fprintf(f, "Placanje: Kartica\n");
            if (tipKartice == 'd') {
                fprintf(f, "Tip kartice: Debitna\n");
                fprintf(f, "Preostalo stanje: %.2f RSD\n", stanjeRacuna);
            } else {
                fprintf(f, "Tip kartice: Kreditna\n");
            }
    }

    fprintf(f, "=============================\n");
    fclose(f);

    printf("\n=== RACUN ===\n");
    for (i = 0; i < n; i++) {
        printf("%s x%d = %.2f RSD\n",
               a[i].naziv,
               a[i].kolicina,
               a[i].kolicina * a[i].cena);
    }

    printf("UKUPNO: %.2f RSD\n", ukupno);

    if (kes == 'y') {
        printf("Placeno: %.2f RSD\n", uplata);
        printf("Kusur: %.2f RSD\n", kusur);
    } else if (kes == 'n') {       
        printf("Placanje: Kartica\n");
        if (tipKartice == 'd')
            printf("Preostalo stanje na racunu: %.2f RSD\n", stanjeRacuna);
        else
            printf("Tip kartice: Kreditna\n");
    }

    printf("Racun je sacuvan u fajlu Fisk.txt\n");
    printf("Ovo je kraj nasega problema\n");
    return 0;
}
