#ifndef PALETTE_EDITOR_H
#define PALETTE_EDITOR_H

#include <QWidget>
#include <QFile>

class QPushButton;
class palette_manager;

class palette_editor : public QWidget
{
	Q_OBJECT
	public:
		explicit palette_editor(QWidget *parent, QString file, palette_manager *controller, bool new_file);
		QString get_file_name();
		QString load_error();
		bool new_file();
		bool can_save();		
		void save(QString path);
		void set_palette(int id);
		void set_active_swatch(int active_swatch_id);
	private:
		void set_color_button(QColor color);
		palette_manager *palette_controller;
		QPushButton *swatches[256];
		QPushButton *active_swatch;
		QVector<QRgb> colors;
		QFile palette_file;
		bool is_new;
		int id;
		int active_swatch_id;
};

#endif // PALETTE_EDITOR_H
