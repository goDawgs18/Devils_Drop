# Devils_Drop
Ride down Devil's Drop if you dare!!! Play as a brave skiier that takes on the ride of their life!
(EEP 520 final Project)

## Game Details:
#### How to set up the game:
1. First install and run docker on your computer
2. Run the following line of code to set up your environment:
```
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
```
3. Go to the Devils_Drop directory and type the following lines of code to start the game
```
esm start
make
enviro
```
4. Navigate to you machines local host on a web browser. Suggested to use Google Chrome. 

#### Gameflow:
The user will play the role of a thrill seeking skiier going down Devil's Drop. The goal for the player is to avoid the trees as they descend down the hill. As the player gets further and futher down the hills trees will start appear faster. If the skiier crashes into a tree game will end and a feet decended will appear in the terminal window running the game. 

The user can always restart the game simply by click the "Go Down Devil's Drop" button.

#### Controls:
- Press the button "Go Down Devil's Drop" to start skiing down the hill
- Press "a" to move the player left
- Press "s" to make the player go straight down the hill or stop horizontal motion
- Press "d" to move the player to the right

## Project Information
#### Goal of the project
The goal of this project was to make a game that envolved enviro and elma. I wanted to make a final project automatically generated objects that the user had to navigate through. My first thought was to make a randomized maze. However during the design process I couldn't think of a way to score user performance. So I made a dodging instead. Then I figured it would be fun to add in some skiing graphics.

#### Design Challenges
During the design process there were a few challenges
- The game would glitch a bit when I got too far in the game. I resolved this by making the objects remove themselves once they have passed a certain threshold
- I wanted the game to be restartable. This was a bit tricky because I could not make the button itself move objects. I needed an object to react when the button was pressed. I solved this by 'removing' the player from the game on a crash by moving it outside the players view. I then brought it back into play when the player clicks the start button
- I wanted to have all the objects dissapear when there was a crash. This ended up being a bit tricky. On a crash I set up the player code so that on a crash it would emit an event that all the other objects would respond to by removing themselves. However this ended up making a bug in my code because the interupt event would superseed the current code that was running. So sometimes I would be trying to have an object trying to remove itself after it had past the threshold after it had already removed itself from the event. Which would cause my code to fail. I resolved this by setting a flag in the interrupt routine instead of actually deleting the element. 

## Resources
Here is a list of resources that I used to develop this code:
- Enviro library: https://github.com/klavinslab/enviro
- Elma library: http://klavinslab.org/elma/
- Course information: https://github.com/klavins/ECEP520
- Environment Generation: https://www.docker.com/
- IDE: https://code.visualstudio.com/
