#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include "debug.h"
#include "events/event_types.h"
#include "dialogs/abstract_dialog.h"

class image_editor;
class palette_editor;

class dialog_manager : public QObject
{
		Q_OBJECT
	public:
		explicit dialog_manager(QWidget *parent = nullptr);
		
		void connect_to_image(image_editor *image);
		void set_active_image(image_editor *image);
		
		void connect_to_palette(palette_editor *palette);
		void set_active_palette(palette_editor *palette);
	
	protected:
		virtual bool event(QEvent *event) override;
		
	private:
		QMap<dialog_events, abstract_dialog *> dialog_map;
		
		void raise_dialog(dialog_events id);
		abstract_dialog *find_dialog(dialog_events id);
		
};

#endif // DIALOG_MANAGER_H
