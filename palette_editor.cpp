#include <QPushButton>
#include <QFile>
#include <QColor>

#include "palette_editor.h"

QColor pc_to_snes(unsigned char low, unsigned char high)
{
	return {(low & 0x1F) << 3, ((low | (high << 8)) >> 5 & 0x1F) << 3, (low >> 2 & 0x1F) << 3};
}

palette_editor::palette_editor(QWidget *parent)
        : QWidget(parent)
{
	QFile palette_file;
	palette_file.setFileName("mode_7p.bin");
	palette_file.open(QFile::ReadWrite);
	QByteArray buffer = palette_file.readAll();
	
	for(int i = 0; i < 256; i++){
		swatches[i] = new QPushButton(this);
		swatches[i]->setFlat(true);
		
		QColor color = pc_to_snes(buffer.at(i * 2), buffer.at(i * 2 + 1));
		colors.append(color.rgba());
		
		QPalette palette;
		palette.setColor(QPalette::Button, color);
		swatches[i]->setPalette(palette);
	}
}

QVector<QRgb> palette_editor::get_color_table()
{
	return colors;
}
