#include "abstract_format.h"

abstract_format::abstract_format(const QByteArray *b)
{
	buffer = b;
}

factory_list<format_factory> *format_list;
