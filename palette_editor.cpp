#include <QPushButton>
#include <QFile>
#include <QColor>
#include <QGridLayout>
#include <QDebug>
#include <QColorDialog>

#include "palette_manager.h"
#include "palette_editor.h"
#include "palette_container.h"

palette_editor::palette_editor(QWidget *parent, QString file, palette_manager *controller, bool new_file)
        : QWidget(parent)
{
	is_new = new_file;
	palette_controller = controller;
	QByteArray buffer;
	
	if(is_new){
		buffer.fill(0x00, 512);
	}else{
		palette_file.setFileName(file);
		palette_file.open(QFile::ReadWrite);
		buffer = palette_file.readAll();		
	}
	
	if(buffer.size() < 512){
		//todo error
		return;
	}
	
	
	QGridLayout *swatch_layout = new QGridLayout();
	palette_container palette;
	
	for(int i = 0; i < 256; i++){
		swatches[i] = new QPushButton(this);
		swatches[i]->setAutoFillBackground(true);
		swatches[i]->setFlat(true);
		swatches[i]->setMaximumSize(16, 16);
		swatches[i]->setMinimumSize(16, 16);
		swatches[i]->setCheckable(true);
		
		connect(swatches[i], &QPushButton::pressed, [this](){
			for(int i = 0; i < 256; i++){
				swatches[i]->setChecked(false);
			}
		});
		
		connect(swatches[i], &QPushButton::pressed, [i, this](){
			set_active_swatch(i);
		});
		
		palette.set_color_snes(256, 0, i, (quint16)(buffer.at(i * 2) & 0xFF) | (buffer.at(i * 2 + 1) << 8));
		
		QPalette button_palette;
		button_palette.setColor(QPalette::Button, palette.get_color_pc(256, 0, i));
		swatches[i]->setPalette(button_palette);
		swatch_layout->addWidget(swatches[i], i >> 4, i & 0x0F, 1, 1, Qt::AlignTop);
	}
	swatch_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 16, Qt::AlignTop);
	swatch_layout->setSpacing(0);
	swatch_layout->setContentsMargins(0, 0, 0, 0);	
	
	active_swatch = new QPushButton(this);
	active_swatch->setAutoFillBackground(true);
	active_swatch->setFlat(true);
	active_swatch->setMaximumSize(96, 64);
	active_swatch->setMinimumSize(96, 64);
	
	connect(active_swatch, &QPushButton::pressed, [this](){
		set_color_button(QColorDialog::getColor());
	});
	
	QGridLayout *active_swatch_layout = new QGridLayout();
	active_swatch_layout->addWidget(active_swatch, 0, 0, 1, 1, Qt::AlignCenter);
	active_swatch_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding), 0, 1, Qt::AlignTop);
	
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addLayout(swatch_layout);
	layout->addLayout(active_swatch_layout);
	
	setLayout(layout);
	
	id = palette_controller->register_palette(palette);
	qDebug() << id;
}

QString palette_editor::load_error()
{
	return "";
}

QString palette_editor::get_file_name()
{
	return palette_file.fileName();
}

bool palette_editor::new_file()
{
	return is_new;
}

bool palette_editor::can_save()
{
	return false;
}


void palette_editor::save(QString path)
{
	
}

void palette_editor::set_palette(int palette_id)
{
	id = palette_id;
	palette_container palette = palette_controller->get_palette(id);
	for(int i = 0; i < 256; i++){
		QPalette button_palette;
		button_palette.setColor(QPalette::Button, palette.get_color_pc(256, 0, i));
		swatches[i]->setPalette(button_palette);
	}
	swatches[0]->setChecked(true);
	set_active_swatch(0);
}

void palette_editor::set_active_swatch(int swatch_id)
{
	active_swatch_id = swatch_id;
	active_swatch->setPalette(swatches[active_swatch_id]->palette());
}

void palette_editor::set_color_button(QColor color)
{
	if(color.isValid()){
		QPalette button_palette;
		button_palette.setColor(QPalette::Button, color);
		swatches[active_swatch_id]->setPalette(button_palette);
		active_swatch->setPalette(button_palette);
	}
}
