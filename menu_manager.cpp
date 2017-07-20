#include <QMenuBar>
#include <QCoreApplication>

#include "menu_manager.h"
#include "menus/history_menu_item.h"
#include "image_editor.h"
#include "main_window.h"
#include "object_group.h"
#include "debug.h"

menu_manager::menu_manager(main_window *parent, QMenuBar *m, QUndoGroup *u) :
        QObject(parent)
{
	window = parent;
	menu_bar = m;
	create_menus();
	create_actions(u);
}

void menu_manager::group_connect_to_widget(QObject *object, event_types event)
{
	if(!event_map.contains(event)){
		event_map[event] = new object_group(this);
	}
	((object_group *)event_map[event])->add_to_group(object);
}

void menu_manager::create_menus()
{
	menu_list.append(new QMenu("&File"));
	
	for(auto &menu : menu_list){
		connect(menu, &QMenu::aboutToShow, this, [=](){ check_enabled(menu); });
		menu_bar->addMenu(menu);
	}
}

template <typename T, typename S>
void menu_manager::add_toggle_action(QString text, S type, toggle_function toggle, hotkey key, QMenu *menu)
{
	menu->addAction(new abstract_menu_item(text, new T(type), toggle, key, this, false));
}

template <typename T, typename S>
void menu_manager::add_action(QString text, S type, hotkey key, QMenu *menu)
{
	menu->addAction(new abstract_menu_item(text, new T(type), nullptr, key, this, false));
}

template <typename T, typename S>
void menu_manager::add_check_action(QString text, S type, hotkey key, QMenu *menu)
{
	menu->addAction(new abstract_menu_item(text, new T(type), nullptr, key, this, true));
}

template <typename T, typename S>
void menu_manager::add_group_action(QString text, S type, hotkey key, QMenu *menu, QActionGroup *group)
{
	menu->addAction(group->addAction((new abstract_menu_item(text, new T(type), nullptr, key, this, true))));
}

void menu_manager::create_actions(QUndoGroup *undo_group)
{
	#define MENU_TEST(T) image_editor *editor = menu_manager::window->get_active_editor(); \
			return editor && editor->T
	toggle_function active_editor    = []() -> bool { return menu_manager::window->get_active_editor(); };
	toggle_function active_palette    = []() -> bool { return false; };
	//toggle_function active_selection  = []() -> bool { MENU_TEST(is_selecting()); };
	//toggle_function clipboard_usable  = []() -> bool { MENU_TEST(is_pasteable()); };
	#undef MENU_TEST
	
	QMenu *menu = find_menu("&File");
	add_action       <window_event>("&New image",      NEW_IMAGE,                       hotkey::New,     menu);
	add_action       <window_event>("&New palette",    NEW_PALETTE,                     hotkey("Alt+n"), menu);
	add_action       <window_event>("&Open image",     OPEN_IMAGE,                      hotkey::Open,    menu);
	add_action       <window_event>("Open &palette",   OPEN_PALETTE,                    hotkey("Alt+o"), menu);
	add_toggle_action<window_event>("&Save image",     SAVE_IMAGE,      active_editor,  hotkey::Save,    menu);
	add_toggle_action<window_event>("Save p&alette",   SAVE_PALETTE,    active_palette, hotkey("Alt+s"), menu);
	add_toggle_action<window_event>("Save image as",   SAVE_IMAGE_AS,   active_editor,  hotkey::SaveAs,  menu);
	add_toggle_action<window_event>("Save palette as", SAVE_PALETTE_AS, active_palette, hotkey("Ctrl+Alt+s"), menu);
	menu->addSeparator();
	add_toggle_action<window_event>("&Close image",   CLOSE_IMAGE,   active_editor,  hotkey::Close,   menu);
	add_toggle_action<window_event>("&Close palette", CLOSE_PALETTE, active_palette, hotkey("Alt+w"), menu);
	add_action       <window_event>("E&xit",      CLOSE,                    hotkey::Quit,   menu);
}

QMenu *menu_manager::find_menu(QString id)
{
	for(auto &menu : menu_list){
		if(menu->title() == id){
			return menu;
		}
	}
	qDebug() << "Error: Menu " << id << " not found";
	return 0;
}

void menu_manager::enable_checkable(QActionGroup *group)
{
	QList<QAction *> actions = group->actions();
	for(auto &current : actions){
		current->setCheckable(true);
	}
	actions.first()->setChecked(true);
}

void menu_manager::post_event(QEvent *event)
{
	event_types event_type = (event_types)event->type();
	if(event_map.contains(event_type) && event_map[event_type]){
		QCoreApplication::sendEvent(event_map[event_type], event);
	}
}

void menu_manager::check_enabled(QMenu *menu)
{
	for(auto &action : menu->actions()){
		if(!action->isSeparator() && !action->menu()){
			dynamic_cast<abstract_menu_item *>(action)->check_enabled();
		}
	}
}

menu_manager::~menu_manager()
{
	for(auto &menu : menu_list){
		delete menu;
	}
}

main_window *menu_manager::window = nullptr;
