/********** 摘自文档 **********/
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define NK_INCLUDE_FIXED_TYPES			// 这个宏会引入 <stdint.h> 以帮助 nuklear 使用正确的数据类型
// nuklear 的设计目标是适配所有平台，以上几个宏是控制 nuklear 特性和行为的
// 不同平台基本数据类型大小不一样，指针长度不一样
// 有些平台(例如嵌入式)不提供 IO 功能，或者使用者希望 nuklear context 使用固定分配的内存等各种特殊需求
// 在 PC 平台上定义以上几个宏几乎是标准动作
#pragma warning(disable:4996)				// nuklear 需要使用新版本 VS 默认禁止的 vsprintf 等旧版 C 函数
#pragma execution_character_set("utf-8")	// VS 需要设定执行字符集为 utf8 格式，否则非英文字符会乱码
/********** 摘自文档 - End **********/


#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <Shlobj.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#define NK_EASYX_IMPLEMENTATION
#include "../nuklear.h"
#include "nuklear_easyx.h"

/* ===============================================================
 *
 *				打开相应的注释，可以运行不同的示例
 *
 * ===============================================================*/
 //#define INCLUDE_ALL 
//#define INCLUDE_STYLE 
//#define INCLUDE_CALCULATOR 
//#define INCLUDE_CANVAS 
#define INCLUDE_OVERVIEW
//#define INCLUDE_CONFIGURATOR 
//#define INCLUDE_NODE_EDITOR 

#ifdef INCLUDE_ALL
#define INCLUDE_STYLE
#define INCLUDE_CALCULATOR
#define INCLUDE_CANVAS
#define INCLUDE_OVERVIEW
#define INCLUDE_CONFIGURATOR
#define INCLUDE_NODE_EDITOR
#endif

#ifdef INCLUDE_STYLE
#include "../demo/common/style.c"
#endif
#ifdef INCLUDE_CALCULATOR
#include "../demo/common/calculator.c"
#endif
#ifdef INCLUDE_CANVAS
#include "../demo/common/canvas.c"
#endif
#ifdef INCLUDE_OVERVIEW
#include "../demo/common/overview.c"
#endif
#ifdef INCLUDE_CONFIGURATOR
#include "../demo/common/style_configurator.c"
#endif
#ifdef INCLUDE_NODE_EDITOR
#include "../demo/common/node_editor.c"
#endif

int main(void)
{
	EasyXFont* font;
	struct nk_context* ctx;

	HWND wnd;
	HDC dc;
	int running = 1;
	int needs_refresh = 1;

#ifdef INCLUDE_CONFIGURATOR
	static struct nk_color color_table[NK_COLOR_COUNT];
	memcpy(color_table, nk_default_color_style, sizeof(color_table));
#endif

	initgraph(900, 700);
	wnd = GetHWnd();
	dc = GetDC(wnd);
	HDC ddc = GetImageHDC();

	font = nk_easyxfont_create("Consolas", 16);
	ctx = nk_easyx_init(font, dc, WINDOW_WIDTH, WINDOW_HEIGHT);

	BeginBatchDraw();
	while (running)
	{
		Sleep(10);

		ExMessage msg;
		nk_input_begin(ctx);

		while (peekmessage(&msg)) {
			if (msg.message == WM_QUIT)
				running = 0;
			nk_easyx_handle_event(wnd, &msg);
			needs_refresh = 1;
		}
		nk_input_end(ctx);

		if (nk_begin(ctx, "Demo", nk_rect(50, 50, 200, 200),
			NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
			NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
		{
			enum { EASY, HARD };
			static int op = EASY;
			static int property = 20;

			nk_layout_row_static(ctx, 30, 80, 2);
			if (nk_button_label(ctx, "阿松大题")) {
				fprintf(stdout, "button pressed\n");
			}

			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
			if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

			nk_layout_row_dynamic(ctx, 22, 1);
			nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
		}
		nk_end(ctx);

		/* -------------- EXAMPLES 摘自文档 ---------------- */
#ifdef INCLUDE_CALCULATOR
		calculator(ctx);
#endif
#ifdef INCLUDE_CANVAS
		canvas(ctx);
#endif
#ifdef INCLUDE_OVERVIEW
		overview(ctx);
#endif
#ifdef INCLUDE_CONFIGURATOR
		style_configurator(ctx, color_table);
#endif
#ifdef INCLUDE_NODE_EDITOR
		node_editor(ctx);
#endif
		/* --------------- EXAMPLES END -------------------------- */

		nk_easyx_render(nk_rgb(30, 30, 30));
		FlushBatchDraw();
	}

	EndBatchDraw();

	nk_easyxfont_del(font);
	ReleaseDC(wnd, dc);
	closegraph();
	return 0;
}

