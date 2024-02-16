[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1681

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1681/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SSD1681是一款有源矩陣EPD顯示器驅動器，帶有用於紅色/黑色/白色EPD顯示器的控制器。 它由200個源輸出、200個門輸出、1個VCOM和1VBD（用於邊界）組成，可支持分辯率高達200x200的顯示器。 在SSD1681中，數據和命令通過硬體可選串列週邊介面從MCU發送。 它具有嵌入式放大器、穩壓器和振盪器，適用於EPD顯示應用。

LibDriver SSD1681是LibDriver推出的SSD1681全功能驅動，該驅動提供繪製單點，填充塊，圖片顯示等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver SSD1681的源文件。

/interface目錄包含了LibDriver SSD1681與平台無關的SPI總線模板。

/test目錄包含了LibDriver SSD1681驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver SSD1681編程範例。

/doc目錄包含了LibDriver SSD1681離線文檔。

/datasheet目錄包含了SSD1681數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的SPI總線模板，完成指定平台的SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

#### example basic

圖像提取格式如下，每個像素使用1個字節存儲。

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
</div>

```C
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

### 文檔

在線文檔: [https://www.libdriver.com/docs/ssd1681/index.html](https://www.libdriver.com/docs/ssd1681/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。