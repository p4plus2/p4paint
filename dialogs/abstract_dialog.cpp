#include "abstract_dialog.h"
#include "debug.h"

abstract_dialog::abstract_dialog(QWidget *parent) : QDialog(parent)
{
	setWindowFlags(Qt::Tool);
}

void abstract_dialog::set_active_image(image_editor *image)
{
	active_image = image;
}

void abstract_dialog::set_active_palette(palette_editor *palette)
{
	active_palette = palette;
}

void abstract_dialog::refresh()
{
	if(!active_image){
		close();
	}
}

factory_list<dialog_factory> *dialog_list;
