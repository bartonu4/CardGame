#ifndef NODE_H
#define NODE_H
#include "list.h"
typedef  List<short> lshort;
class Node{

    unsigned short resultPlayer, resultBot;
    virtual void initialize()=0;


public:
     unsigned int visited,win ;
    Node(){
        resultBot = 0;
        resultPlayer = 0;
        visited  = 0;
        win = 0;
    }
    void update(bool win)
    {
        this->visited++;
        if(win)
        {
            this->win++;
        }
    }

};

class PlayerNode;
class BotNode;

class DeckNode: public Node
{
    BotNode *father;
    void initialize();
public :
    DeckNode();
    DeckNode(BotNode * parent, int card);
    //lshort deckCards;
    int deck;
    List<PlayerNode*> childPlayers;

    short getDeck() const;
    void setDeck(short value);
    PlayerNode * checkChild(int rand);
    BotNode *getFather() const;
    void setFather(BotNode *value);
};


class PlayerNode: public Node
{
    void initialize();
    DeckNode *father;
public:
    PlayerNode(DeckNode * parent, int card);
    //lshort playerCards;
    int player;
    List<BotNode*> childBots;
    short getPlayer() const;
    void setPlayer(short value);
    DeckNode *getFather() const;
    void setFather(DeckNode *value);
    BotNode * checkChild(int rand);
};


class BotNode: public Node
{
    void initialize();
    PlayerNode * father;
public :
    BotNode(PlayerNode * parent, int card);
    // lshort botCards;
    List<DeckNode*> childDecks;
    short bot;

    short getBot() const;
    void setBot(short value);
    DeckNode *checkChild(int rand);
    PlayerNode *getFather() const;
    void setFather(PlayerNode *value);
};
#endif // NODE_H
