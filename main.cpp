#include <iostream>

using namespace std;
#include "mcts.h"
int main()
{
   mcts *bot = new mcts;
   int iter=0, resBot =0, resPlayer =0, eql = 0, oldBot = 0 , oldPlayer = 0;
while(iter<CARD_TO_PLAY)
{
    iter++;
//    if(iter==CARD_TO_PLAY)
//    {
//        cout<<endl<<endl<<endl<<"Result player: "<<resPlayer<<"\t Result bot: "<<resBot;
//        break;
//    }
   int cardDeck = 0, cardPlayer = 0, cardBot = 0, rand = 0;

   rand =  bot->random_gen->getNormal(bot->cardInDeck.size()-1);
   cardDeck = bot->cardInDeck.erase(rand);
   cout<<endl<<endl<<endl<<"Result player: "<<resPlayer<<"\t Result bot: "<<resBot<<"\n\nDeck card  =   "<<cardDeck<<endl;

   cout<<"Enter your card \n";
   cin>>cardPlayer;
   cin.clear();

   if (iter==1)
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

