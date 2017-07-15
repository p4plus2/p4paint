#include "abstract_format.h"

abstract_format::abstract_format(const QByteArray *b)
{
	buffer = b;
}

unsigned char abstract_format::get_byte(int offset)
{
	return offset < buffer->size() ? buffer->at(offset) : 0;
}

factory_list<format_factory> *format_list;
