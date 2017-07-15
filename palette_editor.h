#ifndef PALETTE_EDITOR_H
#define PALETTE_EDITOR_H

#include <QWidget>

class QPushButton;

class palette_editor : public QWidget
{
	Q_OBJECT
	public:
		explicit palette_editor(QWidget *parent);
		QVector<QRgb> get_color_table();
		
	private:
		QPushButton *swatches[256];
		QVector<QRgb> colors;
};

#endif // PALETTE_EDITOR_H
