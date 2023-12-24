#pragma once
#include <random>
#include <qwidget.h>
#include <qpainter.h>


class Book : public QWidget
{
private:
	Q_OBJECT
	static int volumes;
	QPainter painter;
	bool IsFocus;
	bool isAvailible;
	static QVector<int> remainingVolumes;

public:
	int NumVolume;
	static int Width;
	static int Height;
	int Thickness;
	static int ThickMin, ThickMax;

	Book(int thick, int numVol, QWidget* parent) : QWidget(parent)
	{
		IsFocus = false;
		isAvailible = true;
		NumVolume = numVol;
		Thickness = thick;
		setAcceptDrops(true);
	}

	Book(QWidget* parent = 0) : QWidget(parent)
	{
		setAcceptDrops(true);
		isAvailible = false;
		IsFocus = false;
		NumVolume = GetRandVolume();
		Thickness = rand() % (ThickMax - ThickMin) + ThickMin;
	}

	static int GetRandVolume();
	void RemoveFocus();
signals:
	void checkAvailability(int);
	

public slots:
	void recieve(bool);

protected:
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent*) override;
};
