#include "peldaprogram/kepmanipulacio.c"

int main() {
    KepTipus kep = betoltes("kepek/lena.pgm");
    KepTipus kisebb = kicsinyites(kep, 4);
    kimentes("lena2.pgm", kisebb);
    kepFelszabaditas(kep);
    kepFelszabaditas(kisebb);
    return 0;
}
