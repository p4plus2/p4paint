#include "palette_manager.h"

palette_manager::palette_manager(QObject *parent) : QObject(parent)
{
	
}

int palette_manager::register_palette(palette_container p)
{
	update_palette(next_palette_id++, p);
}

void palette_manager::update_palette(int id, palette_container p)
{
	palettes[id] = p;
}

palette_container palette_manager::get_palette(int id)
{
	return palettes[id];
}
