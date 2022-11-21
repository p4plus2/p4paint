#include <QStatusBar>
#include <QTabWidget>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>

#include "main_window.h"
#include "debug.h"
#include "settings_manager.h"
#include "version.h"
#include "image_editor.h"
#include "palette_editor.h"
#include "utility.h"

main_window::main_window(QWidget *parent)
        : QMainWindow(parent)
{
	statusBar()->addWidget(status_bar);
	
	QWidget* widget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(widget);
	layout->addWidget(image_tab_widget);
	QHBoxLayout *tools_layout = new QHBoxLayout(widget);
	tools_layout->addWidget(palette_tab_widget);
	tools_layout->addWidget(toolbox_widget);
	layout->addLayout(tools_layout);
	widget->setLayout(layout);
	setCentralWidget(widget);
	
	image_tab_widget->setTabsClosable(true);
	image_tab_widget->setMovable(true);
	palette_tab_widget->setTabsClosable(true);
	palette_tab_widget->setMovable(true);	
	
	settings_manager settings;
	QVariant geometry = settings.get("geometry");
	QVariant state = settings.get("window_state");
	QVariant saved_last_directory = settings.get("last_directory");
	if(state.isValid()){
		restoreState(state.toByteArray());
	}
	if(geometry.isValid()){
		restoreGeometry(geometry.toByteArray());
		resize(600, size().height());
		image_tab_widget->resize(size());
	}
	
	if(saved_last_directory.isValid()){
		last_directory = saved_last_directory.toString();
	}else{
		last_directory = QDir::homePath();
	}
	
	connect(image_tab_widget, &QTabWidget::tabCloseRequested, this, &main_window::close_image);
	connect(palette_tab_widget, &QTabWidget::tabCloseRequested, this, &main_window::close_palette);
	connect(image_tab_widget, &QTabWidget::currentChanged, this, &main_window::changed_image);
	connect(palette_tab_widget, &QTabWidget::currentChanged, this, &main_window::changed_palette);
	menu_controller->connect_to_widget(this, WINDOW_EVENT);
	menu_controller->connect_to_widget(dialog_controller, DIALOG_EVENT);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	window()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	create_new_palette_tab("Default", true);
	palette_editor *default_palette = (palette_editor *)palette_tab_widget->currentWidget();
	default_palette->set_palette(0);
	
#ifdef USE_DEFAULT_BIN
	//create_new_tab("g/GFX00.bin");
	//create_new_tab("bank26-gsu.bin");
	create_new_palette_tab("mode_7p.bin");
	create_new_image_tab("mode_7.bin");
#endif
}

image_editor *main_window::get_active_editor()
{
	int current_tab = image_tab_widget->currentIndex();
	if(current_tab != -1){
		return get_image_editor(current_tab);
	}
	return nullptr;
}


bool main_window::close_image(int i)
{
	image_editor *editor = get_image_editor(i);
	if(editor->can_save()){
		typedef QMessageBox message;
		QString name = editor->get_file_name();
		int button = message::warning(this, "Save", "Do you wish to save any unsaved changes to " + name + "?", 
		                              message::Yes | message::No | message::Cancel, message::Yes);
		switch(button){
			case message::Yes:
				if(!save_image(i)){
					return false;
				}
				
			break;
			case message::Cancel:
				return false;
			break;
			default:
			break;
		}
	}
	QWidget *widget = image_tab_widget->widget(i);
	image_tab_widget->removeTab(i);
	delete widget;
	return true;
}

bool main_window::close_palette(int i)
{
	palette_editor *editor = get_palette_editor(i);
	if(editor->can_save()){
		typedef QMessageBox message;
		QString name = editor->get_file_name();
		int button = message::warning(this, "Save", "Do you wish to save any unsaved changes to " + name + "?", 
		                              message::Yes | message::No | message::Cancel, message::Yes);
		switch(button){
			case message::Yes:
				if(!save_image(i)){
					return false;
				}
				
			break;
			case message::Cancel:
				return false;
			break;
			default:
			break;
		}
	}
	QWidget *widget = palette_tab_widget->widget(i);
	palette_tab_widget->removeTab(i);
	delete widget;
	return true;
}

void main_window::changed_image(int i)
{
	if(i == -1){
//		dialog_controller->set_active_image(nullptr);
		menu_controller->connect_to_widget(nullptr, EDITOR_EVENT);
		toolbox_widget->set_active_editor(nullptr);
		return;
	}
	
	image_editor *editor = get_image_editor(i);

	editor->set_focus();
//	dialog_controller->set_active_image(editor);
	menu_controller->connect_to_widget(editor, EDITOR_EVENT);
	toolbox_widget->set_active_editor(editor);
}

void main_window::changed_palette(int i)
{
	if(i == -1){
	//	dialog_controller->set_active_editor(nullptr);
	//	menu_controller->connect_to_widget(nullptr, EDITOR_EVENT);
		return;
	}
	
	palette_editor *editor = get_palette_editor(i);

	//dialog_controller->set_active_editor(editor);
	//menu_controller->connect_to_widget(editor, EDITOR_EVENT);
}

void main_window::image_save_state(bool clean)
{
	image_editor *editor = get_image_editor(image_tab_widget->currentIndex());
	if(clean){
		image_tab_widget->setTabText(image_tab_widget->currentIndex(), editor->get_file_name());
	}else{
		image_tab_widget->setTabText(image_tab_widget->currentIndex(), "* "+editor->get_file_name());
	}
}

