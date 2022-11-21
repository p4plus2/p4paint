#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QPushButton>

class image_editor;

class toolbox : public QWidget
{
		Q_OBJECT
	public:
		explicit toolbox(QWidget *parent = nullptr);
		void set_active_editor(image_editor *editor);
		
	signals:
		
	public slots:
		
	private:
		image_editor *active_editor = nullptr;
};

#endif // TOOLBOX_H
