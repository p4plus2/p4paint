#ifndef ABSTRACT_DIALOG_H
#define ABSTRACT_DIALOG_H

#include <QDialog>

#include "debug.h"
#include "factory_list.h"

class image_editor;

class abstract_dialog : public QDialog
{
		Q_OBJECT
	public:
		explicit abstract_dialog(QWidget *parent);
		void set_active_editor(image_editor *editor);
		
	public slots:
		virtual void refresh();
		
	protected:
		image_editor *active_editor;
		
};


struct dialog_factory;
extern factory_list<dialog_factory> *dialog_list;

struct dialog_factory
{		
	dialog_factory(QString n)
	{
		if(!dialog_list){
			dialog_list = new factory_list<dialog_factory>;
		}
		name = n;
		dialog_list->add_factory(this);
	}
	virtual abstract_dialog *get_dialog(QWidget *parent) = 0;
	
	QString name;
};

#endif // ABSTRACT_DIALOG_H
