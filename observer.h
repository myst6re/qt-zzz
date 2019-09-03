/****************************************************************************
 ** Copyright (C) 2009-2012 Arzel Jérôme <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H

#include <QString>

class Observer
{
public:
	Observer();
	virtual ~Observer() {}

	inline void setMaximum(qint64 maximum) {
		_maximum = maximum;
	}

	inline qint64 maximum() const {
		return _maximum;
	}

	virtual void setValue(qint64 value)=0;
private:
	qint64 _maximum;
};

class ObserverPercent : public Observer
{
public:
	ObserverPercent();
	void setValue(qint64 value);
	virtual void setPercent(quint8 percent)=0;
private:
	quint8 _lastPercent;
};

class ObserverStdOut : public ObserverPercent
{
public:
	ObserverStdOut();
	inline void setFilename(const QString &filename) {
		_filename = filename;
	}
	virtual void setPercent(quint8 percent);
private:
	QString _filename;
};

#endif // OBSERVER_H
