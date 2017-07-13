#ifndef ABSTRACT_FORMAT_H
#define ABSTRACT_FORMAT_H

#include <QByteArray>
#include "tile_data.h"

class abstract_format
{
	public:
		abstract_format(const QByteArray *b);
		virtual tile_data get_tile(int offset) = 0;
		virtual QVector<tile_data>get_tiles(int offset, int count) = 0;
		virtual int get_color_depth() = 0;
		
	protected:
		const QByteArray *buffer;
};

#endif // ABSTRACT_FORMAT_H
