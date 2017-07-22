#include "palette_manager.h"

palette_manager::palette_manager(QObject *parent) : QObject(parent)
{
	palette_container palette;
	for(int i = 0; i < 256; i++){
		int color = QColor::fromHsl(22.5 * (i & 15), 40 + ((255 - i) >> 4) * 13, 50 + (i >> 4) * 6).rgba();
		palette.set_color_pc(256, 0, i, color);
	}
	register_palette(palette);
}

int palette_manager::register_palette(palette_container palette)
{
	return update_palette(next_palette_id++, palette);
}

int palette_manager::update_palette(int id, palette_container palette)
{
	palettes[id] = palette;
	return id;
}

palette_container palette_manager::get_palette(int id)
{
	return palettes[id];
}
