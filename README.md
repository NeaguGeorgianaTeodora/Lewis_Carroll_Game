# Lewis_Carroll_Game
For this game, a starting and a target word will be assigned. At each step of the game, you must change a single letter of the word, such that you transform it into another existing word (it is forbidden to transform a word into a non-word). 
For example, if the starting word is SAME and the target word is COST, one solution would be the following:
SAME
CAME
CASE
CAST
COST
In this project, we are interested in computing the way we can transform the starting word into the target word. We will achieve this using a graph data structure.
More specifically, we will construct a graph based on a dictionary containing words with the same number of letters. The nodes in the graph represent the words from the dictionary; there is an edge between two words if you can transition from one word to the other by changing a single letter.
We will use a map data structure to store all the words that comply with a given pattern; a pattern is defined by a word in which one and only one of its letters have been replaced by a *, and therefore it can be replaced by any letter.
For example, we might have the following patterns and words that comply with that pattern:
*AME : CAME, LAME, NAME, SAME 
S*ME: SAME, SOME
SA*E: SAGE, SALE, SAME, SANE, SASE
In the first line from the example above: we have the pattern *AME. This will be a key in the map. In the bucket corresponding to this key, we add all the words from the dictionary that correspond to this pattern: CAME, LAME, NAME, SAME. Of course, this example is not exhaustive.
This map will have as key a string (the pattern) and as values a list of words that comply with that pattern. To construct the map, we iterate through all the words in the dictionary and add them to all the corresponding patterns in the map. 
Then we can start building the graph: for each key in the map, we take all the words that comply with that pattern and we add an edge between all the possible pairs from this list. 
Now we can drop the additional map data structure and focus only on the graph.
The problem of finding the best transformation from the starting word to the target word comes to finding the shortest path between the starting word and the target word in the graph that you created.

