#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include "debug.h"
#include "events/event_types.h"
#include "dialogs/abstract_dialog.h"

class image_editor;

class dialog_manager : public QObject
{
		Q_OBJECT
	public:
		explicit dialog_manager(QWidget *parent = 0);
		
		void connect_to_editor(image_editor *editor);
		void set_active_editor(image_editor *editor);
	
	protected:
		virtual bool event(QEvent *event);
		
	private:
		QMap<dialog_events, abstract_dialog *> dialog_map;
		
		void raise_dialog(dialog_events id);
		abstract_dialog *find_dialog(dialog_events id);
		
};

#endif // DIALOG_MANAGER_H
