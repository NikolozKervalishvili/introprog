/*
Willkommen zum zweiten Aufgabenblatt vom Programmierkurs. Auf diesem Aufgabenblatt geht es um folgende neue Konzepte:

- Blöcke und Scope
- else und else-if
- && und ||
- verschachtelte Schleifen

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 02ex_test.c -o 02ex_test.o -lm && ./02ex_test.o
*/

/*
Wie auch auf dem ersten Aufgabenblatt können Sie alles außer den Kommentaren ignorieren,
und Ihre Lösungen zwischen den "BEGIN CHANGES" und "END CHANGES" eintragen.
*/

#include <stdio.h> 

int sum_divisible_both(int n) {
    int result = 0;
    /*
    Aufgabe 1a:
    Weisen Sie der Variable `result` die Summe aller Ganzzahlen zwischen `0` und `n` (inklusive) zu, welche sowohl
    durch `7` *als auch* durch `13` teilbar sind.
    */
    /* BEGIN CHANGES */
    for (int i=0; i<=n; i++) if (i % 7 == 0 && i % 13 == 0) result += i;
    /* END CHANGES */
    return result;
}

int sum_divisible_or(int n) {
    int result = 0;
    /*
    Aufgabe 1b:
    Weisen Sie der Variable `result` die Summe aller Ganzzahlen zwischen `0` und `n` (inklusive) zu, welche
    durch `7` *oder* durch `13` teilbar sind (das beinhaltet auch die Zahlen, die durch beides teilbar sind).
    */
    /* BEGIN CHANGES */
    for (int i=0; i<=n; i++) if (i % 7 == 0 || i % 13 == 0) result += i;
    /* END CHANGES */
    return result;
}

int sum_divisible_either(int n) {
   int result = 0;
    /*
    Aufgabe 1c:
    Weisen Sie der Variable `result` die Summe aller Ganzzahlen zwischen `0` und `n` (inklusive) zu, welche *entweder*
    durch `7` *oder* durch `13` teilbar sind (aber nicht durch beides).
    */
    /* BEGIN CHANGES */
    for (int i=0; i<=n; i++) if ((i % 7 == 0 || i % 13 == 0) && !(i % 7 == 0 && i % 13 == 0)) result += i;
    /* END CHANGES */
    return result;
}

int signum(int x) {
   int result = 0;
    /*
    Aufgabe 2a:
    Weisen Sie der Variable `result` den Wert `-1` zu, falls `x` strikt negativ ist, `0` falls `x` gleich `0` ist, und
    `1` falls `x` strikt positiv ist.
    */
    /* BEGIN CHANGES */
    if (x>0) result = 1;
    if (x<0) result = -1;
    if (x==0) result = 0;
    /* END CHANGES */
    return result;
}

int is_leapyear(int year) {
    int result = 0;
    /*
    Aufgabe 2b:
    Im gregorianischen Kalender ist ein Jahr ein Schaltjahr, genau dann wenn die Jahreszahl durch 400 teilbar ist, oder
    wenn sie durch vier teilbar ist aber nicht durch 100.

    Weisen Sie der Variable `result` den Wert `1` zu, falls `year` ein Schaltjahr ist, und ansonsten `0`.
    */
    /* BEGIN CHANGES */
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) result = 1; 
    /* END CHANGES */
    return result;
}

int greatest_of_three(int a, int b, int c) {
    int result = 0;
    /*
    Aufgabe 2c:
    Weisen Sie der Variable `result` den größten Wert zu, den eine der drei Variablen `a`, `b`, `c` hat.
    */
    /* BEGIN CHANGES */
    if (a>b && a>c) result = a;
    if (b>a && b>c) result = b;
    if (c>a && c>b) result = c;
    /* END CHANGES */
    return result;
}

int least_common_multiple_with_8(int n) {
    int result = 0;
    /*
    Aufgabe 3a:
    Das kleinste gemeinsame Vielfache zweier Zahlen ist die kleinste Zahl, welche ein ganzzahliges Vielfaches von sowohl
    der einen als auch der anderen ist.
    Beispielsweise ist das kleinste gemeinsame Vielfache von 8 und 10 die 40, da '40 = 8 * 5', '40 = 10 * 4', und es
    kein kleineres gemeinsames Vielfaches gibt.

    Weisen Sie der Variable 'result' das kleinste gemeinsame Vielfache von 'n' und '8' zu.
    */
    /* BEGIN CHANGES */
    int i;
    for (i=1; (n*i) % 8 != 0; i++);
    result = n*i; 
    /* END CHANGES */
    return result;
}

int sum_least_common_multiples_with_8(int n) {
    int result = 0;
    /*
    Aufgabe 3b:
    Weisen Sie der Variable 'result' die Summe der kleinsten gemeinsamen Vielfachen mit 8 der Zahlen von 1 bis 'n' zu.

    Beispeiel: Das KGV von 1 und 8 ist 8, das KGV von 2 und 8 ist 8, das KGV von 3 und 8 ist 24, also ist result für
    'n := 3' der Wert '8 + 8 + 24 = 40'
    */
    /* BEGIN CHANGES */
    for (int j=0; j<=n; j++) {
      int i;
      for(i=1; (j*i) % 8 != 0; i++);
      result += j*i;
    }
    /* END CHANGES */
    return result;
}
