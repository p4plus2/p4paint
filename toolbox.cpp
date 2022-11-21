#include <QGridLayout>
#include "image_editor.h"

#include "toolbox.h"

toolbox::toolbox(QWidget *parent) : QWidget(parent)
{
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(new QPushButton("test", this));
	setLayout(layout);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void toolbox::set_active_editor(image_editor *editor)
{
	active_editor = editor;
}
