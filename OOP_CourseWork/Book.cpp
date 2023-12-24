#include "Book.h"
#include <qevent.h>
#include <qdrag.h>
#include <qmimedata.h>
#include "Table.h"
#include "Rack.h"

int Book::ThickMin = 15;
int Book::ThickMax = 25;
int Book::Height = 80;
int Book::Width = 50;

QVector<int> Book::remainingVolumes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };

Book::Book(int thick, int numVol, QWidget* parent) : QWidget(parent)
{
	IsFocus = false;
	isAvailible = true;
	NumVolume = numVol;
	Thickness = thick;
	setAcceptDrops(true);
}

Book::Book(QWidget* parent) : QWidget(parent)
{
	setAcceptDrops(true);
	isAvailible = false;
	IsFocus = false;
	NumVolume = GetRandVolume();
	Thickness = rand() % (ThickMax - ThickMin) + ThickMin;
}

void Book::paintEvent(QPaintEvent* e) 
{
	QPainter painter;
	painter.begin(this);
	if (IsFocus)
		painter.setPen(Qt::DashLine);
	else
		painter.setPen(Qt::SolidLine);
	painter.drawRect(0, 0, width() - 1, height() - 1);
	painter.drawText(width() / 2 - 5, height() / 2 + 5, QString().number(NumVolume));
	painter.end();
}

void Book::RemoveFocus()
{
	IsFocus = false;
	repaint();
}

void Book::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		Table* t = qobject_cast<Table*>(parent());
		Rack* r = qobject_cast<Rack*>(parent());
		if(t)
		{
			emit checkAvailability(NumVolume);
			if (isAvailible)
			{
				IsFocus = true;
				repaint();
				QDrag* drag = new QDrag(this);
				QMimeData* mimeData = new QMimeData;
				mimeData->setText(QString().number(NumVolume) + " " + QString().number(Thickness) + " " + parent()->objectName());
				qDebug() << parent()->objectName();
				drag->setMimeData(mimeData);
				drag->exec(Qt::CopyAction);
			}
		}
		else if (r->IsFull)
		{
			IsFocus = true;
			repaint();
			QDrag* drag = new QDrag(this);
			QMimeData* mimeData = new QMimeData;
			mimeData->setText(QString().number(NumVolume) + " " + QString().number(Thickness) + " " + parent()->objectName());
			drag->setMimeData(mimeData);
			drag->exec(Qt::CopyAction);
		}
	}
}

void Book::recieve(bool ans)
{
	isAvailible = ans;
}

int Book::GetRandVolume()
{
	if (!remainingVolumes.isEmpty())
	{
		int ind = rand() % remainingVolumes.count();
		int Vol = remainingVolumes[ind];
		remainingVolumes.remove(ind);
		return Vol;
	}
	return -1;
}