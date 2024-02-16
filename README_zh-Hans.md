[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver SSD1681

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ssd1681/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

SSD1681是一款有源矩阵EPD显示器驱动器，带有用于红色/黑色/白色EPD显示器的控制器。它由200个源输出、200个门输出、1个VCOM和1VBD（用于边界）组成，可支持分辨率高达200x200的显示器。在SSD1681中，数据和命令通过硬件可选串行外围接口从MCU发送。它具有嵌入式放大器、稳压器和振荡器，适用于EPD显示应用。

LibDriver SSD1681是LibDriver推出的SSD1681全功能驱动，该驱动提供绘制单点，填充块，图片显示等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver SSD1681的源文件。

/interface目录包含了LibDriver SSD1681与平台无关的SPI总线模板。

/test目录包含了LibDriver SSD1681驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver SSD1681编程范例。

/doc目录包含了LibDriver SSD1681离线文档。

/datasheet目录包含了SSD1681数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

图像提取格式如下，每个像素使用1个字节存储。

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

### 文档

在线文档: [https://www.libdriver.com/docs/ssd1681/index.html](https://www.libdriver.com/docs/ssd1681/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。