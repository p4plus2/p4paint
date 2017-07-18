#ifndef PALETTE_CONTAINER_H
#define PALETTE_CONTAINER_H

#include <QVector>
#include <QColor>

class palette_container
{
	public:
		palette_container();
		
		void set_color_pc(int color_depth, int subpalette, int index, QRgb color);
		void set_color_snes(int color_depth, int subpalette, int index, quint16 color);
		
		QRgb get_color_pc(int color_depth, int subpalette, int index);
		QRgb get_color_snes(int color_depth, int subpalette, int index);
		
		QVector<QRgb> get_subpalette(int color_depth, int subpalette);
		void set_subpalette(int color_depth, int subpalette, QVector<QRgb> subcolors);
	private:
		QVector<QRgb> colors;
		
		quint16 to_snes(QRgb color);
		QRgb to_pc(quint16 color);
};

#endif // PALETTE_CONTAINER_H
