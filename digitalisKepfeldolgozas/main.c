#include "peldaprogram/kepmanipulacio.c"

int main() {
    KepTipus kep = betoltes("kepek/balloons_noisy.pgm");
    nagyobbitas(&kep, 3);
    dilatacio(&kep, 3);
    erozio(&kep, 3);
    erozio(&kep, 3);
    dilatacio(&kep, 3);
    kimentes("eredmeny.pgm", kep);
    kepFelszabaditas(kep);
    return 0;
}
