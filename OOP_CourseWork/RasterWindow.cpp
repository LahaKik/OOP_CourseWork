#include "RasterWindow.h"

RasterWindow::RasterWindow(QWindow* parent) : QWindow(parent), m_backingStore(new QBackingStore(this))
{
	setMinimumSize(QSize(600, 600));
}