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

int Sentence::getTense()
{
    // Модальные глаголы
    if(data.contains("would") || data.contains("should") || data.contains("could") || data.contains("couldn't") || data.contains("had to") || data.contains("might"))
        return past;
    if (data.contains("can") || data.contains("can't") || data.contains("have to") || data.contains("must") || data.contains("may"))
        return true;

    // Subjunctive mood
    if(data.contains("if") && data.contains("were")) // If I were you...
        return present;

    // Complex Object
    if(data.contains("VBD") && (data.contains("VBG"))) // Future Simple
        return past;

    // Compound Sentenses и обычные предложения
    if(data.contains("VB") && (data.contains("will") || data.contains("shall"))) // Future Simple
        return future;
    if(data.contains("VBG") && (data.contains("will") || data.contains("shall"))) // Future Continious
        return future;
    if(data.contains("VBD") && (data.contains("will") || data.contains("shall"))) // Future Continious
        return future;
    if(data.contains("VBD")) // Verb, past tense
        return past;
    if(data.contains("VBN")) // Verb, past participle (Present or Past Perfect == past)
        return past;
    if(data.contains("VBG") && (data.contains("was") || data.contains("were"))) // Past Continious
        return past;
    if(data.contains("VBG") && (data.contains("has been") || data.contains("have been") || data.contains("had been"))) // Present или Past Perfect Continious == past
        return past;
    if(data.contains("VB") && (data.contains("would") || data.contains("should"))) // Future-in-the-Past == past
        return past;
    if(data.contains("VBZ")) // Verb, 3rd person singular present
        return present;
    if(data.contains("VBP")) // Verb, non-3rd person singular present
        return present;
    if(data.contains("VBG") && (data.contains("is") || data.contains("are") || data.contains("am"))) // Present participle
        return present;

    // Односложное предложение (impossible и т.п.)
    return present;
}
