## 2D Sprite Platformer

Small platformer using 2D sprites with Unreal engine. The objective is to practice and get confortable with Unreal Engine.

### TODOS:

**Create Main Character with basic functionality (movement, sprite mesh, rotation, initial health, initial points).//DONE**

**Create main Pickup that is the parent to a Points Pickup and a Health Pickup.//DONE**

**Create Health Pickup and Points Pickup//DONE**

**Keep track of the win/lose conditions (0 health/ 'X' ammount of points).// DONE**

**Interaction between Player Character and Pickups. //DONE**

**Create Base Enemy and its base characteristics (capusle, sprite, etc). //DONE**

**Creation of win/lose conditions ( life = 0 -> lose,  X ammount of points and win platform overlap -> win).//DONE**

**Create specialized Enemies ( slow but more damage, fast one, normal one)**

**Tweaks to the player character( better mid-air controll during jumps, death animation, etc). //DONE**

**Menu and in Game UI.//Partially Done, Made "Start Level" widget**

**LOG:**
09/16/24
Removed the Attributes component and system. Out of scope for such a simple project. 
Decided to save the character stats inside the PlayerPaperCharacter file. 
Interactions between pickups, enemy and character working as intended. 
TODO: keep cleaning code.

////////////////////////////////////////////

10/04/24
Created Gamemode and added functionality:
Handling Game Start (disable/enable of user input - SetPlayerEnabledState of SpritePlayerController Class - after timer ends) and handle Character death (call to HandleDestruction from PlayerPaperCharacter class and SetPlayerEnabledState of SpritePlayerController Class).
Creation of GameStart Widget, display changes in response to Timer.

Improvements on the SpritePlayerController Class: creation of the SetPlayerEnabledStated(bool bPlayerEnabled) method, allows to enable or disable player input.

PlayerPaperCharacter: 
Creation of HandleDestruction() method.

////////////////////////////////////////////

11/4/2024
Win/Lose conditions:
changed the win conditions from "collect all pickup points" to win when all the points pickups were collected and reach the "Win zone".

Game over widgets:
Created both win and lose widgets, triggered when the player reaches the "Win zone" and when the player life reaches 0.

Start Game
Enable input after a imer reaches 0.
Countdown widget.

Level progression:
when player collects all of the points pickups and reaches a "next level zone" the next level is loaded. All of the player stats return to heir default value.

Jump Improvements:
Mid air controls improvement.
Added double jump

Other:
Code cleanup.
Removed Pickup Interface, not longer needed.

////////////////////////////////////////////
