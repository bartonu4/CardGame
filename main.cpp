#include <iostream>

using namespace std;
#include "mcts.h"
int main()
{
    mcts *bot = new mcts;
    int iter=0, resBot =0, resPlayer =0, eql = 0, oldBot = 0 , oldPlayer = 0, tempDeck = 0;
    List<int> cardPlayerList;
    bool wrong = false;
    for(int i = 1; i <= CARD_TO_PLAY; i++)
    {
        cardPlayerList.append(i);
    }
    while(iter<CARD_TO_PLAY)
    {
        iter++;
        //    if(iter==CARD_TO_PLAY)
        //    {
        //        cout<<endl<<endl<<endl<<"Result player: "<<resPlayer<<"\t Result bot: "<<resBot;
        //        break;
        //    }
        int cardDeck = 0, cardPlayer = 0, cardBot = 0, rand = 0;
        if(!wrong)
        {
            rand =  bot->random_gen->getNormal(bot->cardInDeck.size()-1);
            cardDeck = bot->cardInDeck.erase(rand);
        }
        else
        {
            cardDeck = tempDeck;
        }
        cout<<endl<<endl<<endl<<"Result player: "<<resPlayer<<"\t Result bot: "<<resBot<<"\n\nDeck card  =   "<<cardDeck<<endl;
        cout << "Your card: \n";
        for(int i = 0; i < cardPlayerList.size(); i++)
        {
            cout << " " << cardPlayerList.at(i);
        }

        cout << "\n Enter your card \n";
        cin >> cardPlayer;

        int indCard;
        if((indCard = cardPlayerList.indexOf(cardPlayer)) == -1)
        {
            iter--;
            wrong = true;
            tempDeck = cardDeck;
            continue;
        }
        wrong = false;
        cardPlayerList.erase(indCard);
        cin.clear();

        if (iter == 1)
        {
            cardBot = bot->choose(cardDeck,0,0);
        }
        else
        {
            cardBot  = bot->choose(cardDeck,oldBot,oldPlayer);
        }

        if(cardBot>cardPlayer)
        {
            resBot += cardDeck + eql;
            eql  = 0;
        }
        else if (cardPlayer>cardBot)
        {
            resPlayer  += cardDeck + eql ;
            eql = 0;
        }
        else
        {
            eql+= cardDeck;
        }
        bot->setResult(resBot,resPlayer,eql);
        cout<<"Bot card = "<<cardBot<<endl;

        oldPlayer = cardBot;
        oldBot = cardPlayer;
    }

    cout <<endl ;
}

