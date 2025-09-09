# Game in C  

This project is a **Stone game** implemented in C.  
It supports a **single-player mode** where the human plays against the **computer AI** (Minimax with Alpha–Beta pruning).  

---

##  Features
- Interactive **menu system** with:
  -  New Game  
  -  Game Rules  
  -  Exit  
- Complete **Gameplay mechanics**:
  - Stone distribution  
  - Extra turns if last stone lands in player’s store  
  - Capturing opponent’s stones  
  - Endgame stone collection  
- **Computer AI** using **Minimax with Alpha–Beta pruning** for smarter moves  
- User-friendly board display  

---

##  Game Rules
1. The board has **6 pits per player** and **1 store** each.  
2. Players take turns choosing one of their pits.  
3. Stones are distributed counterclockwise, one per pit.  
   - You drop a stone in your store but **skip opponent’s store**.  
4. If your **last stone lands in your store**, you get another turn.  
5. If your **last stone lands in an empty pit on your side**, you capture that stone + opposite pit’s stones.  
6. The game ends when one player’s pits are empty.  
7. Remaining stones on the other side go to their store.  
8. Player with the **most stones in their store** wins.  

---

##  How to Compile & Run
### Compile
```
gcc game.c -o game
```

### Run
```
mancala.exe # Windows
```

---

##  Algorithm Details
- The computer uses **Minimax search** with **Alpha–Beta pruning**.  
- Evaluation function:  
  ```
  score = (Computer’s store stones) - (User’s store stones)
  ```
- Search depth = **5** (configurable with `MAX_DEPTH`).  

---

##  Project Structure
```
game.c     # main source code 
README.md     # project documentation
```

---

##  Future Improvements
- Allow custom number of pits or stones per pit.
- Add save and load functionality using file handling in C.

---
