#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QUndoGroup>
#include <QLabel>

#include "dialog_manager.h"
#include "menu_manager.h"
#include "palette_manager.h"

class image_editor;

class main_window : public QMainWindow
{
		Q_OBJECT
		
	public:
		main_window(QWidget *parent = 0);
		image_editor *get_active_editor();
		~main_window();
		
	public slots:
		bool close_image(int i);
		bool close_palette(int i);
		void changed_image(int i);
		void changed_palette(int i);
		void image_save_state(bool clean);
		void palette_save_state(bool clean);
		void new_image();
		void new_palette();
		void open_image();
		void open_palette();
		bool save_image(bool override_name = false, int target = -1);
		bool save_palette(bool override_name = false, int target = -1);
		
	protected:
		virtual bool event(QEvent *event);
		virtual void closeEvent(QCloseEvent *event);

	private:
		QLabel *statusbar = new QLabel(this);
		QTabWidget *tab_widget = new QTabWidget(this);
		QTabWidget *palette_tab_widget = new QTabWidget(this);
		QUndoGroup *undo_group = new QUndoGroup(this);
		dialog_manager *dialog_controller = new dialog_manager(this);
		menu_manager *menu_controller = new menu_manager(this, menuBar(), undo_group);
		palette_manager *palette_controller = new palette_manager(this);
		int new_counter = 0;
		QString last_directory;

		void create_new_tab(QString name, bool new_image = false);
		void create_new_palette_tab(QString name, bool new_image = false);
		image_editor *get_editor(int i) const;
		
};

#endif // MAIN_WINDOW_H
