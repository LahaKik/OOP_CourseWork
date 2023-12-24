#pragma once
#include <qwindow.h>
#include <qbackingstore.h>

class RasterWindow : public QWindow
{
	Q_OBJECT
	QBackingStore* m_backingStore = nullptr;
public:
	explicit RasterWindow(QWindow* parent = 0);
};

