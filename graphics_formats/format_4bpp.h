#ifndef FORMAT_4BPP_H
#define FORMAT_4BPP_H

#include "abstract_format.h"

class format_4bpp : public abstract_format
{
	public:
		using abstract_format::abstract_format;
		virtual int max_tiles();
		virtual tile_data get_tile(int offset);
		virtual QVector<tile_data>get_tiles(int offset, int count);
		virtual int get_color_depth();
		
		const int tile_size = 0x20;
};


struct format_4bpp_factory : public format_factory
{
	using format_factory::format_factory;
	virtual abstract_format *get_format(const QByteArray *b) { return new format_4bpp(b); }
};

static const char *format_name = "4BPP SNES";
static format_4bpp_factory factory(format_name);

#endif // FORMAT_4BPP_H
