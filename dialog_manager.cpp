#include "dialog_manager.h"
#include "image_editor.h"

dialog_manager::dialog_manager(QWidget *parent) :
        QObject(parent)
{

}

void dialog_manager::connect_to_editor(image_editor *editor)
{
#define CONNECT(D,E,S,T) connect((D *)find_dialog(E), &D::S, editor, &hex_editor::T);

#undef CONNECT
}

void dialog_manager::set_active_editor(image_editor *editor)
{
	for(auto &dialog : dialog_map){
		dialog->set_active_editor(editor);
		dialog->refresh();
	}
}

void dialog_manager::raise_dialog(dialog_events id)
{
	abstract_dialog *dialog = find_dialog(id);
	dialog->show();
	dialog->raise();
	dialog->activateWindow();
}

bool dialog_manager::event(QEvent *event)
{
	if(event->type() != (QEvent::Type)DIALOG_EVENT){
		return QObject::event(event);
	}
	raise_dialog(((dialog_event *)event)->sub_type());
	return true;
}

abstract_dialog *dialog_manager::find_dialog(dialog_events id)
{
	if(dialog_map.contains(id)){
		return dialog_map[id];
	}
	qDebug() << "Error: Dialog " << id << " not found";
	return 0;
}
