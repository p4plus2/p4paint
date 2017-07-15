#include "format_gsu.h"

#include <QDebug>

int format_gsu::default_x_tiles()
{
	return 32;
}

int format_gsu::default_y_tiles()
{
	return 16;
}

tile_data format_gsu::get_tile(int offset)
{
	QImage image(8, 8, QImage::Format_Indexed8);
	image.setColorCount(get_color_depth());
	for(int row = 0; row < 8; row++){
		for(int column = 0; column < 8; column++){
			unsigned int real_offset = offset >= buffer->size() ? offset - buffer->size() : offset;
			unsigned char pixel = get_byte(row * 0x100 + real_offset + column);
			if(offset > buffer->size()){
				pixel >>= 4;
			}
			image.setPixel(column, row, pixel & 0x0F);
		}
	}
	return {0, image};
}

int format_gsu::max_tiles()
{
	return buffer->size() / tile_size;
}

QVector<tile_data>format_gsu::get_tiles(int offset, int count)
{
	QVector<tile_data> tiles;
	
	for(int i = 0; i < count; i++){
		tiles.append(get_tile(offset));
		offset += 0x08;
		if(i && (i + 1) % 32 == 0){
			offset += 0x700;
		}
	}
	
	return tiles;
}

int format_gsu::get_color_depth()
{
	return 16;
}
