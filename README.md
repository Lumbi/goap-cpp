# GOAPY SLIMES!

A hobby project to try implementing [GOAP](http://alumni.media.mit.edu/~jorkin/goap.html).

<img width="512" alt="image" src="https://user-images.githubusercontent.com/1648852/222326840-e0bcf5bb-b057-477f-a1bf-e7f0a7409a2f.png">

## Slime feasting frenzy!!

&nbsp;

<img width="320" alt="slimes bouncing around" src="https://user-images.githubusercontent.com/1648852/222493104-51c906ad-a95b-4729-bfca-a32cb1d2c1dd.gif">

&nbsp;

Each slime has has some AI which uses GOAP to find it's way in life.

Actions:
- Seek food (walk around randomly)
- Sleep (wait for food to appear)
- Power up (become BIG!)

Goal:
- Get BIG!

&nbsp;

<img width="128" alt="a big slime" src="https://user-images.githubusercontent.com/1648852/222328697-673b6626-8609-4683-9f46-69000b26c608.png">

&nbsp;

The strategy is pretty simple: when there's food, walk around to find it, otherwise sleep, and power up when *satiated* (full with food).

Every update (it should be throttled...), the slime reads the world state and runs GOAP on the action graph to decide the next action to take.

The world spawns food at random every now and then. You can also click to spawn food at a location.

## Boring implementation details

I used Dijkstra instead of A* because didn't have any heuristic function. The path-finding implementation is also embarrassingly generic just because I felt like it.

Check out `ActionGraph.cpp` and `PathFinding.cpp`, that's where most of the juicy stuff is.

Using [SFML](https://www.sfml-dev.org/index.php) for graphics, etc.

NOTE: Very much NOT optimized code

## Assets

- https://frozentaurus.itch.io/food-assets
- https://stealthix.itch.io/animated-slimes
