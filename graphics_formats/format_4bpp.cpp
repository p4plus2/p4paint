#include "format_4bpp.h"
#include <QDebug>

tile_data format_4bpp::get_tile(int offset)
{
	qDebug() << buffer->size();
	QImage image(8, 8, QImage::Format_Indexed8);
	image.setColorTable({0xFFFFFFFF, 0xFFFF0000, 0xFF00FF00, 0xFF0000FF,
	                     0xFFCCCCCC, 0xFFCC0000, 0xFF00CC00, 0xFF0000CC, 
	                     0xFF888888, 0xFF880000, 0xFF008800, 0xFF000088, 
	                     0xFF444444, 0xFF440000, 0xFF004400, 0xFF000044});
	for(int row = 0; row < 8; row++){
		unsigned char byte1 = buffer->at(row * 0x2 + offset);
		unsigned char byte2 = buffer->at(row * 0x2 + offset + 0x01);
		unsigned char byte3 = buffer->at(row * 0x2 + offset + 0x10);
		unsigned char byte4 = buffer->at(row * 0x2 + offset + 0x11);
		for(int bit = 7; bit >= 0; bit--){
			unsigned int pixel = (((byte1 & (1 << bit)) >> bit) << 3) |
					     (((byte2 & (1 << bit)) >> bit) << 2) |
					     (((byte3 & (1 << bit)) >> bit) << 1) |
					      ((byte4 & (1 << bit)) >> bit);
			image.setPixel(7-bit, row, pixel);
		}
	}
	return {0, image};
}

int format_4bpp::max_tiles()
{
	return buffer->size() / 0x20;
}

QVector<tile_data>format_4bpp::get_tiles(int offset, int count)
{
	QVector<tile_data> tiles;
	
	for(int i = 0; i < count; i++){
		tiles.append(get_tile(offset));
		offset += 0x20;
	}
	
	return tiles;
}

int format_4bpp::get_color_depth()
{
	return 16;
}
