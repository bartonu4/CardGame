#include "node.h"

void PlayerNode::initialize()
{

}
DeckNode *PlayerNode::getFather() const
{
    return father;
}

void PlayerNode::setFather(DeckNode *value)
{
    father = value;
}

BotNode *PlayerNode::checkChild(int rand)
{
    BotNode * botNode;
    bool check = false;
    if(this->childBots.size()>0)
    {

        for(int i=0;i<childBots.size();i++)
        {
            if(this->childBots.at(i)->bot==rand)
            {
                botNode = this->childBots.at(i);
                check = true;
            }
        }
        if(!check)
        {
            botNode = new BotNode(this,rand);
            this->childBots.append(botNode);

        }
    }
    else
    {
        botNode = new BotNode(this,rand);
        this->childBots.append(botNode);
    }
    return botNode;
}


PlayerNode::PlayerNode(DeckNode *parent, int card)
{
    father = parent;
    player =card;
}
short PlayerNode::getPlayer() const
{
    return player;
}

void PlayerNode::setPlayer(short value)
{
    player = value;
}


BotNode *DeckNode::getFather() const
{
    return father;
}

void DeckNode::setFather(BotNode *value)
{
    father = value;
}
void DeckNode::initialize()
{

}

DeckNode::DeckNode()
{

}

DeckNode::DeckNode(BotNode *parent, int card){
    father = parent;
    deck = card;
}
short DeckNode::getDeck() const
{
    return deck;
}

void DeckNode::setDeck(short value)
{
    deck = value;
}

PlayerNode *DeckNode::checkChild(int rand)
{
    PlayerNode * playerNode;
    bool check = false;
    if(this->childPlayers.size()>0)
    {

        for(int i=0;i<this->childPlayers.size();i++)
        {
            if(this->childPlayers.at(i)->player==rand)
            {
                playerNode = this->childPlayers.at(i);
                check = true;
            }
        }
        if(!check)
        {
            playerNode = new PlayerNode(this,rand);
            this->childPlayers.append(playerNode);

        }
    }
    else
    {
        playerNode = new PlayerNode(this,rand);
        this->childPlayers.append(playerNode);
    }
    return playerNode;
}



void BotNode::initialize()
{

}
PlayerNode *BotNode::getFather() const
{
    return father;
}

void BotNode::setFather(PlayerNode *value)
{
    father = value;
}


BotNode::BotNode(PlayerNode *parent, int card)
{
    father = parent;
    bot = card;
}
short BotNode::getBot() const
{
    return bot;
}

void BotNode::setBot(short value)
{
    bot = value;
}

DeckNode *BotNode::checkChild(int rand)
{
    DeckNode * deckNode;
    bool check = false;
    if(this->childDecks.size()>0)
    {

        for(int i=0;i<childDecks.size();i++)
        {
            if(this->childDecks.at(i)->deck==rand)
            {
                deckNode = this->childDecks.at(i);
                check = true;
            }
        }
        if(!check)
        {
            deckNode = new DeckNode(this,rand);
            this->childDecks.append(deckNode);

        }
    }
    else
    {
        deckNode = new DeckNode(this,rand);
        this->childDecks.append(deckNode);
    }
    return deckNode;
}

