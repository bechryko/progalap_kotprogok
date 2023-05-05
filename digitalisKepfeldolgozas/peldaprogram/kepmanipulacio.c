#include <stdio.h>
#include <stdlib.h>

typedef struct KepTipus{
    int magassag, szelesseg, szinek, foglaltMagassag, foglaltSzelesseg;
    int **pontok;
} KepTipus;

KepTipus masolas(KepTipus eredeti) {
    KepTipus kep;
    kep.szelesseg = eredeti.szelesseg;
    kep.magassag = eredeti.magassag;
    kep.szinek = eredeti.szinek;
    kep.pontok = malloc(sizeof (int *) * (kep.foglaltMagassag = kep.magassag));
    for (int i = 0; i < kep.magassag; ++i) {
        kep.pontok[i] = malloc(sizeof (int) * (kep.foglaltSzelesseg = kep.szelesseg));
        for (int j = 0; j < kep.szelesseg; ++j) {
            kep.pontok[i][j] = eredeti.pontok[i][j];
        }
    }
    return kep;
}

KepTipus betoltes(char fajlnev[]){
    KepTipus kep;
    FILE *f = fopen(fajlnev, "r");
    fscanf(f, "%*s");
    fscanf(f, "%d %d %d", &kep.szelesseg, &kep.magassag, &kep.szinek);
    kep.pontok = malloc(sizeof (int *) * (kep.foglaltMagassag = kep.magassag));
    for (int i = 0; i < kep.magassag; ++i) {
        kep.pontok[i] = malloc(sizeof (int) * (kep.foglaltSzelesseg = kep.szelesseg));
    }
    for (int i = 0; i < kep.magassag; ++i) {
        for (int j = 0; j < kep.szelesseg; ++j) {
            fscanf(f, "%d", &kep.pontok[i][j]);
        }
    }
    fclose(f);
    return kep;
}

void kimentes(char fajlnev[], KepTipus kep){
    FILE *f = fopen(fajlnev, "w");
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n%d\n", kep.szelesseg, kep.magassag, kep.szinek);
    for (int i = 0; i < kep.magassag; ++i) {
        for (int j = 0; j < kep.szelesseg; ++j) {
            fprintf(f, "%d\n", kep.pontok[i][j]);
        }
    }
    fclose(f);
}

void kepFelszabaditas(KepTipus kep) {
    for (int i = 0; i < kep.foglaltMagassag; ++i) {
        free(kep.pontok[i]);
    }
    free(kep.pontok);
}

