#ifndef TILE_H
#define TILE_H

#include <QImage>

struct tile_data{
	short palette;
	short subpalette;
	QImage image;
};

#endif // TILE_H
