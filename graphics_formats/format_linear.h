#ifndef FORMAT_LINEAR_H
#define FORMAT_LINEAR_H

#include "abstract_format.h"

class format_linear : public abstract_format
{
	public:
		using abstract_format::abstract_format;
		virtual int default_x_tiles() override;
		virtual int default_y_tiles() override;
		virtual int max_tiles() override;
		virtual tile_data get_tile(int offset) override;
		virtual QVector<tile_data>get_tiles(int offset, int count) override;
		virtual int get_color_depth() override;
		
		const int tile_size = 0x40;
};


struct format_linear_factory : public format_factory
{
	using format_factory::format_factory;
	virtual abstract_format *get_format(const QByteArray *b) override { return new format_linear(b); }
};

static const char *format_name = "Mode 7 SNES";
static format_linear_factory factory(format_name);
#endif // FORMAT_LINEAR_H
