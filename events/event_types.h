#ifndef EVENT_TYPES
#define EVENT_TYPES

#include "general_event.h"

enum editor_events{
	CUT = QEvent::User+1,
	COPY,
	PASTE,
	SELECT_ALL,
	UNDO,
	REDO,
	EDITOR_EVENT_MAX
};

enum window_events{
	NEW_IMAGE = EDITOR_EVENT_MAX+1,
	NEW_PALETTE,
	OPEN_IMAGE,
	OPEN_PALETTE,
	SAVE_IMAGE,
	SAVE_PALETTE,
	SAVE_IMAGE_AS,
	SAVE_PALETTE_AS,
	CLOSE_IMAGE,
	CLOSE_PALETTE,
        CLOSE,
        VERSION,
	WINDOW_EVENT_MAX
};
enum dialog_events{
	DIALOG_EVENT_MAX = EDITOR_EVENT_MAX+1,
};

enum event_types : int{
	EDITOR_EVENT = EDITOR_EVENT_MAX,
	WINDOW_EVENT = WINDOW_EVENT_MAX,
	DIALOG_EVENT = DIALOG_EVENT_MAX,
	SETTINGS_EVENT,
	UNIMPLEMENTED
};

typedef general_event<editor_events, EDITOR_EVENT> editor_event;
typedef general_event<window_events, WINDOW_EVENT> window_event;
typedef general_event<dialog_events, DIALOG_EVENT> dialog_event;

#endif // EVENT_TYPES

