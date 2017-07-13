#ifndef ABSTRACT_FORMAT_H
#define ABSTRACT_FORMAT_H

#include <QByteArray>
#include "tile_data.h"
#include "factory_list.h"

class abstract_format
{
	public:
		abstract_format(const QByteArray *b);
		virtual int default_x_tiles() = 0;
		virtual int default_y_tiles() = 0;
		virtual int max_tiles() = 0;
		virtual tile_data get_tile(int offset) = 0;
		virtual QVector<tile_data>get_tiles(int offset, int count) = 0;
		virtual int get_color_depth() = 0;
		
	protected:
		const QByteArray *buffer;
};

struct format_factory;
extern factory_list<format_factory> *format_list;

struct format_factory
{		
	format_factory(QString n)
	{
		if(!format_list){
			format_list = new factory_list<format_factory>;
		}
		name = n;
		format_list->add_factory(this);
	}
	virtual abstract_format *get_format(const QByteArray *b) = 0;
	
	QString name;
};

#endif // ABSTRACT_FORMAT_H
