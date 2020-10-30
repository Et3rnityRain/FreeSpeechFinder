/*!
* \file sentence.cpp
* \brief FreeSpeechFinder
*/

#include "sentence.h"
#include <QThread>

Sentence::Sentence()
{
    QString dir = QDir::currentPath();
    dir.remove(dir.lastIndexOf("/"), dir.size() - dir.lastIndexOf("/"));
    dir.append("/stanford-corenlp-full-2018-02-27");

    path = dir;
}

/*!
Удаление прямой речи из текста
\param elementaryTokens[in|out] - ссылка на массив токенов, где нужно удалить прямую речь
*/
bool Sentence::isDirectSpeech()
{
    if (!isDS && sentence.contains("“") && sentence.contains("”"))
    {
        isDS = false;
        return true;
    }
    else if (!isDS && sentence.contains("“"))
    {
        isDS = true;
        return true;
    }
    else if (isDS && sentence.contains("“") && sentence.contains("”"))
    {
        isDS = true;
        return true;
    }
    else if(isDS && sentence.contains("”"))
    {
        isDS = false;
        return true;
    }

    return isDS;
}

/*!
Загрузка предложения в файл
\param path[in]- путь к Stanford Core NLP
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

/*!
Получение информации из Stanford Core NLP
*/
void Sentence::getInfoFromStanford()
{
    QProcess proc;
    proc.startDetached(path + "/start.bat");
    QThread::sleep(5);
}

/*!
Загрузка предложения в память
*/
void Sentence::loadInfoToMemory()
{
    QFile file(path + "/input.txt.xml");
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QTextStream in(&file);
        data = in.readAll();
        file.close();
    }
}

/*!
\Определение время преложения
\return - время предложения
*/
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

/*!
\Определение лица преложения
\return - лицо предложения
*/
int Sentence::getPerson()
{
        if (sentence.contains("I ") || sentence.contains(" we ") || sentence.contains("We "))
            return first;
        else if(sentence.contains(" he ") || sentence.contains("He ") || sentence.contains(" she ") || sentence.contains("She ") || sentence.contains(" it ") || sentence.contains("It "))
            return third;
        else if (sentence.contains("You ") || sentence.contains(" you ") || sentence.contains("They ") || sentence.contains(" they "))
            return second;
        else if (data.contains("NNP")) // Не содержит местоимений, а только имя собственное
            return third;
        else
            return first; // Безличное предложение
}
