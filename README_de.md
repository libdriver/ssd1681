[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1681

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1681/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

SSD1681 ist ein Aktivmatrix-EPD-Anzeigetreiber mit Controller für Rot/Schwarz/Weiß-EPD-Anzeigen. Er besteht aus 200 Source-Ausgängen, 200 Gate-Ausgängen, 1 VCOM und 1 VBD (für den Rand), der Anzeigen mit einer Auflösung von bis zu 200 x 200 Zoll unterstützen kann Beim SSD1681 werden Daten und Befehle von der MCU über eine per Hardware wählbare serielle Peripherieschnittstelle gesendet. Es verfügt über einen eingebetteten Booster, Regler und Oszillator, der für EPD-Anzeigeanwendungen geeignet ist.

LibDriver SSD1681 ist der voll funktionsfähige Treiber von SSD1681, der von LibDriver gestartet wurde. Er bietet die Funktionen zum Zeichnen von Einzelpunkten, Füllen von Blöcken, Bildanzeige usw. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver SSD1681-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver SSD1681 SPI.

/test enthält den Testcode des LibDriver SSD1681-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver SSD1681-Beispielcode.

/doc enthält das LibDriver SSD1681-Offlinedokument.

/Datenblatt enthält SSD1681-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

Das Bildextraktionsformat ist wie folgt und jedes Pixel wird in einem Byte gespeichert.

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
</div>

```c
#include "driver_ssd1681_basic.h"

uint8_t data;
char str[] = "test";
uint8_t g_image[40000];

/* basic init */
if (ssd1681_basic_init() != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

/* clear the red color */
if (ssd1681_basic_clear(SSD1681_COLOR_RED) != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

/* clear the black color */
if (ssd1681_basic_clear(SSD1681_COLOR_BLACK) != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

...
    
/* basic string */
if (ssd1681_basic_string(SSD1681_COLOR_RED, 0, 0, str, (uint16_t)strlen(str), 1, SSD1681_FONT_16) != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

...
    
/* basic point read */
if (ssd1681_basic_read_point(SSD1681_COLOR_RED, 16, 16, &data) != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

...
    
/* basic write point */
if (ssd1681_basic_write_point(SSD1681_COLOR_BLACK, 20, 20, 1) != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

...
    
/* basic write rect */
if (ssd1681_basic_rect(SSD1681_COLOR_BLACK, 0, 0, 32, 32), 1) != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

...
    
/* basic draw the picture */
if (ssd1681_basic_picture(SSD1681_COLOR_BLACK, 0, 0, 200, 200, g_image) != 0)
{
    (void)ssd1681_basic_deinit();
    
    return 1;
}

/* basic deinit */
if (ssd1681_basic_deinit() != 0)
{
    return 1;
}

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ssd1681/index.html](https://www.libdriver.com/docs/ssd1681/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.