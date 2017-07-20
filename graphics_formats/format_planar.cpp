#include "format_planar.h"
#include <QDebug>

template <int BIT_DEPTH>
int format_planar<BIT_DEPTH>::default_x_tiles()
{
	return 16;
}

template <int BIT_DEPTH>
int format_planar<BIT_DEPTH>::default_y_tiles()
{
	return 16;
}

template <int BIT_DEPTH>
tile_data format_planar<BIT_DEPTH>::get_tile(int offset)
{
	QImage image(8, 8, QImage::Format_Indexed8);
	image.setColorCount(get_color_depth());
	for(int row = 0; row < 8; row++){
		unsigned char bytes[BIT_DEPTH];
		for(int i = 0; i < BIT_DEPTH; i++){
			bool odd_plane = (BIT_DEPTH & 1 && i == BIT_DEPTH - 1);
			bytes[i] = get_byte(row * (0x2 - odd_plane) + offset + (i & 1) + ((i & 0xFE) << 3));
		}
		
		for(int bit = 7; bit >= 0; bit--){
			unsigned int pixel = 0;
			for(int i = 0; i < BIT_DEPTH; i++){
				pixel |= ((bytes[i] & (1 << bit)) >> bit) << (BIT_DEPTH - 1 - i);
			}

			image.setPixel(7-bit, row, pixel);
		}
	}
	return {0, 0, image};
}

template <int BIT_DEPTH>
int format_planar<BIT_DEPTH>::max_tiles()
{
	return buffer->size() / tile_size;
}

template <int BIT_DEPTH>
QVector<tile_data>format_planar<BIT_DEPTH>::get_tiles(int offset, int count)
{
	QVector<tile_data> tiles;
	
	for(int i = 0; i < count; i++){
		tiles.append(get_tile(offset));
		offset += tile_size;
	}
	
	return tiles;
}

template <int BIT_DEPTH>
int format_planar<BIT_DEPTH>::get_color_depth()
{
	return 1 << BIT_DEPTH;
}
