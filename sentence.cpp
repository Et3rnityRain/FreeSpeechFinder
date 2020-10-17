#include "sentence.h"

Sentence::Sentence()
{
    QString dir = QDir::currentPath();
    dir.remove(dir.lastIndexOf("/"), dir.size() - dir.lastIndexOf("/"));
    dir.append("/stanford-corenlp-full-2018-02-27");

    path = dir;
}

/* !
 * \Удаление тэгов
 * \param[in|out] elementaryTokens - ссылка на массив токенов, где нужно удалить прямую речь
 */
void Sentence::deleteDirectSpeech(QList <QString> &elementaryTokens)
{
    for (int i = 0; i < elementaryTokens.size(); i++)
    {
        if (elementaryTokens[i].contains("\""))
        {
            while(!elementaryTokens[i].contains("\""))
            {
                elementaryTokens.removeAt(i);
            }
            if (elementaryTokens[i + 1] == "-" || elementaryTokens[i + 2] == "-")
                while(!elementaryTokens[i].contains("!") || !elementaryTokens[i].contains(".") || !elementaryTokens[i].contains("?"))
                    elementaryTokens.removeAt(i);
            elementaryTokens.removeAt(i);
        }
    }
}

/* !
 * \Удаление тэгов
 * \param[in|out] text - ссылка на текст, где нужно удалить тэги
 */
void Sentence::deleteTags(QString &text)
{
    QRegExp rx("<\/?[a-z]+>");
    text.remove(rx);
}

/* !
 * \Загрузка предложения в файл
 * \param[in] path - путь к Stanford Core NLP
 */
void Sentence::loadTextToFile()
{
    QFile file(path + "/input.txt");
    if ((file.exists())&&(file.open(QIODevice::WriteOnly)))
    {
        QTextStream out(&file);
        out << sentence;
        file.close();
    }
}

/* !
 * \Получение информации из Stanford Core NLP
 */
void Sentence::getInfoFromStanford()
{
    QProcess proc;
    proc.startDetached(path + "/start.bat");
    proc.waitForFinished(-1);
}

/* !
 * \Загрузка предложения в память
 */
void Sentence::loadInfoToMemory()
{
    QFile file(path + "/input.txt.out");
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QTextStream in(&file);
        in >> data;
        file.close();
    }
}
