#include "palette_manager.h"

palette_manager::palette_manager(QObject *parent) : QObject(parent)
{
	
}

int palette_manager::register_palette(palette_container p)
{
	return update_palette(next_palette_id++, p);
}

int palette_manager::update_palette(int id, palette_container p)
{
	palettes[id] = p;
	return id;
}

palette_container palette_manager::get_palette(int id)
{
	return palettes[id];
}
