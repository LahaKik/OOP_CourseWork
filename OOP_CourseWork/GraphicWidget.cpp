#include "GraphicWidget.h"
#include <qgridlayout.h>


GraphicWidget::GraphicWidget(QWidget* parent) : QWidget(parent)
{
	setStyleSheet("background-color: dimgray");
	auto layout = new QGridLayout();
	table = new Table(this, 3);
	rack = new Rack(4, table);
	layout->addWidget(table, 0, 0);
	layout->addWidget(rack, 0, 1);
	
	setLayout(layout);
	emit complete();
}
