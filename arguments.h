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
#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QStringList>
#include <QMap>
#include <QDir>

class Arguments
{
public:
	Arguments();
	[[ noreturn ]] void showHelp(int exitCode = 0);
	const QStringList &paths() const;
	const QDir &destination() const;
	bool extract() const;
	bool help() const;
	bool quiet() const;
	QMap<QString, QString> commands() const;
private:
	void parse();
	void wilcardParse();
	static QStringList searchFiles(const QString &path);
	QStringList _paths;
	QDir _directory;
	bool _extract, _help, _quiet;

};

#endif // ARGUMENTS_H