void main_window::palette_save_state(bool clean)
{
	palette_editor *editor = get_palette_editor(palette_tab_widget->currentIndex());
	if(clean){
		palette_tab_widget->setTabText(palette_tab_widget->currentIndex(), editor->get_file_name());
	}else{
		palette_tab_widget->setTabText(palette_tab_widget->currentIndex(), "* "+editor->get_file_name());
	}	
}

void main_window::new_image()
{
	new_counter++;
	create_new_image_tab("Untitled_"+QString::number(new_counter), true);
}

void main_window::new_palette()
{
	new_counter++;
	create_new_palette_tab("Untitled_"+QString::number(new_counter), true);
}

void main_window::open_image()
{
	QString file_types = "Typical files (*.bin *.smc *.sfc);;All files(*.*)";
	QStringList file_list = QFileDialog::getOpenFileNames(this, "Open file(s)", last_directory, file_types);
	for(auto &file_name : file_list){
		create_new_image_tab(file_name);
	}
	
	if(file_list.size()){
		last_directory = absolute_path(file_list.at(0));
	}
}

void main_window::open_palette()
{
	QString file_types = "Typical files (*.bin *.pal *.tpl *.mw3);;All files(*.*)";
	QStringList file_list = QFileDialog::getOpenFileNames(this, "Open file(s)", last_directory, file_types);
	for(auto &file_name : file_list){
		create_new_palette_tab(file_name);
	}
	
	if(file_list.size()){
		last_directory = absolute_path(file_list.at(0));
	}
}

bool main_window::save_image(bool override_name, int target)
{
	image_editor *editor = get_image_editor((target != -1 ) ? target : image_tab_widget->currentIndex());
	QString name = "";
	if(editor->new_file() || override_name){
		name = QFileDialog::getSaveFileName(this, "Save", last_directory, 
	                                            "ROM files (*.smc *.sfc);;All files(*.*)");
		if(name == ""){
			return false;
		}
		last_directory = absolute_path(name);
	}
	editor->save(name);
	return true;
}

bool main_window::save_palette(bool override_name, int target)
{
	palette_editor *editor = get_palette_editor((target != -1 ) ? target : palette_tab_widget->currentIndex());
	QString name = "";
	if(editor->new_file() || override_name){
		name = QFileDialog::getSaveFileName(this, "Save", last_directory, 
	                                            "ROM files (*.smc *.sfc);;All files(*.*)");
		if(name == ""){
			return false;
		}
		last_directory = absolute_path(name);
	}
	editor->save(name);
	return true;
}

bool main_window::event(QEvent *event)
{
	if(event->type() != (QEvent::Type)WINDOW_EVENT){
		return QWidget::event(event);
	}

	switch(((window_event *)event)->sub_type()){
		#define CASE(V, C, ...) case V: C(__VA_ARGS__); return true
		
		CASE(NEW_IMAGE, new_image);
		CASE(NEW_PALETTE, new_palette);
	        CASE(OPEN_IMAGE,open_image);
		CASE(OPEN_PALETTE, open_palette);
	        CASE(SAVE_IMAGE, save_image);
		CASE(SAVE_PALETTE, save_palette);
	        CASE(SAVE_IMAGE_AS, save_image, true);
		CASE(SAVE_PALETTE_AS, save_palette, true);
	        CASE(CLOSE_IMAGE, close_image, image_tab_widget->currentIndex());
		CASE(CLOSE_PALETTE, close_palette, image_tab_widget->currentIndex());
	        CASE(CLOSE, close);
	        CASE(VERSION, display_version_dialog);
		default:
			qDebug() << "Bad event" << ((editor_event *)event)->sub_type();
			return false;
			
		#undef CASE
	}
}

void main_window::closeEvent(QCloseEvent *event)
{
	while(image_tab_widget->count()){
		if(!close_image(0)){
			event->setAccepted(false);
			return;
		}
	}
	settings_manager settings;
	settings.set("geometry", saveGeometry());
	settings.set("window_state", saveState());
	settings.set("last_directory", last_directory);
	QApplication::quit();
	QMainWindow::closeEvent(event);
}

void main_window::create_new_image_tab(QString name, bool new_file)
{
	QSize window_size = size();
	image_editor *editor = new image_editor(this, name, undo_group, palette_controller, new_file);
	if(editor->load_error() != ""){
		QMessageBox::critical(this, "Invalid ROM", editor->load_error(), QMessageBox::Ok);
		delete editor;
		return;
	}
	
	connect(editor, &image_editor::save_state_changed, this, &main_window::image_save_state);
	connect(editor, &image_editor::update_status_text, status_bar, &QLabel::setText);
	
	image_tab_widget->addTab(editor, QFileInfo(name).fileName());
	image_tab_widget->setCurrentWidget(editor);
	
	editor->set_focus();
	editor->update_window();
	resize(window_size);
}

void main_window::create_new_palette_tab(QString name, bool new_file)
{
	QSize window_size = size();
	palette_editor *editor = new palette_editor(palette_tab_widget, name, palette_controller, new_file);
	if(editor->load_error() != ""){
		QMessageBox::critical(this, "Invalid ROM", editor->load_error(), QMessageBox::Ok);
		delete editor;
		return;
	}
	
	//connect(editor, &palette_editor::save_state_changed, this, &main_window::file_save_state);
	
	palette_tab_widget->addTab(editor, QFileInfo(name).fileName());
	palette_tab_widget->setCurrentWidget(editor);
	
	resize(window_size);
}

image_editor *main_window::get_image_editor(int i) const
{
	return dynamic_cast<image_editor *>(image_tab_widget->widget(i));
}

palette_editor *main_window::get_palette_editor(int i) const
{
	return dynamic_cast<palette_editor *>(palette_tab_widget->widget(i));
}

main_window::~main_window()
{
}

