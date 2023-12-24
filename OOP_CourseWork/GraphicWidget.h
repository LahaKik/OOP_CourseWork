#pragma once
#include <qwidget.h>
#include "Rack.h"
#include <qpushbutton.h>
#include "Table.h"

class GraphicWidget : public QWidget
{
	Q_OBJECT
	Rack* rack;
	Table* table;

public:
	GraphicWidget(QWidget* parent = nullptr);

signals:
	void complete();
};

