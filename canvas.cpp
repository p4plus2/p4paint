#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QMouseEvent>

#include "canvas.h"
#include "image_editor.h"
#include "utility.h"
#include "graphics_formats/abstract_format.h"

#include "palette_container.h"
#include "palette_manager.h"

canvas::canvas(image_editor *parent, QByteArray *b, palette_manager *controller) :
        QWidget(parent)
{
	buffer = b;
	palette_controller = controller;
}

void canvas::scroll_tiles(int delta)
{
	offset_y += delta;
	offset_y = clamp(offset_y, 0, qMax((tile_count-x_tiles*y_tiles)/x_tiles, 0));
	update();
}

void canvas::set_scale(int scale_factor)
{
	scale = scale_factor;
	
	setMinimumSize(x_tiles * tile_width * scale, qMin(y_tiles * tile_height * scale, 512));
	setMaximumWidth(x_tiles * tile_width * scale);
	
	update();
}

void canvas::set_format(abstract_format *image_format)
{
	format = image_format;
	x_tiles = format->default_x_tiles();
	y_tiles = format->default_y_tiles();
	
	tile_count = format->max_tiles();
	tiles = format->get_tiles(0, tile_count);
	
	palette_container palette = palette_controller->get_palette(0);
	for(auto &tile : tiles){
		tile.image.setColorTable(palette.get_subpalette(256, 0));
	}
	
	set_scale(scale);
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
