#include <QGridLayout>
#include <QMenu>
#include <QUndoStack>
#include <QDebug>

#include "graphics_formats/abstract_format.h"
#include "image_editor.h"
#include "canvas.h"
#include "utility.h"

image_editor::image_editor(QWidget *parent, QString file_name, QUndoGroup *undo_group, bool new_file) :
        QWidget(parent)
{
	is_new = new_file;
	
	if(is_new){
		update_save_state(1);
	}else{
		image_file.setFileName(file_name);
		image_file.open(QFile::ReadWrite);
		buffer = image_file.readAll();
	}
	
	undo_stack = new QUndoStack(undo_group);
	undo_stack->setActive();
	
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &image_editor::customContextMenuRequested, this, &image_editor::context_menu);
	
	draw_area = new canvas(&buffer, this);
	draw_area->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	
	connect(tile_up, &QPushButton::clicked, [=](bool){ draw_area->scroll_tiles(-1); });
	connect(page_up, &QPushButton::clicked, [=](bool){ draw_area->scroll_tiles(-16); });
	connect(tile_down, &QPushButton::clicked, [=](bool){ draw_area->scroll_tiles(1); });
	connect(page_down, &QPushButton::clicked, [=](bool){ draw_area->scroll_tiles(16); });
	
	QVBoxLayout *scroll_layout = new QVBoxLayout();
	scroll_layout->addWidget(page_up, Qt::AlignTop);
	scroll_layout->addWidget(tile_up, Qt::AlignTop);
	scroll_layout->addStretch(1);
	scroll_layout->addWidget(tile_down, Qt::AlignBottom);
	scroll_layout->addWidget(page_down, Qt::AlignBottom);
	
	QVector<format_factory *> factories = format_list->get_factories();
	for(auto factory : factories){
		formats.insert(factory->name, factory->get_format(&buffer));
		format_selection->addItem(factory->name);
	}
	
	connect(format_selection, resolve<int>::from(&QComboBox::activated), this, &image_editor::change_format);
	change_format(0); //set a default format
	
	QGridLayout *layout = new QGridLayout();
	layout->addWidget(draw_area, 0, 0, 1, 1, Qt::AlignTop);
	layout->addLayout(scroll_layout, 0, 1, 1, 1, Qt::AlignRight);
	layout->addWidget(format_selection, 1, 0);
	setLayout(layout);
}

QString image_editor::load_error()
{
	return "";
}

void image_editor::set_focus()
{
	
}

void image_editor::update_window()
{
	
}

QString image_editor::get_file_name()
{
	return image_file.fileName();
}

bool image_editor::can_save()
{
	return false;
}

void image_editor::save(QString path)
{
	
}

bool image_editor::new_file()
{
	return is_new;
}

void image_editor::change_format(int a)
{
	Q_UNUSED(a);
	draw_area->set_format(formats[format_selection->currentText()]);
	updateGeometry();
	adjustSize();
	propagate_resize(this);
}

void image_editor::context_menu(const QPoint& position)
{	
	QMenu menu;
	//typedef QKeySequence hotkey;
	//bool selection_active = selection_area.is_active();
	//menu.addAction("Cut", this, SLOT(cut()), hotkey::Cut)->setEnabled(selection_active);
	//menu.addAction("Copy", this, SLOT(copy()), hotkey::Copy)->setEnabled(selection_active);
	//menu.addAction("Paste", this, SLOT(paste()), hotkey::Paste)->setEnabled(buffer->check_paste_data());
	//menu.addAction("Delete", this, SLOT(delete_text()), hotkey::Delete)->setEnabled(selection_active);
	//menu.addSeparator();
	//menu.addAction("Select all", this, SLOT(select_all()), hotkey::SelectAll);
	menu.exec(mapToGlobal(position));
}

void image_editor::keyPressEvent(QKeyEvent *event)
{
	
}

void image_editor::wheelEvent(QWheelEvent *event)
{
	
}

bool image_editor::event(QEvent *event)
{
	return false;
}

void image_editor::update_save_state(int direction)
{
	save_state += direction;
	emit save_state_changed(!save_state);
}

image_editor::~image_editor()
{
	
}
