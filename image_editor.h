#ifndef IMAGE_EDITOR_H
#define IMAGE_EDITOR_H

#include <QObject>
#include <QWidget>
#include <QUndoGroup>
#include <QFile>
#include <QPushButton>
#include <QMap>
#include <QComboBox>

#include "tile_data.h"

class canvas;
class abstract_format;
class palette_manager;

class image_editor : public QWidget
{
	Q_OBJECT
	public:
		explicit image_editor(QWidget *parent, QString file_name, 
		                      QUndoGroup *undo_group, palette_manager *controller, bool new_file = false);
		~image_editor() override;
		
		QString load_error();
		
		void set_focus();
		void update_window();
		QString get_file_name();
		
		bool can_save();
		void save(QString path);
		bool new_file();
		
		void change_format(int a);
		
		void context_menu(const QPoint& position);
		void set_selected_tile(const tile_data tile);
	signals:
		void save_state_changed(bool save);
		void update_status_text(QString text);

	protected:
		virtual void keyPressEvent(QKeyEvent *event) override;
		virtual void wheelEvent(QWheelEvent *event) override;
		virtual bool event(QEvent *event) override;

	private:
		canvas *draw_area = nullptr;
		palette_manager *palette_controller = nullptr;
		QUndoStack *undo_stack = nullptr;
		
		QPushButton *page_up = new QPushButton(QChar(u'\u219F'), this);
		QPushButton *tile_up = new QPushButton(QChar(u'\u2191'), this);
		QPushButton *page_down = new QPushButton(QChar(u'\u21A1'), this);
		QPushButton *tile_down = new QPushButton(QChar(u'\u2193'), this);
		
		QFile image_file;
		bool is_new;
		int save_state = 0;
		QByteArray buffer;
		QMap<QString, abstract_format *> formats;
		QComboBox *format_selection = new QComboBox(this);
		
		void update_save_state(int direction);
};
#endif // IMAGE_EDITOR_H