void nagyobbitas(KepTipus *eredeti, int novelesSzorzoja) {
    KepTipus kep;
    kep.szelesseg = eredeti->szelesseg * novelesSzorzoja;
    kep.magassag = eredeti->magassag * novelesSzorzoja;
    kep.szinek = eredeti->szinek;
    kep.pontok = malloc(sizeof (int *) * (kep.foglaltMagassag = kep.magassag));
    for (int i = 0; i < kep.magassag; ++i) {
        kep.pontok[i] = malloc(sizeof (int) * (kep.foglaltSzelesseg = kep.szelesseg));
        for (int j = 0; j < kep.szelesseg; ++j) {
            if(i % novelesSzorzoja == 0 && j % novelesSzorzoja == 0) {
                kep.pontok[i][j] = eredeti->pontok[i / novelesSzorzoja][j / novelesSzorzoja];
            } else {
                kep.pontok[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < (kep.magassag / novelesSzorzoja) - 1; ++i) {
        for (int j = 0; j < (kep.szelesseg / novelesSzorzoja); ++j) {
            int felsoPont = kep.pontok[i * novelesSzorzoja][j * novelesSzorzoja];
            int alsoPont = kep.pontok[(i + 1) * novelesSzorzoja][j * novelesSzorzoja];
            int lepesPontonkent = (alsoPont - felsoPont) / (novelesSzorzoja + 1);
            for (int k = 0; k < novelesSzorzoja; ++k) {
                if(k != 0) {
                    kep.pontok[i * novelesSzorzoja + k][j * novelesSzorzoja] = felsoPont + lepesPontonkent * k;
                }
                if(j == 0) {
                    continue;
                }
                int jobbPont = kep.pontok[i * novelesSzorzoja + k][j * novelesSzorzoja];
                int balPont = kep.pontok[i * novelesSzorzoja + k][(j - 1) * novelesSzorzoja];
                lepesPontonkent = (balPont - jobbPont) / (novelesSzorzoja + 1);
                for (int l = 1; l < novelesSzorzoja; ++l) {
                    kep.pontok[i * novelesSzorzoja + k][j * novelesSzorzoja - l] = jobbPont + lepesPontonkent * l;
                }
            }
        }
    }
    kep.magassag -= novelesSzorzoja - 1;
    kep.szelesseg -= novelesSzorzoja - 1;
    kepFelszabaditas(*eredeti);
    *eredeti = kep;
}

void kicsinyites(KepTipus *eredeti, int csokkentesSzorzoja) {
    KepTipus kep;
    kep.szelesseg = eredeti->szelesseg / csokkentesSzorzoja;
    kep.magassag = eredeti->magassag / csokkentesSzorzoja;
    kep.szinek = eredeti->szinek;
    kep.pontok = malloc(sizeof(int*) * (kep.foglaltMagassag = kep.magassag));
    for(int i = 0; i < kep.magassag; ++i) {
        kep.pontok[i] = malloc(sizeof(int) * (kep.foglaltSzelesseg = kep.szelesseg));
        for(int j = 0; j < kep.szelesseg; ++j) {
            kep.pontok[i][j] = eredeti->pontok[i * csokkentesSzorzoja][j * csokkentesSzorzoja];
        }
    }
    kepFelszabaditas(*eredeti);
    *eredeti = kep;
}

void erozio(KepTipus *eredeti, int maszkMeret) {
    if(maszkMeret % 2 == 0) {
        fprintf(stderr, "A maszk merete csak paratlan lehet!\n");
        return;
    } else if(maszkMeret < 3) {
        fprintf(stderr, "A maszk merete legalabb 3 kell legyen!\n");
        return;
    }
    KepTipus kep = masolas(*eredeti);
    for(int i = 0; i < kep.magassag; ++i) {
        for(int j = 0; j < kep.szelesseg; ++j) {
            int min = 255;
            for(int k = 0; k < maszkMeret; ++k) {
                for(int l = 0; l < maszkMeret; ++l) {
                    int x = i - (maszkMeret / 2) + k;
                    int y = j - (maszkMeret / 2) + l;
                    if(x < 0 || x >= kep.magassag || y < 0 || y >= kep.szelesseg) {
                        continue;
                    }
                    if(kep.pontok[x][y] < min) {
                        min = kep.pontok[x][y];
                    }
                }
            }
            eredeti->pontok[i][j] = min;
        }
    }
    kepFelszabaditas(kep);
}

void dilatacio(KepTipus *eredeti, int maszkMeret) {
    if(maszkMeret % 2 == 0) {
        fprintf(stderr, "A maszk merete csak paratlan lehet!\n");
        return;
    } else if(maszkMeret < 3) {
        fprintf(stderr, "A maszk merete legalabb 3 kell legyen!\n");
        return;
    }
    KepTipus kep = masolas(*eredeti);
    for(int i = 0; i < kep.magassag; ++i) {
        for(int j = 0; j < kep.szelesseg; ++j) {
            int max = 0;
            for(int k = 0; k < maszkMeret; ++k) {
                for(int l = 0; l < maszkMeret; ++l) {
                    int x = i - (maszkMeret / 2) + k;
                    int y = j - (maszkMeret / 2) + l;
                    if(x < 0 || x >= kep.magassag || y < 0 || y >= kep.szelesseg) {
                        continue;
                    }
                    if(kep.pontok[x][y] > max) {
                        max = kep.pontok[x][y];
                    }
                }
            }
            eredeti->pontok[i][j] = max;
        }
    }
    kepFelszabaditas(kep);
}
