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
#include "observer.h"
#include <stdio.h>

Observer::Observer()
{
}

ObserverPercent::ObserverPercent()
{
}

void ObserverPercent::setValue(qint64 value)
{
	quint8 percent = quint8(value * 100.0 / double(maximum()));

	if (percent != _lastPercent) {
		_lastPercent = percent;
		setPercent(percent);
	}
}

ObserverStdOut::ObserverStdOut()
{
}

void ObserverStdOut::setPercent(quint8 percent)
{
	printf("[%d%%] %s\r", percent, qPrintable(_filename));
}
