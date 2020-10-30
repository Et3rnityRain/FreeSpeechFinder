/*!
* \file sentence.h
* \brief FreeSpeechFinder
*/

#ifndef SENTENCE_H
#define SENTENCE_H
#include "QString"
#include "QList"
#include "QDir"
#include "QTextStream"
#include "QProcess"

/// Класс, хранящий информацию о предложении
class Sentence
{
public:
    Sentence();

    QString sentence; ///< Предложение
    QString data; ///< Информация о предложении
    bool isDS = false;
    enum {past, present, future} tense; ///< Время предложения
    enum {first, second, third} person; ///< Лицо предложения
    QString path; ///< Путь к Stanford Core NLP

    int getTense(); // Найти время предложения
    int getPerson(); // Найти лицо предложения

    bool isDirectSpeech(); // Удалить прямую речь из фрагмента текста
    void loadTextToFile(); // Загрузить предложение в файл
    void getInfoFromStanford(); // Получить информацию в StanfordCoreNLP
    void loadInfoToMemory(); // Загрузить полученную информацию в память
};

#endif // SENTENCE_H
