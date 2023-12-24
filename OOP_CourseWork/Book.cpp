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
int Book::volumes = 0;
QVector<int> Book::remainingVolumes = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };

void Book::paintEvent(QPaintEvent* e) 
{
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
	//IsFocus = true;
	//repaint();
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
			//connect(this, SIGNAL(removeFromRack(int)), r, SLOT(DelBook(int)));
			//emit removeFromRack(NumVolume);
			//disconnect(this, SIGNAL(removeFromRack(int)), r, SLOT(DelBook(int)));
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