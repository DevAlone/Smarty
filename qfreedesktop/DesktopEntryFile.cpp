#include "DesktopEntryFile.h"
namespace qfreedesktop {
DesktopEntryFile::DesktopEntryFile(const QString& path)
    : path(path)
{
    parseFile();
}

QString DesktopEntryFile::getItem(const QString& group, const QString& key, bool* exist) const
{
    if (data.find(group) == data.end() || data[group].find(key) == data[group].end()) {
        if (exist)
            *exist = false;

        return "";
    }

    return data[group][key];
}

void DesktopEntryFile::parseFile()
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        _isValid = false;
        return;
    }

    _isValid = true;

    QTextStream in(&file);
    QString lastSection = "";
    data[lastSection] = QMap<QString, QString>();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.size() > 2) {
            if (line.startsWith('[') && line.endsWith(']')) {
                // section
                lastSection = line.mid(1, line.size() - 2);
            } else if (line.contains('=')) {
                QPair<QString, QString> keyVal;
                auto delimiterPos = line.indexOf('=');
                keyVal.first = line.mid(0, delimiterPos);
                keyVal.second = line.mid(delimiterPos + 1, line.size() - delimiterPos - 1);

                data[lastSection][keyVal.first] = keyVal.second;
            }
        }
    }
}

bool DesktopEntryFile::isValid() const
{
    return _isValid;
}
}
