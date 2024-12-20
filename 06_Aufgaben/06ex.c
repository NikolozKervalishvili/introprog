/*
Willkommen zum sechsten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um enums und structs.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 06ex_test.c -o 06ex_test.o -lm && ./06ex_test.o
*/

#include "06_canvas.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

/*
In diesem Aufgabenblatt erweitern wir unsere Canvas API um Farben.
Menschen nehmen Farben als Mischung von drei "Basisfarben" wahr: rot, grün, und blau.
Jedes Pixel eines Bildschirms gibt rotes, grünes, und blaues Licht ab, je nach Intensität dieser
drei Farbkanäle sehen wir unterschiedliche Farben.

Unsere Canvas hat nun neue Funktionen `canvas_set_r`, `canvas_set_g`, and `canvas_set_b`, welche die einzelnen Kanäle
`red`, `green` und `blue` setzen. Das Canvas header-file dokumentiert die neuen Funktionen ausführlicher.
*/

/*
Aufgabe 1a:
Farben verhalten sich auf einem Bildschirm anders als zum Beispiel Wasserfarben auf Papier.

Färben Sie die gegebene Canvas so, dass die Rotkomponente jedes Pixels gleichmäßig von ganz links (also bei `x == 0` -> 0.0)
nach ganz rechts (bei `x == maximum` -> 1.0) zunimmt, und die Grünkomponente jedes Pixels gleichmäßig von
ganz unten (also bei `y == 0` -> 0.0) nach ganz oben (bei `y == maximum` -> 1.0) zunimmt.
Die Blaukomponente soll überall unverändert bleiben (und ist nicht in allen Testfällen die selbe).

Tipp: der Rotanteil für ein Pixel an der X-Koordinate berechnet sich beispielsweise als `x / (Canvasbreite - 1)`.
Aber Vorsicht: bei Division auf `int`s wird immer zur Null abgerundet, während hier z.B. in der Mitte 0.5 rauskommen soll.
(Einen Wert durch den Maximalwert zu teilen um eine Zahl zwischen 0 und 1 zu erhalten, wird als
"normalisieren" bezeichnet. Normalisieren kommt häufig vor, auch auf diesem Blatt. Wie wäre es also mit einer
Hilfsfunktion `float normalize(int value, int max)` ? :-) )
*/
Canvas swatch_red_green(Canvas c) {
	for (int y=0; y<canvas_height(c); y++) {
		for (int x=0; x<canvas_width(c); x++) {
			c = canvas_set_r(c, x, y, (float) x/ (float) (canvas_width(c)-1));
			c = canvas_set_g(c, x, y, (float) y/ (float) (canvas_height(c)-1));
		}
	}
    return c;
}

/*
Dieses enum repräsentiert die drei Farbkanäle.
*/
typedef enum ColorChannel_ {
    Red,
    Green,
    Blue
} ColorChannel;

/*
Aufgabe 1b:
Das obrige Enum können wir nun nutzen um eine Funktion zu schreiben, welche unterschiedliche Farbkanäle setzen kann.
Schreiben Sie die Funktion so, dass der jeweils richtige `channel` des Pixels mit der Koordinate `(x,y)` den Wert `v`
erhält.
*/

void set_color(Canvas c, int x, int y, ColorChannel channel, float v) {
	if (channel == Red) c = canvas_set_r(c, x, y, v);
	if (channel == Green) c = canvas_set_g(c, x, y, v);
	if (channel == Blue) c = canvas_set_b(c, x, y, v);
}
	

Canvas canvas_set_channel(Canvas c, int x, int y, ColorChannel channel, float v) {
	//for (int i = 0; i<canvas_height(c); i++) for (int j=0; j<canvas_width(c); j++)
	//if (i == y && i == x)
	//switch (channel) {
		//case Red: c = canvas_set_r(c, x, y, v);
		//case Green: c = canvas_set_g(c, x, y, v);
		//case Blue: c = canvas_set_b(c, x, y, v);
	//}
	set_color(c, x, y, channel, v);
    return c;
}

