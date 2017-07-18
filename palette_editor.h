#ifndef PALETTE_EDITOR_H
#define PALETTE_EDITOR_H

#include <QWidget>

class QPushButton;
class palette_manager;

class palette_editor : public QWidget
{
	Q_OBJECT
	public:
		explicit palette_editor(QWidget *parent, QString file, palette_manager *controller, bool new_file);
		
	private:
		palette_manager *palette_controller;
		QPushButton *swatches[256];
		QVector<QRgb> colors;
		bool is_new;
};

#endif // PALETTE_EDITOR_H
