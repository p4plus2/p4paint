#ifndef IMAGE_EDITOR_H
#define IMAGE_EDITOR_H

#include <QObject>
#include <QWidget>
#include <QUndoGroup>
#include <QFile>
#include <QPushButton>
#include <QMap>
#include <QComboBox>

class canvas;
class abstract_format;

class image_editor : public QWidget
{
	Q_OBJECT
	public:
		explicit image_editor(QWidget *parent, QString file_name, QUndoGroup *undo_group, bool new_file = false);
		~image_editor();
		
		QString load_error();
		
		void set_focus();
		void update_window();
		QString get_file_name();
		
		bool can_save();
		void save(QString path);
		bool new_file();
		
		void change_format(int a);
		
		void context_menu(const QPoint& position);
	signals:
		void save_state_changed(bool save);

	protected:
		virtual void keyPressEvent(QKeyEvent *event);
		virtual void wheelEvent(QWheelEvent *event);
		virtual bool event(QEvent *event);

	private:
		canvas *draw_area;
		
		QPushButton *page_up = new QPushButton(QChar(u'\u219F'), this);
		QPushButton *tile_up = new QPushButton(QChar(u'\u2191'), this);
		QPushButton *page_down = new QPushButton(QChar(u'\u21A1'), this);
		QPushButton *tile_down = new QPushButton(QChar(u'\u2193'), this);
		
		QFile image_file;
		bool is_new;
		int save_state = 0;
		QUndoStack *undo_stack;
		QByteArray buffer;
		QMap<QString, abstract_format *> formats;
		QComboBox *format_selection = new QComboBox(this);
		
		void update_save_state(int direction);
};
#endif // IMAGE_EDITOR_H
