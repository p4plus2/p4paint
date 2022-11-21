#include <QDebug>

#include "palette_container.h"

palette_container::palette_container()
{
	colors.reserve(256);
	colors.fill(0xFF000000, 256);
}

void palette_container::set_color_pc(int color_depth, int subpalette, int index, QRgb color)
{
	colors[color_depth * subpalette + index] = color;
}

void palette_container::set_color_snes(int color_depth, int subpalette, int index, quint16 color)
{
	colors[color_depth * subpalette + index] = to_pc(color);
}

QRgb palette_container::get_color_pc(int color_depth, int subpalette, int index)
{
	return colors[color_depth * subpalette + index];
}

QRgb palette_container::get_color_snes(int color_depth, int subpalette, int index)
{
	return to_snes(colors[color_depth * subpalette + index]);
}

QVector<QRgb> palette_container::get_subpalette(int color_depth, int subpalette)
{
	return colors.mid(color_depth * subpalette, color_depth);
}

void palette_container::set_subpalette(int color_depth, int subpalette, QVector<QRgb> subcolors)
{
	for(int i = 0; i < color_depth; i++){
		colors[subpalette * color_depth + i] = subcolors[i];
	}
	
}

quint16 palette_container::to_snes(QRgb color)
{
	int red = (color & 0xFF0000) >> 16;
	int green = (color & 0xFF00) >> 8;
	int blue = (color & 0xFF);
	
	return  (((red   + (red   <= 248 ? 4 : 0)) >> 3)|
		(((green + (green <= 248 ? 4 : 0)) >> 3) << 5)|
		(((blue  + (blue  <= 248 ? 4 : 0)) >> 3) << 10)) & 0x7FFF;
}

QRgb palette_container::to_pc(quint16 color)
{
	int red = (color & 0x1F) << 3;
	red |= red >> 5;
	
	int green = ((color >> 5) & 0x1F) << 3;
	green |= green >> 5;
	
	int blue = ((color >> 10) & 0x1F) << 3;
	blue |= blue >> 5;
	
	return QColor::fromRgb(red, green, blue).rgba();
}
