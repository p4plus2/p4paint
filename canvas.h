#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

#include "tile_data.h"

class image_editor;

class canvas : public QWidget
{
		Q_OBJECT
	public:
		explicit canvas(QByteArray *b, image_editor *parent = 0);
		void scroll_tiles(int delta);
		void set_scale(int scale_factor);
		
	protected:
		void paintEvent(QPaintEvent *event);
		
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
	
	private:
		QByteArray *buffer;
		QVector<tile_data> tiles;
		int tile_count = 0;
		int offset_y = 0;
		int scale = 4;
		
		bool mouse_held;
		QPoint mouse_press;
		QPoint mouse_current;
		QPoint mouse_release;
		
		const int y_tiles = 16;
		const int x_tiles = 16;
		const int tile_width = 8;
		const int tile_height = 8;
		
};
#endif // CANVAS_H
