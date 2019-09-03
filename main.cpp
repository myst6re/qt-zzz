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
#include <QCoreApplication>
#include <QTimer>
#ifdef Q_OS_WIN
#include <QTextCodec>
#endif
#include <iostream>
#include "arguments.h"
#include "zzz.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
#ifdef Q_OS_WIN
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 850"));
#endif

	Arguments args;
	Observer *observer;
	ObserverStdOut stdObserver;

	if (args.quiet()) {
		observer = nullptr;
	} else {
		observer = &stdObserver;
	}

	if (args.help() || args.paths().isEmpty()) {
		args.showHelp();
	} else {
		bool hasMultipleFiles = args.paths().count() > 1;

		foreach (const QString &path, args.paths()) {

			if (hasMultipleFiles) {
				stdObserver.setFilename(QDir::toNativeSeparators(path));
			}

			Zzz zzz(path);

			if (args.extract()) {
				if (!zzz.extractTo(args.destination(), observer)) {
					std::cout << "Error " << qPrintable(zzz.lastInErrorString()) << qPrintable(zzz.lastOutErrorString());
				}
			} else {
				std::cout << "Not implemented";
			}
		}
	}

	QTimer::singleShot(0, &a, SLOT(quit()));

	return a.exec();
}
