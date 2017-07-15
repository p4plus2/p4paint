#ifndef FORMAT_LINEAR_H
#define FORMAT_LINEAR_H

#include "abstract_format.h"

class format_linear : public abstract_format
{
	public:
		using abstract_format::abstract_format;
		virtual int default_x_tiles();
		virtual int default_y_tiles();
		virtual int max_tiles();
		virtual tile_data get_tile(int offset);
		virtual QVector<tile_data>get_tiles(int offset, int count);
		virtual int get_color_depth();
		
		const int tile_size = 0x40;
};


struct format_linear_factory : public format_factory
{
	using format_factory::format_factory;
	virtual abstract_format *get_format(const QByteArray *b) { return new format_linear(b); }
};

static const char *format_name = "Mode 7 SNES";
static format_linear_factory factory(format_name);
#endif // FORMAT_LINEAR_H
