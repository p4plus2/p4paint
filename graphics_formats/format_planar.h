#ifndef FORMAT_8BPP_H
#define FORMAT_8BPP_H

#include "abstract_format.h"

template <int BIT_DEPTH>
class format_planar : public abstract_format
{
	public:
		using abstract_format::abstract_format;
		virtual int default_x_tiles() override;
		virtual int default_y_tiles() override;
		virtual int max_tiles() override;
		virtual tile_data get_tile(int offset) override;
		virtual QVector<tile_data>get_tiles(int offset, int count) override;
		virtual int get_color_depth() override;
		
		const int tile_size = 8 * BIT_DEPTH;
};

template <int BIT_DEPTH>
struct format_planar_factory : public format_factory
{
	using format_factory::format_factory;
	virtual abstract_format *get_format(const QByteArray *b) override { return new format_planar<BIT_DEPTH>(b); }
};

static format_planar_factory<2> factory_2bpp("2BPP SNES");
static format_planar_factory<3> factory_3bpp("3BPP SNES");
static format_planar_factory<4> factory_4bpp("4BPP SNES");
static format_planar_factory<8> factory_8bpp("8BPP SNES");
#endif // FORMAT_8BPP_H
