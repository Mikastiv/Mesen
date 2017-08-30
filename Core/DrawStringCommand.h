#pragma once
#include "stdafx.h"
#include "DrawCommand.h"

class DrawStringCommand : public DrawCommand
{
private:
	int _x, _y, _color, _backColor;
	string _text;

	//Taken from FCEUX's LUA code
	const int _tabSpace = 4;
	const uint8_t _font[792] = {
		6,  0,  0,  0,  0,  0,  0,  0,	// 0x20 - Spacebar
		3, 64, 64, 64, 64, 64,  0, 64,
		5, 80, 80, 80,  0,  0,  0,  0,
		6, 80, 80,248, 80,248, 80, 80,
		6, 32,120,160,112, 40,240, 32,
		6, 64,168, 80, 32, 80,168, 16,
		6, 96,144,160, 64,168,144,104,
		3, 64, 64,  0,  0,  0,  0,  0,
		4, 32, 64, 64, 64, 64, 64, 32,
		4, 64, 32, 32, 32, 32, 32, 64,
		6,  0, 80, 32,248, 32, 80,  0,
		6,  0, 32, 32,248, 32, 32,  0,
		3,  0,  0,  0,  0,  0, 64,128,
		5,  0,  0,  0,240,  0,  0,  0,
		3,  0,  0,  0,  0,  0,  0, 64,
		5, 16, 16, 32, 32, 32, 64, 64,
		6,112,136,136,136,136,136,112,	// 0x30 - 0
		6, 32, 96, 32, 32, 32, 32, 32,
		6,112,136,  8, 48, 64,128,248,
		6,112,136,  8, 48,  8,136,112,
		6, 16, 48, 80,144,248, 16, 16,
		6,248,128,128,240,  8,  8,240,
		6, 48, 64,128,240,136,136,112,
		6,248,  8, 16, 16, 32, 32, 32,
		6,112,136,136,112,136,136,112,
		6,112,136,136,120,  8, 16, 96,
		3,  0,  0, 64,  0,  0, 64,  0,
		3,  0,  0, 64,  0,  0, 64,128,
		4,  0, 32, 64,128, 64, 32,  0,
		5,  0,  0,240,  0,240,  0,  0,
		4,  0,128, 64, 32, 64,128,  0,
		6,112,136,  8, 16, 32,  0, 32,	// 0x3F - ?
		6,112,136,136,184,176,128,112,	// 0x40 - @
		6,112,136,136,248,136,136,136,	// 0x41 - A
		6,240,136,136,240,136,136,240,
		6,112,136,128,128,128,136,112,
		6,224,144,136,136,136,144,224,
		6,248,128,128,240,128,128,248,
		6,248,128,128,240,128,128,128,
		6,112,136,128,184,136,136,120,
		6,136,136,136,248,136,136,136,
		4,224, 64, 64, 64, 64, 64,224,
		6,  8,  8,  8,  8,  8,136,112,
		6,136,144,160,192,160,144,136,
		6,128,128,128,128,128,128,248,
		6,136,216,168,168,136,136,136,
		6,136,136,200,168,152,136,136,
		7, 48, 72,132,132,132, 72, 48,
		6,240,136,136,240,128,128,128,
		6,112,136,136,136,168,144,104,
		6,240,136,136,240,144,136,136,
		6,112,136,128,112,  8,136,112,
		6,248, 32, 32, 32, 32, 32, 32,
		6,136,136,136,136,136,136,112,
		6,136,136,136, 80, 80, 32, 32,
		6,136,136,136,136,168,168, 80,
		6,136,136, 80, 32, 80,136,136,
		6,136,136, 80, 32, 32, 32, 32,
		6,248,  8, 16, 32, 64,128,248,
		3,192,128,128,128,128,128,192,
		5, 64, 64, 32, 32, 32, 16, 16,
		3,192, 64, 64, 64, 64, 64,192,
		4, 64,160,  0,  0,  0,  0,  0,
		6,  0,  0,  0,  0,  0,  0,248,
		3,128, 64,  0,  0,  0,  0,  0,
		5,  0,  0, 96, 16,112,144,112,	// 0x61 - a
		5,128,128,224,144,144,144,224,
		5,  0,  0,112,128,128,128,112,
		5, 16, 16,112,144,144,144,112,
		5,  0,  0, 96,144,240,128,112,
		5, 48, 64,224, 64, 64, 64, 64,
		5,  0,112,144,144,112, 16,224,
		5,128,128,224,144,144,144,144,
		2,128,  0,128,128,128,128,128,
		4, 32,  0, 32, 32, 32, 32,192,
		5,128,128,144,160,192,160,144,
		2,128,128,128,128,128,128,128,
		6,  0,  0,208,168,168,168,168,
		5,  0,  0,224,144,144,144,144,
		5,  0,  0, 96,144,144,144, 96,
		5,  0,224,144,144,224,128,128,
		5,  0,112,144,144,112, 16, 16,
		5,  0,  0,176,192,128,128,128,
		5,  0,  0,112,128, 96, 16,224,
		4, 64, 64,224, 64, 64, 64, 32,
		5,  0,  0,144,144,144,144,112,
		5,  0,  0,144,144,144,160,192,
		6,  0,  0,136,136,168,168, 80,
		5,  0,  0,144,144, 96,144,144,
		5,  0,144,144,144,112, 16, 96,
		5,  0,  0,240, 32, 64,128,240,
		4, 32, 64, 64,128, 64, 64, 32,
		3, 64, 64, 64, 64, 64, 64, 64,
		4,128, 64, 64, 32, 64, 64,128,
		6,  0,104,176,  0,  0,  0,  0
	};

	int GetCharNumber(char ch)
	{
		ch -= 32;
		return (ch < 0 || ch > 98) ? 0 : ch;
	}

	int GetCharWidth(char ch)
	{
		return _font[GetCharNumber(ch) * 8];
	}

protected:
	void InternalDraw()
	{
		int x = _x;
		int y = _y;
		for(char c : _text) {
			if(c == '\n') {
				x = _x;
				y += 9;
			} else if(c == '\t') {
				x += (_tabSpace - (((x - _x) / 8) % _tabSpace)) * 8;
			} else {
				int ch = GetCharNumber(c);
				int width = GetCharWidth(c);
				int rowOffset = (c == 'y' || c == 'g' || c == 'p' || c == 'q') ? 1 : 0;
				for(int j = 0; j < 8; j++) {
					uint8_t rowData = (j == 7 && rowOffset == 0 || j == 0 && rowOffset == 1) ? 0 : _font[ch * 8 + 1 + j - rowOffset];
					for(int i = 0; i < width; i++) {
						int drawFg = (rowData >> (7 - i)) & 0x01;
						DrawPixel(x + i, y + j, drawFg ? _color : _backColor);
					}
				}
				for(int i = 0; i < width; i++) {
					DrawPixel(x + i, y - 1, _backColor);
				}
				x += width;
			}
		}
	}

public:
	DrawStringCommand(int x, int y, string text, int color, int backColor, int frameCount) :
		_x(x), _y(y), _text(text), _color(color), _backColor(backColor), DrawCommand(frameCount)
	{
		if(!(_color & 0xFF000000)) {
			_color |= 0xFF000000;
		}
		if(!(_backColor & 0xFF000000)) {
			_backColor |= 0xFF000000;
		}
	}
};
