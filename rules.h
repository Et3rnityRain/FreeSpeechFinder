/*!
* \file rules.h
* \brief FreeSpeechFinder
*/

#ifndef RULES_H
#define RULES_H
#include "sentence.h"

/// Класс, хранящий правила и выполняющий проверку предложений
class Rules
{
public:
    QString textTense; ///< Время текста
    QString textPerson; ///< Лицо текста

    bool checkRules(Sentence &sentense);

    bool RhetoricalQuestion(Sentence &sentence); // Сравнить с первым правилом
    bool ExclamotarySentence(Sentence &sentence); // Сравнить со вторым правилом
    bool ChangeNarrative(Sentence &sentence); // Сравнить с третьим правилом
    bool TalkingToYourself(Sentence &sentence); // Сравнить с четвертым правилом
    bool Thoughts(Sentence &sentence); // Сравнить с пятым правилом
    bool ChangePersonNarrative(Sentence &sentence); // Сравнить с шестым правилом
};

#endif // RULES_H
