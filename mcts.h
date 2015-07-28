#ifndef MCTS_H
#define MCTS_H
#include "node.h"
#include <random>
#include <iostream>
#define CARD_TO_PLAY 10
class Random_Generator;
class mcts
{
    DeckNode *root;
    int numOfCards, botResult, playerResult,equal,flippedCard,winscore;

    BotNode * next;

public:
    mcts();
    int choose(int cardDeck, int cardBot, int cardPlayer);
    PlayerNode * selectNode(DeckNode* node );
    PlayerNode *simulation(DeckNode *node);
    void expandDeck(DeckNode *node, int num);
    void expandPlayer(PlayerNode *node, int num);
    void expandBot(BotNode *node, int num);
    void move(PlayerNode *playerNode, int botRes, int playerRes, int eq);
    void updateBot(bool win, BotNode *node);
    void updateDeck(bool win, DeckNode *node);
    void updatePlayer(bool win, PlayerNode *node);
    void setRoot(int cardDeck, int cardBot, int cardPlayer);
    void setResult(int plRes, int bRes, int eq);
    Random_Generator *random_gen;
     lshort cardInDeck,cardInPlayer,cardInBot;
};



class Random_Generator
{

    std::random_device rd;

        std::mt19937 gen;
public:
        Random_Generator()
        {
            gen.seed(rd());
        }
        int getRandomPoisson(int max, lshort card){
            if(max>10){
                max = 10;
            }
            std::poisson_distribution<int> dis((double)(max + 0.000001));
            //dis.reset();
            int result = dis(gen);
//            while(!cards.contains(result))
//            {
//                result=dis(gen);
//            }

//            return cards.indexOf(result);
            return result;
        }
        int getNormal(int max){
            std::uniform_int_distribution<int> dis(0,max);
            int result = dis(gen);
            return result;
        }
};
#endif // MCTS_H
