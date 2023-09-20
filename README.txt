Welcome to my Zork project!

For this version of the zork game I have implemented a parser that allows the user to  define custom maps and modify them given some constrains indicated in the exemple.txt file. The parser reads and places entities (room, creatures, player, item) into the world and connects rooms with exits too.
During the dessign I had some ideas to accelerate the process of coding thanks to a book I read "Game Programming Patterns by Robert Nystrom" and I wanted to implement the command class which stores pointers to funcions and had a trigger public function that allows the stored function to be called. This would have facilitated the process of reading the input actions as the world could have a map of <string, command> that would get the command given a string and execute it. But when implementing it I had problems with the arguments and declarations and descarted the idea and moved into a simpler if{} else if {} parse for user input.
My game version contains the basic mecanics of moving in four dimensions (north, south, east, west), picking and droping items, and moving items inside other items.
I have added some extra features appart from the world parses:
-Player inventory capacity: I have defined a capacity in the player class that defines how many items the player can have, items also have size and there is a bagpack that increments the player capacity.
-Build mechanic: I have defined a build action that allows the player to craft new items out of base items in the example.txt like crafting a Sword or Bait out of a Rock, Paper and Stick.
-Dragon creature: I have made a series of rules that check whether you are capable of advancing to the next room if there is a dragon creature in the same room as you are, and it blocks the path if you have not built a specific item (Is it the sword or the bait? Play and find out!)
-Look and inspect actions: You can inspect the room or entities in the room to check which items do they contain. Or simply look at the room name and description.
-reset action: In case you build the wrong item, the game will not be beatable and you will have to reset (I didn't want to simply create a destroy Item that gives you back the items, but I couldn't think of a fun way to get back the needed materials for building the other item)

I hope you enjoy the game!!!

Oriol Gallego Vazquez