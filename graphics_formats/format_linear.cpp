#include "format_linear.h"

#include <QDebug>

int format_linear::default_x_tiles()
{
	return 16;
}

int format_linear::default_y_tiles()
{
	return 16;
}

//use commented blocks to view tilemaps as pixels
tile_data format_linear::get_tile(int offset)
{
	QImage image(8, 8, QImage::Format_Indexed8);
	image.setColorCount(get_color_depth());
	for(int row = 0; row < 8; row++){
		for(int column = 0; column < 8; column++){
			//unsigned char pixel = get_byte(row * 0x80 + offset + column);
			unsigned char pixel = get_byte(row * 8 + offset + column);
			image.setPixel(column, row, pixel);
		}
	}
	return {0, 0, image};
}

int format_linear::max_tiles()
{
	return buffer->size() / tile_size;
}

QVector<tile_data>format_linear::get_tiles(int offset, int count)
{
	QVector<tile_data> tiles;

	for(int i = 0; i < count; i++){
		tiles.append(get_tile(offset));
		offset += tile_size;
		//offset += 0x08;
		//if(i && (i + 1) % 16 == 0){
		//	offset += 0x380;
		//}
	}
	
	return tiles;
}

int format_linear::get_color_depth()
{
	return 256;
}
