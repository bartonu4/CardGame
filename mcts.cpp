#include "mcts.h"

mcts::mcts()
{
    root = NULL;
    for(int i=1;i<=CARD_TO_PLAY;i++)
    {
        cardInBot.append(i);
        cardInDeck.append(i);
        cardInPlayer.append(i);
    }
    playerResult = 0;
    botResult = 0;

    double Sn = (double)(((double)(CARD_TO_PLAY+1)/2)*CARD_TO_PLAY);
    winscore = Sn/2+1;
    equal = 0;
    random_gen = new Random_Generator();
}
PlayerNode *mcts::selectNode(DeckNode *node)
{
    expandDeck(node,cardInDeck.size()+1);
    return  simulation(node);

}

PlayerNode * mcts::simulation(DeckNode * node)
{
    int numOfSimulation = 5000;
    double wins=0;
    int index=0;
    if(node->childPlayers.size()<7)
    {
        numOfSimulation = (10-node->childPlayers.size())* numOfSimulation;
        std::cout<<" Num of simulations: "<<numOfSimulation<<'\n';
    }
    for(int i = 0;i<node->childPlayers.size();i++)
    {

        for(int j=0;j<numOfSimulation;j++)
        {

            move(node->childPlayers.at(i), botResult,playerResult, equal);


        }
        double local_winrate =(double) ((double)  node->childPlayers.at(i)->win)/
                ((double)node->childPlayers.at(i)->visited);
        if(wins<local_winrate)
        {
            wins  = local_winrate;
            index = i;

        }
        std::cout<<"CARD "<<node->childPlayers.at(i)->player<<"; Winrate "<<local_winrate<<std::endl;
    }
    return node->childPlayers.at(index);

}

void mcts::move(PlayerNode *playerNode,int botRes,int playerRes,int eq)
{
    BotNode *botNode;
    DeckNode *deckNode ;
    PlayerNode *plNode;
    lshort simCardInDeck = cardInDeck;
    lshort simCardInBot= cardInBot;
    lshort simCardInPlayer = cardInPlayer;
    int equal=eq;
    int deckcard =flippedCard;
    plNode=playerNode;
    int playercard = simCardInPlayer.erase( simCardInPlayer.indexOf(playerNode->getPlayer()));
    while(1)
    {
        int rand = random_gen->getNormal(simCardInBot.size()-1);
        int botcard = simCardInBot.erase(rand);
        botNode = plNode->checkChild(botcard);

        if(playercard>botcard)
        {
            playerRes += deckcard+equal;
            equal = 0;
        }
        else if(playercard<botcard)
        {
            botRes+=deckcard+equal;
            equal = 0;
        }
        else
        {
            equal+=deckcard;
        }

        if(playerRes>=winscore)
        {
            updateBot(true,botNode);
            break;
        }
        else if(botRes>=winscore)
        {
            updateBot(false,botNode);
            break;
        }
        if(simCardInBot.size()==0)
        {
            if(playerRes>botRes)
            {
                updateBot(true,botNode);
            }
            else
            {
                updateBot(false,botNode);
            }
            break;
        }

        rand = random_gen->getNormal(simCardInDeck.size()-1);
        deckcard = simCardInDeck.erase(rand);
        deckNode = botNode->checkChild(deckcard);

        rand = random_gen->getNormal(simCardInPlayer.size()-1);
        playercard = simCardInPlayer.erase(rand);
        plNode = deckNode->checkChild(playercard);

    }
}

void mcts::updateDeck(bool win, DeckNode *node)
{
    node->update(win);
    if(node!=root)
    {
        updateBot(win, node->getFather());
    }
}

void mcts::updatePlayer(bool win, PlayerNode *node)
{
    node->update(win);
    updateDeck(win, node->getFather());
}

void mcts::setRoot(int cardDeck, int cardBot, int cardPlayer )
{
    if(root==NULL)
    {
        root = new DeckNode(NULL,cardDeck);
    }
    else
    {
        root = root->checkChild(cardPlayer)->checkChild(cardBot)->checkChild(cardDeck);
        cardInBot.erase(cardInBot.indexOf(cardBot ));
        cardInPlayer.erase(cardInPlayer.indexOf(cardPlayer));
    }
}

void mcts::setResult(int plRes, int bRes, int eq)
{
    playerResult = plRes;
    botResult = bRes;
    equal  = eq;

}

void mcts::updateBot(bool win, BotNode *node)
{
    node->update(win);

    if(node->getFather()!=NULL)
    {
        updatePlayer(win, node->getFather());
    }


}
void mcts::expandPlayer(PlayerNode *node, int num)
{
    if(node->childBots.size()<num)
    {

        for(int i=0;i<num;i++)
        {

            bool exist = true;

            for(int j = 0;j<node->childBots.size();j++)
            {

                if(node->childBots.at(j)->getBot()==cardInBot.at(i))
                {
                    exist = false;
                }

            }

            if(exist==true)
            {
                node->childBots.append(new BotNode(node,cardInBot.at(i)));
            }



        }

    }
}

void mcts::expandBot(BotNode *node, int num)
{
    if(node->childDecks.size()<num)
    {

        for(int i=0;i<num;i++)
        {

            bool exist = true;

            for(int j = 0;j < node->childDecks.size();j++)
            {

                if(node->childDecks.at(j)->getDeck()==cardInDeck.at(i))
                {
                    exist = false;
                }

            }

            if(exist==true)
            {
                node->childDecks.append(new DeckNode(node,cardInDeck.at(i)));
            }



        }

    }
}


void mcts::expandDeck(DeckNode *node, int num)
{

    if(node->childPlayers.size()<num)
    {

        for(int i=0;i<num;i++)
        {
            bool exist = true;

            for(int j = 0;j<node->childPlayers.size();j++)
            {

                if(node->childPlayers.at(j)->getPlayer()==cardInPlayer.at(i))
                {
                    exist = false;
                }

            }

            if(exist==true)
            {
                node->childPlayers.append(new PlayerNode(node,cardInPlayer.at(i)));
            }



        }

    }
}





int mcts::choose(int cardDeck,int cardBot, int cardPlayer)
{
    flippedCard = cardDeck;
    setRoot(cardDeck,cardBot,cardPlayer);
    PlayerNode * res;
    res = selectNode(root);
    return res->player;
}


