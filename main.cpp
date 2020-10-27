/*!
* \file main.cpp
* \brief FreeSpeechFinder
*/

#include <QCoreApplication>
#include <QProcess>
#include "sentence.h"
#include "rules.h"
#include "QDir"
#include "QDirIterator"
#include "QTextStream"
#include "stdio.h"
#include "QThread"
#include "test.cpp"
#include "QXmlStreamReader"

/*!
Нахождение прямой речи на странице
\param QString &pageText[in|out] - Текст страницы
\param QString tense[in] - Время текста
\param QString person[in] - Лицо текста
*/
void findFreeSpeech(QString &pageText, QString tense, QString person);

/*!
Распаковать epub-файла
\param path[in] - Путь к файлу
*/
void unpack(QString path);

/*!
Запаковать epub-файла
\param path[in] - Путь к файлу
*/
void pack(QString path);

/*!
Получение текста из файла
\param path[in] - Путь к файлу
\param QString tense[in] - Время текста
\param QString person[in] - Лицо текста
*/
void getTextFromFile(QString path, QString tense, QString person);

bool isFind = false;

/*!
Функция main
\param argc[in] - Количество введенных параметров командной строки
\param *argv[][in] - Введенные парметры командной строки
\return 0 - Успешное выполнение
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream in(stdin);
    QString path;
    QString tense;
    QString person;

    if (argc == 2)
    {
        if (argv[1] == "test")
        {
            Test test;
            test.RunAllTest();
            test.AnalyzeResult();
            return 0;
        }
        else
        {
            in >> tense;
            in >> person;
        }
    }
    else if (argc == 4)
    {
        path = argv[1];
        tense = argv[2];
        person = argv[3];
    }
    else if (argc < 4)
    {
        in >> path;

        if(path == "test")
        {
            Test test;
            test.RunAllTest();
            test.AnalyzeResult();
            return 0;
        }
        else
            in >> tense >> person;
    }
    else if (argc > 4)
    {
        printf("\nIncorrect input data.\n");
        return 0;
    }


    // Проверка на некорректные входные данные
    if (!QFile::exists(path))
    {
        printf("\nIncorrect filepath.\n");
        return 0;
    }
    if (tense != "present" && tense != "past" && tense != "future")
    {
        printf("\nIncorrect input data.\n");
        return 0;
    }
    if (person != "first" && person != "second" && person != "third")
    {
        printf("\nIncorrect input data.\n");
        return 0;
    }

    unpack(path);
    getTextFromFile(path, tense, person);

    // Проверка на нахождение свободной косвенной речи
    if(!isFind)
    {
        printf("\nNo free speech in text.\n");
        QDir dir(path.remove(".epub"));
        dir.removeRecursively();
        return 0;
    }

    pack(path);

    return a.exec();
}

void unpack(QString path)
{
    QString dir = QDir::currentPath();
    dir.remove(dir.lastIndexOf("/"), dir.size() - dir.lastIndexOf("/")).append("/7-Zip/7z.exe");

    QProcess proc;
    QStringList list;;

    QString curDir = path;
    curDir.remove(".epub").prepend("-o");

    list << "x" << path << curDir;
    proc.start(dir, list);
    proc.waitForFinished(-1);
}

void pack(QString path)
{
    QString dir = QDir::currentPath();
    dir.remove(dir.lastIndexOf("/"), dir.size() - dir.lastIndexOf("/")).append("/7-Zip/7z.exe");

    QProcess proc;
    QStringList list;
    QString tmp = path;

    list << "a" << "-tzip" << "-sdel" << path.remove(".epub").append("_FreeSpeech")
         << path.remove("_FreeSpeech").append("\\").append("META-INF")
         << path.remove("META-INF").append("OEBPS")
         << path.remove("OEBPS").append("mimetype");

    proc.start(dir, list);
    proc.waitForFinished(-1);

    QDir old(path.remove("\\mimetype"));
    old.removeRecursively();

    QString old_name = tmp.remove(".epub").append("_FreeSpeech.zip");
    QString new_name = tmp.remove(".zip").append(".epub");
    QFile::rename(old_name, new_name);
}

void getTextFromFile(QString path, QString tense, QString person)
{
    QString pageText;
    QDirIterator iter(path.remove(".epub").append("\\OEBPS\\"), QDir::Files);

    while(iter.hasNext())
    {
        QFile file (iter.next());

        if (iter.fileName().indexOf(".xhtml") != -1 || iter.fileName().indexOf(".html") != -1)
        {

            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream read(&file);
                read.setCodec("UTF-8");
                pageText = read.readAll();
                file.close();
            }

            findFreeSpeech(pageText, tense, person);

            if(file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream write(&file);
                write.setCodec("UTF-8");
                write << pageText;
                file.close();
            }
        }
    }
}

void findFreeSpeech(QString &pageText, QString tense, QString person)
{
    Rules rules;
    Sentence sentence;
    QList <QString> text;
    QString textString;
    QList <QString> elementaryTokens;

    QXmlStreamReader xml(pageText);
    while (!xml.atEnd())
    {
        if (xml.readNext() == QXmlStreamReader::Characters )
        {
            textString += xml.text();
        }
    }

    textString.remove("\n");

    elementaryTokens = textString.split(QRegExp("\\b"));
    sentence.deleteDirectSpeech(elementaryTokens);

    // Разделение текста на предложения
    int begin = 0;
    for (int i = 1; i < elementaryTokens.size(); i++)
    {
        if (elementaryTokens[i].contains("!") || elementaryTokens[i].contains(".") || elementaryTokens[i].contains("?"))
            if(elementaryTokens[i - 1] != "Dr" && elementaryTokens[i - 1] != "Mr" && elementaryTokens[i - 1] != "Mrs")
            {
                QString sentence;
                for (int j = begin; j <= i; j++)
                    sentence.append(elementaryTokens[j]);
                text.append(sentence);
                begin = i + 1;
            }
    }

    rules.textTense = tense;
    rules.textPerson = person;

    // Проверка каждого предложения на соответствие с правилами
    for (int i = 0; i < text.size(); i++)
    {
        sentence.sentence = text[i];
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        // Выделение тэгами
        if(rules.checkRules(sentence))
        {
            pageText.replace(QString(text[i]), QString(text[i].append("</span>").prepend("<span color=\"yellow\">")));
            isFind = true;
        }
    }
}

