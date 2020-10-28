/*!
* \file rules.cpp
* \brief FreeSpeechFinder
*/

#include "rules.h"

/*!
Проверка на соответствие предложения с одним из правил
\param sentence[in] - предложение и необходимая информация о нем
\return - проходит ли предложение по какому-либо из правил (да/нет)
*/
bool Rules::checkRules(Sentence &sentence)
{
    return (RhetoricalQuestion(sentence) || ExclamotarySentence(sentence) || ChangeNarrative(sentence) || TalkingToYourself(sentence) || Thoughts(sentence) || ChangePersonNarrative(sentence));
}

/*!
Проверка на наличие в предложении риторического вопроса
\param sentence[in] - предложение и необходимая информация о нем
\return - проходит ли предложение по этому правилу (true/false)
*/
bool Rules::RhetoricalQuestion(Sentence &sentence)
{
    return sentence.sentence.contains("?");
}

/*!
Проверка на наличие в предложении восклицания
\param sentence[in] - предложение и необходимая информация о нем
\return - проходит ли предложение по этому правилу (true/false)
*/
bool Rules::ExclamotarySentence(Sentence &sentence)
{
    return sentence.sentence.contains("!");
}

/*!
Проверка на наличие в предложении смены времени повествования
\param sentence[in] - предложение и необходимая информация о нем
\return - проходит ли предложение по этому правилу (true/false)
*/
bool Rules::ChangeNarrative(Sentence &sentence)
{
    if(textTense == "present")
    {
        if(sentence.getTense() == sentence.past)
            return true;
    }
    else if(textTense == "past")
    {
        if(sentence.getTense() == sentence.present || sentence.getTense() == sentence.future)
            return true;
    }
    else
        return false;
}

/*!
Проверка на наличие в предложении конструкции "разговора героя с собой"
\param sentence[in] - предложение и необходимая информация о нем
\return - проходит ли предложение по этому правилу (true/false)
*/
bool Rules::TalkingToYourself(Sentence &sentence)
{
    QList <QString> talkingVerbs = {
        "tell",
        "told",
        "ask"
        "swear",
        "swore",
        "sworn"
    };

    QList <QString> structure = {
        "myself",
        "himself",
        "herself",
        "yourself",
        "ourselves",
        "yourselves",
        "themselves"
    };

    QList <QString> separators = {
        ",",
        ";",
        "and",
        "or",
        "but",
        "so"
    };

    for (int i = 0; i < structure.size(); i++)
        for (int j = 0; j < talkingVerbs.size(); j++)
            for (int k = 0; k < separators.size(); k++)
            {
                if(sentence.sentence.contains(structure[i]) && sentence.sentence.contains(talkingVerbs[j]))
                {
                    if (sentence.sentence.indexOf(structure[i]) < sentence.sentence.indexOf(separators[k]) // Если конструкция TalkingToYourself находится в левой части двусоставного предложения (до союза или знака препинания)
                            && sentence.sentence.indexOf(talkingVerbs[j]) < sentence.sentence.indexOf(separators[k])
                            && !(sentence.sentence.indexOf("that") < sentence.sentence.indexOf(separators[k])))
                        return true;
                    else if (sentence.sentence.indexOf(structure[i]) > sentence.sentence.indexOf(separators[k]) // Если конструкция TalkingToYourself находится в правой части двусоставного предложения (после союза или знака препинания) или предложение односоставное
                            && sentence.sentence.indexOf(structure[j]) > sentence.sentence.indexOf(separators[k])
                            && !(sentence.sentence.indexOf("that") > sentence.sentence.indexOf(separators[k])))
                        return true;
                }
            }

    return false;
}

/*!
Проверка на наличие в предложении мыслей героев
\param sentence[in] - предложение и необходимая информация о нем
\return - проходит ли предложение по этому правилу (true/false)
*/
bool Rules::Thoughts(Sentence &sentence)
{
    QList <QString> structure = {
        "remember",
        "remembered",
        "was remembering",
        "were remembering",
        "think",
        "thought",
        "was thinking",
        "were thinking"
    };

    QList <QString> separators = {
        ",",
        ";",
        "and",
        "or",
        "but",
        "so"
    };

    for (int i = 0; i < structure.size(); i++)
        for (int j = 0; j < separators.size(); j++)
        {
            if (sentence.sentence.indexOf(structure[i]) < sentence.sentence.indexOf(separators[j]) // Если конструкция Thoughts находится в левой части двусоставного предложения (до союза или знака препинания)
                    && !(sentence.sentence.indexOf("that") < sentence.sentence.indexOf(separators[j])))
                return true;
            else if (sentence.sentence.indexOf(structure[i]) > sentence.sentence.indexOf(separators[j]) // Если конструкция Thoughts находится в правой части двусоставного предложения (после союза или знака препинания) или предложение односоставное
                    && !(sentence.sentence.indexOf("that") > sentence.sentence.indexOf(separators[j])))
                return true;
        }

    return false;
}

/*!
Проверка на наличие в предложении смены лица повествования
\param sentence[in] - предложение и необходимая информация о нем
\return - проходит ли предложение по этому правилу (true/false)
*/
bool Rules::ChangePersonNarrative(Sentence &sentence)
{
    if(textPerson == "first")
    {
        if(sentence.getPerson() == sentence.second)
            return true;
    }
    else if (textPerson == "third")
    {
        if(sentence.getPerson() == sentence.first || sentence.getPerson() == sentence.second)
            return true;
    }
    else
        return false;
}
