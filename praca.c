#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct produkt {
    char nazwa[50];
    char kategoria[30];
    char producent[30];
    float cena;
    float waga;
};

void wczytywanie_produktow(struct produkt produkty[], int *rozmiar, const char *nazwapliku) {
    FILE *plik = fopen(nazwapliku, "r");

    if (plik == NULL) {
        printf("Nie udalo się otworzyc pliku z produktami %s\n", nazwapliku);
        exit(EXIT_FAILURE);
    }

    fscanf(plik, "%d", rozmiar);

    for (int i = 0; i < *rozmiar; ++i) {
        fscanf(plik, "%s %s %s %f %f", produkty[i].nazwa, produkty[i].kategoria, produkty[i].producent, &produkty[i].cena, &produkty[i].waga);
    }

    fclose(plik);
}

void wypisanie_prod(struct produkt produkty[], int rozmiar) {
    printf("Produkty:\n");
    for (int i = 0; i < rozmiar; ++i) {
        printf("%d:", i + 1);
        printf("| %s |", produkty[i].nazwa);
        printf(" %s |", produkty[i].kategoria);
        printf(" %s |", produkty[i].producent);
        printf(" Cena: %.2f |", produkty[i].cena);
        printf(" Waga: %.2f |", produkty[i].waga);
        printf("\n");
    }
    printf("\n");
}

void najmiej_kupowane(struct produkt produkty[], int rozmiar) {
    int indeksnk = 0;

    for (int i = 0; i < rozmiar; ++i) {
        if (produkty[i].waga < produkty[indeksnk].waga) {
            indeksnk = i;
        }
    }

    printf("Najmniej kupowany produkt:");
    printf("| %s |", produkty[indeksnk].nazwa);
    printf(" %s |", produkty[indeksnk].kategoria);
    printf(" %s |", produkty[indeksnk].producent);
    printf(" Cena: %.2f |", produkty[indeksnk].cena);
    printf(" Waga: %.2f |", produkty[indeksnk].waga);
    printf("\n\n");
}

void srednia_wartosc(struct produkt produkty[], int rozmiar) {
    char kategorie[5][16] = {"pieczywo", "owoce", "warzywa", "dodatki", "napoje"};
    int ilosc_produktow[5] = {0, 0, 0, 0, 0};
    float suma_wartosci[5] = {0, 0, 0, 0, 0};

    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (strcmp(produkty[i].kategoria, kategorie[j]) == 0) {
                ilosc_produktow[j]++;

                suma_wartosci[j] += produkty[i].cena * produkty[i].waga;
            }
        }
    }

    printf("Srednia wartosc produktow:\n\n");

    for (int j = 0; j < 5; ++j) {
        if (ilosc_produktow[j] > 0) {
            printf("Kategoria: %s -> %.2f\n", kategorie[j], suma_wartosci[j] / ilosc_produktow[j]);
        }
    }

    printf("\n");
}

int main() {
    int max = 100;
    struct produkt produkty[max];
    int rozmiar;

    wczytywanie_produktow(produkty, &rozmiar, "produkty.txt");
    wypisanie_prod(produkty, rozmiar);
    najmiej_kupowane(produkty, rozmiar);

    srednia_wartosc(produkty, rozmiar);

    float suma_cen = 0;
    for (int i = 0; i < rozmiar; ++i) {
        suma_cen += produkty[i].cena * produkty[i].waga;
    }
    float srednia_cena = suma_cen / rozmiar;

    FILE *plik2 = fopen("drugi_plik.txt", "w");
    for (int i = 0; i < rozmiar; ++i) {
        if (produkty[i].cena * produkty[i].waga > srednia_cena) {
            fprintf(plik2, "%s %s %s %.2f %.2f\n", produkty[i].nazwa, produkty[i].kategoria, produkty[i].producent, produkty[i].cena, produkty[i].waga);
        }
    }
    fclose(plik2);

    printf("Produkty o cenie wyzszej niz srednia zostaly zapisane do pliku drugi_plik.txt: \n\n");

    char szukana[30];
    printf("Podaj producenta: ");
    scanf("%s", szukana);
    printf("\n");

    int indeks_prod = -1;
    float suma = 0;

    for (int i = 0; i < rozmiar; ++i) {
        if (strcmp(produkty[i].producent, szukana) == 0) {

            if (indeks_prod == -1 || produkty[i].waga > produkty[indeks_prod].waga) {
                indeks_prod = i;
            }

            suma += produkty[i].cena * produkty[i].waga;
        }
    }

    if (indeks_prod != -1) {
        printf("Najwiecej razy kupiony produkt od producenta | %s |:\n\n",szukana);
        printf("| %s |", produkty[indeks_prod].nazwa);
        printf("| %s |", produkty[indeks_prod].kategoria);
        printf(" | Cena: %.2f |", produkty[indeks_prod].cena);
        printf(" | Waga: %.2f |\n\n", produkty[indeks_prod].waga);
        printf("Laczna wartosc kupionych produktow: %.2f\n", suma);
    } else {
        printf("Brak produktow producenta| %s | \n", szukana);
    }

    return 0;
}