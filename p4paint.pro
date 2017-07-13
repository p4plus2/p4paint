#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T00:28:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = p4paint
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        main_window.cpp \
    settings_manager.cpp \
    object_group.cpp \
    canvas.cpp \
    dialog_manager.cpp \
    menu_manager.cpp \
    dialogs/abstract_dialog.cpp \
    menus/abstract_menu_item.cpp \
    menus/history_menu_item.cpp \
    image_editor.cpp \
    graphics_formats/format_4bpp.cpp \
    graphics_formats/abstract_format.cpp \
    graphics_formats/format_gsu.cpp

HEADERS  += main_window.h \
    debug.h \
    settings_manager.h \
    object_group.h \
    events/event_types.h \
    events/general_event.h \
    events/settings_event.h \
    canvas.h \
    dialog_manager.h \
    menu_manager.h \
    dialogs/abstract_dialog.h \
    menus/abstract_menu_item.h \
    menus/history_menu_item.h \
    factory_list.h \
    version.h \
    utility.h \
    image_editor.h \
    graphics_formats/format_4bpp.h \
    graphics_formats/abstract_format.h \
    tile_data.h \
    graphics_formats/format_gsu.h

OTHER_FILES += \
    version.sh
