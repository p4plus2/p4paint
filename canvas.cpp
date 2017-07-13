#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QMouseEvent>

#include "canvas.h"
#include "image_editor.h"
#include "utility.h"
#include "graphics_formats/abstract_format.h"

#include "graphics_formats/format_gsu.h"

canvas::canvas(QByteArray *b, image_editor *parent) :
        QWidget(parent)
{
	buffer = b;
	
	//abstract_format *format = new format_4bpp(buffer);
	abstract_format *format = new format_gsu(buffer);
	tile_count = format->max_tiles();
	tiles = format->get_tiles(0, tile_count);
	setMinimumWidth(x_tiles * tile_width * scale);
}

void canvas::scroll_tiles(int delta)
{
	offset_y += delta;
	offset_y = clamp(offset_y, 0, qMax(tile_count-256, 0));
	update();
}

void canvas::set_scale(int scale_factor)
{
	scale = scale_factor;
	setMinimumWidth(x_tiles * tile_width * scale);
}

void canvas::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	painter.fillRect(0, 0, x_tiles * tile_width * scale, y_tiles * tile_height * scale, Qt::black);
	for(int y = offset_y; y < offset_y + y_tiles && y < tiles.size() / x_tiles; y++){
		for(int x = 0; x < x_tiles; x++){
			QImage image = tiles[y * x_tiles + x].image.scaled(tile_width * scale, tile_height * scale);
			painter.drawImage(x * tile_width * scale, (y - offset_y) * tile_height * scale, image);
		}
	}
}

void canvas::mousePressEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton){
		event->accept();
		mouse_held = true;
		mouse_press = event->pos();
		mouse_current = event->pos();
	}
}

void canvas::mouseMoveEvent(QMouseEvent *event)
{
	if(mouse_held){
		event->accept();
		mouse_current = event->pos();
	}
}

void canvas::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton && mouse_held){
		event->accept();
		mouse_release = event->pos();
		mouse_current = event->pos();
	}
}