#include "rules.h"
#include "sentence.h"

class checkRulesTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!firstStrangeTest())
            errorList.append("Error in test: firstStrangeTest\n");
        if (!secondStrangeTest())
            errorList.append("Error in test: secondStrangeTest\n");
    }

    bool firstStrangeTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "The old lady pulled her spectacles down and looked over them about the room; then she put them up and looked out under them.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return rules.checkRules(sentence) == false;
    }

    bool secondStrangeTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "She seldom or never looked through them for so small a thing as a boy; they were her state pair, the pride of her heart, and were built for \"style\", not service—she could have seen through a pair of stove-lids just as well.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return rules.checkRules(sentence) == false;
    }
};

class getTenseTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!singlePartSentenceTest())
            errorList.append("Error in test: singlePartSentenceTest\n");
        if (!pastTenseSentenceTest())
            errorList.append("Error in test: pastTenseSentenceTest\n");
        if (!presentTensetSentenceTest())
            errorList.append("Error in test: presentTensetSentenceTest\n");
        if (!futureTenseSentenceTest())
            errorList.append("Error in test: futureTenseSentenceTest\n");
        if (!compoundSentenceTest())
            errorList.append("Error in test: compoundSentenceTest\n");
    }

    bool singlePartSentenceTest()
    {
        Sentence sentence;
        sentence.sentence = "Funny?";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getTense() == sentence.present;
    }

    bool pastTenseSentenceTest()
    {
        Sentence sentence;
        sentence.sentence = "I could hide in the vaults amongst the books.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getTense() == sentence.past;
    }

    bool presentTensetSentenceTest()
    {
        Sentence sentence;
        sentence.sentence = "We are the heroes.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getTense() == sentence.present;
    }

    bool futureTenseSentenceTest()
    {
        Sentence sentence;
        sentence.sentence = "I will give up my life if need be, give up my honor, give up all my dreams, but I will find her.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getTense() == sentence.future;
    }

    bool compoundSentenceTest()
    {
        Sentence sentence;
        sentence.sentence = "Everyone was busy, so I went to the movie alone.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getTense() == sentence.past;
    }
};

class getPersonTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!firstPersonNarrativeTest())
            errorList.append("Error in test: firstPersonNarrativeTest\n");
        if (!secondPersonNarrativeTest())
            errorList.append("Error in test: secondPersonNarrativeTest\n");
        if (!thirdPersonNarrativeTest())
            errorList.append("Error in test: thirdPersonNarrativeTest\n");
        if (!NNPNarrativeTest())
            errorList.append("Error in test: NNPNarrativeTest\n");
        if (!ImpersonalNarrativeTest())
            errorList.append("Error in test: ImpersonalNarrativeTest\n");
    }

    bool firstPersonNarrativeTest()
    {
        Sentence sentence;
        sentence.sentence = "I could hide in the vaults amongst the books.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getPerson() == sentence.first;
    }

    bool secondPersonNarrativeTest()
    {
        Sentence sentence;
        sentence.sentence = "Would you like that, Father?";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getPerson() == sentence.second;
    }

    bool thirdPersonNarrativeTest()
    {
        Sentence sentence;
        sentence.sentence = "He will never stop looking.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getPerson() == sentence.third;
    }

    bool NNPNarrativeTest()
    {
        Sentence sentence;
        sentence.sentence = "Pete loved her.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getPerson() == sentence.third;
    }

    bool ImpersonalNarrativeTest()
    {
        Sentence sentence;
        sentence.sentence = "Impossible.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        return sentence.getPerson() == sentence.first;
    }
};

class RhetoricalQuestionTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!RhetoricalQuestionFirstTest())
            errorList.append("Error in test: RhetoricalQuestionFirstTest\n");
        if (!RhetoricalQuestionSecondTest())
            errorList.append("Error in test: RhetoricalQuestionSecondTest\n");
        if (!RhetoricalQuestionThirdTest())
            errorList.append("Error in test: RhetoricalQuestionThirdTest\n");
        if (!RhetoricalQuestionFourthTest())
            errorList.append("Error in test: RhetoricalQuestionFourthTest\n");
    }

    bool RhetoricalQuestionFirstTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "When the battle was done, there were changes made.";

        return rules.RhetoricalQuestion(sentence) == false;
    }

    bool RhetoricalQuestionSecondTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "Am I still a thief if I put it all back and no one ever knows?";

        return rules.RhetoricalQuestion(sentence) == true;
    }

    bool RhetoricalQuestionThirdTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "Was that some ploy?";

        return rules.RhetoricalQuestion(sentence) == true;
    }

    bool RhetoricalQuestionFourthTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "Would you like that, Father?";

        return rules.RhetoricalQuestion(sentence) == true;
    }
};

class ExclamotarySentenceTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!ExclamotarySentenceFirstTest())
            errorList.append("Error in test: ExclamotarySentenceFirstTest\n");
        if (!ExclamotarySentenceSecondTest())
            errorList.append("Error in test: ExclamotarySentenceSecondTest\n");
        if (!ExclamotarySentenceThirdTest())
            errorList.append("Error in test: ExclamotarySentenceThirdTest\n");
        if (!ExclamotarySentenceFourthTest())
            errorList.append("Error in test: ExclamotarySentenceFourthTest\n");
    }

    bool ExclamotarySentenceFirstTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "When the battle was done, there were changes made.";

        return rules.ExclamotarySentence(sentence) == false;
    }

    bool ExclamotarySentenceSecondTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "Jeezly-crow!";

        return rules.ExclamotarySentence(sentence) == true;
    }

    bool ExclamotarySentenceThirdTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "Georgie’s scared of the dark!";

        return rules.ExclamotarySentence(sentence) == true;
    }

    bool ExclamotarySentenceFourthTest()
    {
        Sentence sentence;
        Rules rules;
        sentence.sentence = "What a baby!";

        return rules.ExclamotarySentence(sentence) == true;
    }
};

class ChangeNarrativeTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!NoChangingNarrativeTest())
            errorList.append("Error in test: NoChangingNarrativeTest\n");
        if (!PresentToPastChangingTest())
            errorList.append("Error in test: PresentToPastChangingTest\n");
        if (!PastToPresentChangingTest())
            errorList.append("Error in test: PastToPresentChangingTest\n");
        if (!PastToFutureChangingTest())
            errorList.append("Error in test: PastToFutureChangingTest\n");
    }

    bool NoChangingNarrativeTest()
    {
        Sentence sentence;
        sentence.sentence = "When the battle was done, there were changes made.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textTense = "past";

        return rules.ChangeNarrative(sentence) == false;
    }

    bool PresentToPastChangingTest()
    {
        Sentence sentence;
        sentence.sentence = "I saw my future in a drop of blood.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textTense = "present";

        return rules.ChangeNarrative(sentence) == true;
    }

    bool PastToPresentChangingTest()
    {
        Sentence sentence;
        sentence.sentence = "Am I still a thief if I put it all back and no one ever knows?";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textTense = "past";

        return rules.ChangeNarrative(sentence) == true;
    }

    bool PastToFutureChangingTest()
    {
        Sentence sentence;
        sentence.sentence = "I will never stop looking. I will give up my life if need be, give up my honor, give up all my dreams, but I will find her.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textTense = "past";

        return rules.ChangeNarrative(sentence) == true;
    }
};

class TalkingToYourselfTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!NoTalkingToYourselfTest())
            errorList.append("Error in test: NoTalkingToYourselfTest\n");
        if (!TalkingToYourselfFirstTest())
            errorList.append("Error in test: TalkingToYourselfFirstTest\n");
    }

    bool NoTalkingToYourselfTest()
    {
        Sentence sentence;
        sentence.sentence = "He told himself that it was the worst day in his live.";

        Rules rules;

        return rules.TalkingToYourself(sentence) == false;
    }

    bool TalkingToYourselfFirstTest()
    {
        Sentence sentence;
        sentence.sentence = "That would be enough, he told himself, so long as I had Rosey.";

        Rules rules;

        return rules.TalkingToYourself(sentence) == true;
    }
};

class ThoughtsTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!NoThoughtsTest())
            errorList.append("Error in test: NoThoughtsTest\n");
        if (!ThoughtsFirstTest())
            errorList.append("Error in test: ThoughtsFirstTest\n");
        if (!ThoughtsSecondTest())
            errorList.append("Error in test: ThoughtsSecondTest\n");
    }

    bool NoThoughtsTest()
    {
        Sentence sentence;
        sentence.sentence = "Alice thought that it was her destiny.";

        Rules rules;

        return rules.Thoughts(sentence) == false;
    }

    bool ThoughtsFirstTest()
    {
        Sentence sentence;
        sentence.sentence = "Gold for iron, Pate remembered, you won’t do better.";

        Rules rules;

        return rules.Thoughts(sentence) == true;
    }

    bool ThoughtsSecondTest()
    {
        Sentence sentence;
        sentence.sentence = "If I hit him in the mouth with my tankard, I could knock out half his teeth, Pate thought.";

        Rules rules;

        return rules.Thoughts(sentence) == true;
    }
};

class ChangePersonNarrativeTest
{
public:
    void startTest(QList <QString> &errorList)
    {
        if (!NoChangingPersonNarrativeTest())
            errorList.append("Error in test: NoChangingPersonNarrativeTest\n");
        if (!FirstToSecondChangingTest())
            errorList.append("Error in test: FirstToSecondChangingTest\n");
        if (!ThirdToFirstChangingTest())
            errorList.append("Error in test: ThirdToFirstChangingTest\n");
        if (!ThirdToSecondChangingTest())
            errorList.append("Error in test: ThirdToSecondChangingTest\n");
    }

    bool NoChangingPersonNarrativeTest()
    {
        Sentence sentence;
        sentence.sentence = "When the battle was done, there were changes made.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textPerson = "first";

        return rules.ChangePersonNarrative(sentence) == false;
    }

    bool FirstToSecondChangingTest()
    {
        Sentence sentence;
        sentence.sentence = "Then you would be the kinslayer, not him.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textPerson = "first";

        return rules.ChangePersonNarrative(sentence) == true;
    }

    bool ThirdToFirstChangingTest()
    {
        Sentence sentence;
        sentence.sentence = "I laughed in her face, but she had powers.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textPerson = "third";

        return rules.ChangePersonNarrative(sentence) == true;
    }

    bool ThirdToSecondChangingTest()
    {
        Sentence sentence;
        sentence.sentence = "You will need me to teach him how to rule and keep him safe from his enemies.";
        sentence.loadTextToFile();
        sentence.getInfoFromStanford();
        sentence.loadInfoToMemory();

        Rules rules;
        rules.textPerson = "third";

        return rules.ChangePersonNarrative(sentence) == true;
    }
};

class Test
{
public:
    QList <QString> errorList;

    void RunAllTest()
    {
        checkRulesTest test0;
        getTenseTest test1;
        getPersonTest test2;
        RhetoricalQuestionTest test3;
        ExclamotarySentenceTest test4;
        ChangeNarrativeTest test5;
        TalkingToYourselfTest test6;
        ThoughtsTest test7;
        ChangeNarrativeTest test8;

        test0.startTest(errorList);
        test1.startTest(errorList);
        test2.startTest(errorList);
        test3.startTest(errorList);
        test4.startTest(errorList);
        test5.startTest(errorList);
        test6.startTest(errorList);
        test7.startTest(errorList);
        test8.startTest(errorList);
    }

    void AnalyzeResult()
    {
        QTextStream out(stdout);
        out << "\n***********************\n";
        if (!errorList.isEmpty())
        {
            out << "There are " << errorList.size() << " wrong tests\n";
            for (int i = 0; i < errorList.size(); i++)
            {

                out << errorList[i];
            }
        }
        else
            out << "All tests are correct.\n";
        out << "***********************\n";
    }

};
