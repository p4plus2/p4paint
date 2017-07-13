#ifndef FORMAT_4BPP_H
#define FORMAT_4BPP_H

#include "abstract_format.h"

class format_4bpp : public abstract_format
{
	public:
		using abstract_format::abstract_format;
		virtual tile_data get_tile(int offset);
		virtual QVector<tile_data>get_tiles(int offset, int count);
		virtual int get_color_depth();
};

#endif // FORMAT_4BPP_H
