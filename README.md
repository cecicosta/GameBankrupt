# README #

### What is in this repository? ###

Consider the following hypothetical game, which we will call Bankrupt, very similar to Monopoly where several of its mechanics have been simplified. In a match of that game, the players change in rounds, in an order randomly defined at the beginning of the game. Players always start a match with 300 coins each. In this game, the board consists of 20 properties in sequence. Each house has a cost of sale, a rental value, a owner if they are already purchased, and follow a certain order on the board. In Bankrupt, it is not possible to build hotels and no other improvements on the properties of the board, for simplicity of the problem. The sales and rental value of all 20 properties are configured in a file named gameConfig.txt, which the program reads and interpretate.
The repository implements the above game logics and simulates a match beetwen random players, each one with a different strategy, as following:

* The impulsive player buys any property on which he stops.
* The demanding player buys any property, as long as the rent is
which 50 coins.
* The cautious player buys any property as long as he has a
80 coins left after purchase.
* The random player buys the property that he stops with probability of
50%.

## Rules ##
* When falling into an unowned property, the player can choose whether or not to buy
property. This is the only way a property can be purchased.
* When you fall into a property that you own, you must pay the owner the rent
property.
* Upon completing a round on the board, the player earns 100 coins.

This project is writen with C++ and uses some features from C++11, which is needed to compile.
