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
#include "arguments.h"
#include <QCoreApplication>
#include <QDir>
#include <QTextStream>

Arguments::Arguments() :
    _extract(false), _help(false), _quiet(false)
{
	parse();
}

const QStringList &Arguments::paths() const
{
	return _paths;
}

const QDir &Arguments::directory() const
{
	return _directory;
}

bool Arguments::extract() const
{
	return _extract;
}

bool Arguments::help() const
{
	return _help;
}

bool Arguments::quiet() const
{
	return _quiet;
}

void Arguments::parse()
{
	QStringList args = qApp->arguments();
	args.removeFirst(); // Application path

	if (!args.isEmpty()) {
		const QString &arg = args.takeFirst();

		if (arg == "extract") {
			_extract = true;
		} else if (arg == "pack") {
			_extract = false;
		} else {
			_help = true;
		}

		bool stopOptions = false;

		while (!args.isEmpty()) {
			const QString &arg = args.takeFirst();

			if (!stopOptions) {
				if (arg == "-h" || arg == "--help") {
					_help = true;
				} else if (arg == "-q" || arg == "--quiet") {
					_quiet = true;
				} else if (arg == "--") {
					stopOptions = true;
				} else {
					_paths << arg;
				}
			} else {
				_paths << arg;
			}
		}

		wilcardParse();
	} else {
		_help = true;
	}
}

QMap<QString, QString> Arguments::commands() const
{
	QMap<QString, QString> options;

	options["-h --help"] = "Show this help and quit.";
	options["-q --quiet"] = "Suppress all outputs";

	return options;
}

void Arguments::showHelp(int exitCode)
{
	QTextStream out(stdout, QIODevice::WriteOnly);
	out << "zzz extract ZZZ_FILE [ZZZ_FILE2...] OUTPUT_DIR\n";
	out << "zzz pack ZZZ_FILE SOURCE_DIR\n";

	out << "Options\n";

	QMapIterator<QString, QString> it(commands());
	while (it.hasNext()) {
		it.next();

		out << "\t" << qPrintable(it.key()) << "\n";
		out << "\t" << "\t" << qPrintable(it.value()) << "\n";
	}

	out.flush();

	::exit(exitCode);
}

QStringList Arguments::searchFiles(const QString &path)
{
	int index = path.lastIndexOf('/');
	QString dirname, filename;

	if (index > 0) {
		dirname = path.left(index);
		filename = path.mid(index + 1);
	} else {
		filename = path;
	}

	QDir dir(dirname);
	QStringList entryList = dir.entryList(QStringList(filename), QDir::Files);
	int i=0;
	foreach (const QString &entry, entryList) {
		entryList.replace(i++, dir.filePath(entry));
	}
	return entryList;
}

void Arguments::wilcardParse()
{
	QStringList paths;

	foreach (const QString &path, _paths) {
		if (path.contains('*') || path.contains('?')) {
			paths << searchFiles(QDir::fromNativeSeparators(path));
		} else {
			paths << QDir::fromNativeSeparators(path);
		}
	}

	if (!paths.isEmpty()) {
		// Output directory
		_directory = paths.takeLast();
		_paths = paths;
	}
}
