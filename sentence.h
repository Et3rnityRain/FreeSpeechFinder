#ifndef SENTENCE_H
#define SENTENCE_H
#include "QString"
#include "QList"
#include "QDir"
#include "QTextStream"
#include "QProcess"

class Sentence
{
public:
    Sentence();

    QString sentence;
    QString data;
    enum {past, present, future} tense;
    enum {first, second, third} person;
    QString path;

    int getTense(); // Найти время предложения
    int getPerson(); // Найти лицо предложения

    void deleteDirectSpeech(QList <QString> &elementaryTokens);
    void deleteTags(QString &text); // Удалить тэги из фрагмента текста
    void loadTextToFile(); // Загрузить предложение в файл
    void getInfoFromStanford(); // Получить информацию в StanfordCoreNLP
    void loadInfoToMemory(); // Загрузить полученную информацию в память
};

#endif // SENTENCE_H
