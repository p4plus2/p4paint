#ifndef FORMAT_GSU_H
#define FORMAT_GSU_H

#include "abstract_format.h"

class format_gsu : public abstract_format
{
	public:
		using abstract_format::abstract_format;
		virtual int default_x_tiles() override;
		virtual int default_y_tiles() override;
		virtual int max_tiles() override;
		virtual tile_data get_tile(int offset) override;
		virtual QVector<tile_data>get_tiles(int offset, int count) override;
		virtual int get_color_depth() override;
		
		const int tile_size = 0x20;
};


struct format_gsu_factory : public format_factory
{
	using format_factory::format_factory;
	virtual abstract_format *get_format(const QByteArray *b) override { return new format_gsu(b); }
};

static const char *format_name = "GSU SNES";
static format_gsu_factory factory(format_name);
#endif // FORMAT_GSU_H
