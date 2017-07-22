#ifndef PALETTE_MANAGER_H
#define PALETTE_MANAGER_H

#include <QObject>
#include <QMap>

#include "palette_container.h"

class palette_manager : public QObject
{
		Q_OBJECT
	public:
		explicit palette_manager(QObject *parent = nullptr);
		int register_palette(palette_container palette);
		int update_palette(int id, palette_container palette);
		palette_container get_palette(int id);
	
	private:
		int next_palette_id = 0;

		QMap <int, palette_container> palettes;
};

#endif // PALETTE_MANAGER_H
