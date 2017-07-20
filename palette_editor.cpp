#include <QPushButton>
#include <QFile>
#include <QColor>
#include <QGridLayout>
#include <QDebug>

#include "palette_manager.h"
#include "palette_editor.h"
#include "palette_container.h"

palette_editor::palette_editor(QWidget *parent, QString file, palette_manager *controller, bool new_file)
        : QWidget(parent)
{
	QFile palette_file;
	palette_file.setFileName(file);
	palette_file.open(QFile::ReadWrite);
	QByteArray buffer = palette_file.readAll();
	
	palette_controller = controller;
	is_new = new_file;
	
	QGridLayout *layout = new QGridLayout();
	palette_container palette;
	
	for(int i = 0; i < 256; i++){
		swatches[i] = new QPushButton(this);
		swatches[i]->setAutoFillBackground(true);
		swatches[i]->setFlat(true);
		swatches[i]->setMaximumSize(16, 16);
		swatches[i]->setMinimumSize(16, 16);
		
		palette.set_color_snes(256, 0, i, (buffer.at(i * 2) & 0xFF) | (buffer.at(i * 2 + 1) << 8));
		
		QPalette button_palette;
		button_palette.setColor(QPalette::Button, palette.get_color_pc(256, 0, i));
		swatches[i]->setPalette(button_palette);
		layout->addWidget(swatches[i], i >> 4, i & 0x0F, 1, 1, Qt::AlignTop);
	}
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding), 0, 16, Qt::AlignTop);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);	
	setLayout(layout);
	
	id = palette_controller->register_palette(palette);
}
