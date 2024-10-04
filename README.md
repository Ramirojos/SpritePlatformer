## 2D Sprite Platformer

Small platformer using 2D sprites with Unreal engine. The objective is to practice and get confortable with Unreal Engine.

### TODOS:

**Create Main Character with basic functionality (movement, sprite mesh, rotation, initial health, initial points).//DONE**

**Create main Pickup that is the parent to a Points Pickup and a Health Pickup.//DONE**

**Create Health Pickup and Points Pickup//DONE**

**Keep track of the win/lose conditions (0 health/ 'X' ammount of points).// DONE**

**Interaction between Player Character and Pickups. //DONE**

**Create Base Enemy and its base characteristics (capusle, sprite, etc). //DONE**

**Creation of win/lose conditions ( life = 0 -> lose,  X ammount of points and win platform overlap -> win). //Partially done, only loose condition at the moment.**

**Create specialized Enemies ( slow but more damage, fast one, normal one)**

**Tweaks to the player character( better mid-air controll during jumps, death animation, etc).**

**Menu and in Game UI.//PArtially Done, Made "Start Level" widget**

**LOG:**
09/16/24
Removed the Attributes component and system. Out of scope for such a simple project. 
Decided to save the character stats inside the PlayerPaperCharacter file. 
Interactions between pickups, enemy and character working as intended. 
TODO: keep cleaning code.

10/04/24
Created Gamemode and added functionality:
Handling Game Start (disable/enable of user input - SetPlayerEnabledState of SpritePlayerController Class - after timer ends) and handle Character death (call to HandleDestruction from PlayerPaperCharacter class and SetPlayerEnabledState of SpritePlayerController Class).
Creation of GameStart Widget, display changes in response to Timer.

Improvements on the SpritePlayerController Class: creation of the SetPlayerEnabledStated(bool bPlayerEnabled) method, allows to enable or disable player input.

PlayerPaperCharacter: 
Creation of HandleDestruction() method.




