[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1681

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1681/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SSD1681 は、赤/黒/白 EPD ディスプレイ用のコントローラーを備えたアクティブ マトリックス EPD ディスプレイ ドライバーです。200 のソース出力、200 のゲート出力、1 つの VCOM および 1 つの VBD (ボーダー用) で構成され、最大解像度 200x200 のディスプレイをサポートできます。 SSD1681 は、ハードウェアで選択可能なシリアル ペリフェラル インターフェイスを介して MCU からデータとコマンドが送信されます。EPD ディスプレイ アプリケーションに適したブースター、レギュレータ、オシレータが組み込まれています。

LibDriver SSD1681 は、LibDriver によって起動される SSD1681 のフル機能ドライバーです。単一点描画、塗りつぶしブロック、画像表示などの機能を提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver SSD1681のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver SSD1681用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver SSD1681ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver SSD1681プログラミング例が含まれています。

/ docディレクトリには、LibDriver SSD1681オフラインドキュメントが含まれています。

/ datasheetディレクトリには、SSD1681データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

画像抽出フォーマットは次のとおりで、すべてのピクセルが 1 バイトに格納されます。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ssd1681/index.html](https://www.libdriver.com/docs/ssd1681/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。