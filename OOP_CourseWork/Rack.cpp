#include "Rack.h"
#include <qpainter.h>
#include <qevent.h>
#include <qmimedata.h>

void Rack::paintEvent(QPaintEvent*)
{
	QPainter painter;
	QVector<QLine> frame;
	frame.append(QLine(width() / 2 - widthShelf / 2, height() - 10, width() / 2 - widthShelf / 2, height() - (Book::Height + 25) * CountShelf - 10));
	frame.append(QLine(width() / 2 + widthShelf / 2, height() - 10, width() / 2 + widthShelf / 2, height() - (Book::Height + 25) * CountShelf - 10));
	for (size_t i = 0; i < CountShelf; i++)
	{
		frame.append(QLine(width() / 2 - widthShelf / 2, height() - (Book::Height + 25) * (CountShelf - i) + 50 - 10, width() / 2 + widthShelf / 2, height() - (Book::Height + 25) * (CountShelf - i) + 50 - 10));
	}

	painter.begin(this);
	painter.drawLines(frame);
	painter.end();
}

void Rack::applyThickness(int thickness)
{
	widthShelf = thickness * 1.2 / CountShelf;
}

void Rack::dragEnterEvent(QDragEnterEvent* e)
{
	if (!IsSameBook(e) && CorrectBook(e))
	{
		e->acceptProposedAction();
	}
	else
	{
		Book* book = qobject_cast<Book*>(e->source());
		book->RemoveFocus();
	}
}

void Rack::dropEvent(QDropEvent* e)
{
	if (e->mimeData()->hasText())
	{
		QStringList spl = e->mimeData()->text().split(" ");
		int numVol = spl[0].toInt();
		int thick = spl[1].toInt();

		AddBook(thick, numVol);
	}
}

void Rack::DelBook(int Val)
{
	IsFull = false;
	delBook = Val;
	for (size_t i = 0; i < CountShelf; i++)
	{
		for (size_t j = 0; j < shelf[i].count(); j++)
		{
			if (Val == shelf[i][j]->NumVolume)
			{
				/*isFullShelf[i] = false;
				delete shelf[i][j];
				shelf[i].remove(j);*/
				shelf[i][j]->hide();
				break;
			}
		}
	}
}

bool Rack::IsSameBook(QDragEnterEvent* e)
{
	if (e->mimeData()->hasText())
	{
		QStringList spl = e->mimeData()->text().split(" ");
		int numVol = spl[0].toInt();
		if (numVol == delBook)
			return false;

		int thick = spl[1].toInt();
		for (size_t i = 0; i < CountShelf; i++)
		{
			for (size_t j = 0; j < shelf[i].count(); j++)
			{
				Book* tbook = shelf[i][j];
				qDebug() << tbook->NumVolume;
				if (tbook->NumVolume == numVol)
					return true;
			}
		}
	}
	return false;
}

void Rack::AddBook(int thick, int numVol)
{
	emit deleteBook(numVol);
	if (numVol == delBook)
	{
		for (size_t i = 0; i < CountShelf; i++)
		{
			for (size_t j = 0; j < shelf[i].count(); j++)
			{
				if (numVol == shelf[i][j]->NumVolume)
				{
					shelf[i][j]->show();
					IsFull = true;
					delBook = 0;
					return;
				}
			}
		}
	}

	for (size_t i = 0; i < CountShelf; i++)
	{
		if (widthShelf - offset[i] >= thick && !isFullShelf[i])
		{
			shelf[i].append(new Book(thick, numVol, this));
			shelf[i].last()->setGeometry(width() / 2 - widthShelf / 2 + offset[i], height() - (Book::Height + 25) * (CountShelf - i + 1.5) + 50 - 10 + Book::Height, thick, Book::Height);
			shelf[i].last()->show();
			offset[i] += thick;
			break;
		}
		else if (!isFullShelf[i])
		{
			isFullShelf[i] = true;
		}
	}
	lastBook = numVol;
}

bool Rack::CorrectBook(QDragEnterEvent* e)
{
	if (e->mimeData()->hasText())
	{
		QStringList spl = e->mimeData()->text().split(" ");
		int numVol = spl[0].toInt();
		if (spl[2] == "Rack")
			return false;

		if (numVol == lastBook + 1 || numVol == delBook)
		{
			if (numVol == 30)
				IsFull = true;
			return true;
		}
	}
	return false;
}
