#ifndef TILE_H
#define TILE_H

#include <QImage>

struct tile_data{
	int palette;
	int subpalette;
	QImage image;
};

#endif // TILE_H