/*
Aufgabe 1c:
Die folgende Funktion soll eine Canvas nach den selben Richtlinien wie in Aufgabe 1a einfärben, anstelle von Rot für
die X-Achse und Grün für die Y-Achse allerdings die Farben aus den Parametern nutzen.
Schreiben Sie die Funktion so, dass `channel_x` den Farbkanal für die X-Achse festlegt und `channel_y` den Farbkanal für
die Y-Achse.
Alle nicht in den Parametern angegeben Farbkanäle sollen unverändert bleiben.
*/
Canvas swatch_rgb(Canvas c, ColorChannel channel_x, ColorChannel channel_y) {
	for (int y=0; y<canvas_height(c); y++) {
		for (int x=0; x<canvas_width(c); x++) {
			set_color(c, x, y, channel_x, (float)x / (float) (canvas_width(c)-1));
			set_color(c, x, y, channel_y, (float)y / (float) (canvas_height(c)-1));
		}
	}
    return c;
}

/*
Häufig wollen wir nicht über einzelne Farbkanäle nachdenken, sondern über Farben als solche.
Darum definieren wir einen neuen Typ für Farben. Eine Farbe wird eindeutig durch die Intensität ihrer drei Farbkanäle
beschrieben, also fassen wir drei Intensitätswerte in einem struct zusammen:
*/
typedef struct RGBByTheWayThisCanBeNamedArbitrarilygSinceWeAreUsingTheTypedefAnyways {
    float r;
    float g;
    float b;
} RGB;

/*
Aufgabe 2a:
Geben Sie den Wert zurück, der die Farbe Flieder (rot 0.86, grün 0.82, blau 1.0) repräsentiert.

Hinweis: Häufig werden RGB-Farben alternativ mit Ganzzahlen zwischen 0 und 255 angegeben, statt mit Kommazahlen zwischen 0.0 und 1.0.
Flieder wäre dann z.B. (rot 219, grün 209, blau 255).
*/
RGB lilac() {
    RGB color;
    color.r = 0.86;
    color.g = 0.82;
    color.b = 1.0;
    return color;
}

/*
Aufgabe 2b:
Nutzen wir nun unser neues struct auf der Canvas. Die folgende Funktion soll mit einem Funktionsaufruf alle
Kanäle gleichzeitig ansteuern!
Setzen Sie die Farbe des Pixels mit Koordinate `(x, y)` auf die von `color` repräsentierte Farbe.
*/
Canvas canvas_set_rgb_struct(Canvas c, int x, int y, RGB color) {
	c = canvas_set_r(c, x, y, color.r);
	c = canvas_set_g(c, x, y, color.g);
	c = canvas_set_b(c, x, y, color.b);
    return c;
}

/*
Aufgabe 2c:
Konvertieren Sie die gegebene Farbe in den Grauton der gleichen Helligkeit.
Die Helligkeit vom Grauton berechnet sich, indem man den Rotwert mit 0.2989, den Grünwert mit 0.587,
und den Blauwert mit 0.1140 multipliziert, und die Resultate addiert.
Der Grauton mit dieser Helligkeit setzt alle drei Farbkanäle auf diesen Wert.
*/
RGB rgb_to_gray(RGB color) {
	float grey = color.r * 0.2989 + color.g * 0.587 + color.b * 0.1140;
	color.r = grey;
	color.g = grey;
	color.b = grey;
    return color;
}

/*
Aufgabe 2d:
Konvertieren Sie mithilfe der `rgb_to_gray` Funktion das gegebene Bild in ein Graustufenbild.
Die aktuelle Farbe eines Pixels kann mit den `canvas_get_r`, `canvas_get_g` und `canvas_get_b` Funktionen ausgelesen
werden (siehe Headerfile für die Dokumentation).

Tipp: Genau so wie wir die drei Funktionen zum Färben zusammengefasst haben ließen sich auch die gerade genannten drei
Funktionen in einer Hilfsfunktion zusammenfassen welche die Farbe an der gegebenen Koordinate als ein
Wert vom Typ `RGB` zurück gibt.
*/
Canvas canvas_to_gray(Canvas c) {
	for (int y=0; y<canvas_height(c); y++) {
		for (int x=0; x<canvas_width(c); x++) {
			RGB rgb = {
				.r = canvas_get_r(c, x, y),
				.g = canvas_get_g(c, x, y),
				.b = canvas_get_b(c, x, y),
			};
			rgb = rgb_to_gray(rgb);
			c = canvas_set_r(c, x, y, rgb.r);
			c = canvas_set_g(c, x, y, rgb.g);
			c = canvas_set_b(c, x, y, rgb.b);
		}
	}
    return c;
}
