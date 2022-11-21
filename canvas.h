#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

#include "tile_data.h"

class image_editor;
class palette_manager;
class abstract_format;

class canvas : public QWidget
{
		Q_OBJECT
	public:
		explicit canvas(image_editor *parent, QByteArray *b, palette_manager *controller);
		void scroll_tiles(int delta);
		void set_scale(int scale_factor);
		void set_format(abstract_format *image_format);
		
		void set_tile_palette(int palette);
		void set_tile_subpalette(int subpalette);
	
	signals:
		void tile_changed(const tile_data tile);
		
	protected:
		void paintEvent(QPaintEvent *event) override;
		
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
	
	private:
		QByteArray *buffer;
		palette_manager *palette_controller;
		
		abstract_format *format;
		QVector<tile_data> tiles;
		int tile_count = 0;
		int offset_y = 0;
		int scale = 4;
		
		bool mouse_held;
		QPoint mouse_press;
		QPoint mouse_current;
		QPoint mouse_release;
		
		QPoint clip_to_tile(QPoint point);
		int position_to_tile(QPoint position);
		
		int y_tiles = 32;
		int x_tiles = 32;
		const int tile_width = 8;
		const int tile_height = 8;
		
};
#endif // CANVAS_H
