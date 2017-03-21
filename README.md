# Tactical-AI 
Author: Pau Bonet Vall Llebrera

## Introduction
The first videogames where simply logic games without AI, but as the years passed more features were added in the videogames world such as stored patterns in games like Speed Race(1974), and when the microprocessor was added random elements where also added into videogames. Around the 80's games like Space Invaders and Pac-Man started to have functionabilities that would depend on the players' input

The true beggining of the AI started with the real-time strategy games such as Dune II, that used finite state machines that took in account real-time decisions pathfinding and game economic decisions.

Nowadays AI is used in videogames mostly for pathfinding and combat. Mixing different methods like [Bottom-Up AI Methods](https://en.wikipedia.org/wiki/Top-down_and_bottom-up_design) and the ones mentioned before.

## Tactical AI elements

1. **Visibility**: this element is related with the area of influence of an AI, every entity with AI will need an area of influence and an activation area(don't have to be different necessarly), for example an assassin could see a unit at 10 tiles of distance, but the other unit won't realize of his existance until the assassin is 3 tiles near him. 

![Example of Visibility Area](http://imgur.com/S1Qumbc.png)

When coding the best way to use this elemnt would be having to properties one for the influence area(how other entities react to this entity) and another one for the activation area(how this entity reacts to other entities).


2. **Interaction Position** : once a unit is alerted to interact with another it needs to have a clear tile to start interacting with the other unit, we have to decide how units will be placed around other's to interact with it.

> 2.1. Range and Melee: the interaction position will directly depend on the unit characteristic, if an enemy is trying to attack a unit his interaction position will be more far if it has a range attack than the enemy with a melee attack. That's why we have to take care about this 2 properties when setting the interaction position.

> 2.2. Unreachable Areas: What if our enemy wants to reach a unit that is in the top of a locked tower, this enemy will constantly try to find a free tile closer to the unit, but if this unit doesn't move why do we keep trying to achieve it?
An optimal solution would be to stay in an "alert" state, it would be middle point between the wander state and the attack state, we don't need to waste resources in pathfinding a new tile every time we are in range, we should call a state that will wait until the unit moves to a reachable position.

> 2.3. Multi Unit Positioning: What happens if we have other enemies in all the positions that are in range of the unit that we want to attack. Let's take a look to this image:

![](http://imgur.com/g9hq3lH.png)

The problem here would be that there are tiles that are already used by other entities, that's where pathfinding comes in, and looks for an empty walkable tile. What if our target is completely surrounded of entites, we have to use a kind of "onion ring" of entites and wait until there is a tile to attack.

## How to Implenet an AI into a 2D game

1. **Action and Reaction:** In order to make a succesful AI for a game we have to consider how many this AI will be, to do that we need to know what our main character is able to do that will affect directly the NPCs, so if our main character is just able to deal damage with melee attacks our NPCs won't be affected by the "ATTACK" action of our player, let's see how this would simply be managed in our source code in a simple way.

For example, in the next image we will see a Mario Scene with some enemies around, (without taking in account the real game functionalities) our enemy could change his behaviour depending on the actual Power-Up that Marios has, if this enemy is inside Mario's range he will try to attack him in order to survive.

![](http://imgur.com/QdFk8ct.jpg)

That's why knowing what our NPC's and our main character skills it's so important, we have to know how do they interact with each other to start building connections between them.

![Most Simple AI](http://imgur.com/L3Lxvtg.png)

2. **Define the States** :Once we know how the entities of the game interact with each other, we have to make a list with the states of each entity and how other entities will make these states change.

Entity 1:
> 1. Wander: if we don't have an enemy near we will keep a wander state, it could be walking with a pattern or staying in the same place until some other state is activate it.
> 2. Attack: if we have an enemy in our range we will attack them
> 3. Evade: this state will be activate it if and enemy attack it's coming and we are not currently attacking.
> 4. Find Aid: this state will be activate it if we are low on HP.

3. **Use a Finite-State Machine** :If you are new in creating AI, state machines are a tool that will agilize and simplify that task, an Entity AI could be simplified into for example 4 states: wander, attack, evade, and find aid.

![FSM](http://imgur.com/OgHWyD8.png)

Translated to our code, the 4 states would be 4 functions that will be executed depending on the transition conditions, this transitions are the arrows that connect them, and in our code it will be statements (normally controlled also by functions).

How to use them in our game code, having a FSM(finite state machine) will let us to only call the correct function in every game Update(), and call the transition function in the PreUpdate(), the idea is that this transition function should give us information about which state function the FSM will use in the following frame. 

4. **Implement a Finite-State Machine** : To begin with the implementation we should make a FSM class that will manage the states, so we will need one variable to store the current state (curr_state) and a function to modify it.

![](http://imgur.com/ePZT3nE.png)

5. **Implement the NPC brain** : If we want the AI work properly our entities need to send to the FSM their current state, so we will have a FSM() function inside all the entities that will need AI. 
## Download the Exercise
### Before Start
To make the exercise open the handout and complete the TODOs that are commented, if you need help there is a Solution folder.
Any doubt or improvement contact me : paubv1997@gmail.com
[Download the .RAR](https://github.com/BooLAW/Tactical-AI/releases)



## Interesting Links:

[State Machines Article](https://gamedevelopment.tutsplus.com/tutorials/finite-state-machines-theory-and-implementation--gamedev-11867)

[Demo of a GOAP AI System](https://gamedevelopment.tutsplus.com/tutorials/goal-oriented-action-planning-for-a-smarter-ai--cms-20793)

[Article that talks about State Machines](https://www.gamedev.net/resources/_/technical/artificial-intelligence/a-practical-guide-to-building-a-complete-game-a-r784)

[Advanced Article for Strategical and Tactical AI](http://www.cse.scu.edu/~tschwarz/COEN129/PPT/Tactical%20and%20Strategical%20AI.pdf)

