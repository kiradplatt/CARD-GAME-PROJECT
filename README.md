# CARD-GAME-PROJECT
It is a card game project source code for a Computer Programming course in Ca'Foscari University of Venice.
1. Components
  • A deck of 40 cards divided into 4 suits
    – 10 cards - Clubs (from 1 to 7, with J,Q K)
    – 10 cards - Spades (from 1 to 7, with J,Q K)
    – 10 cards - Diamonds (from 1 to 7, with J,Q K)
    – 10 cards - Hearts (from 1 to 7, with J,Q K)
2. Players
  • From 2 to 20 players
3. Goal of the game
  • Be the last player in the game
4. Game Play
  At the beginning of the game each player has 2 life points.
  The game is played in phases. At each stage:
  1. Shuffle the deck.
  2. Deal each player 2 cards: one face down and one face up.
  3. Randomly choose the first player of the phase.
5. Progress of the Phase
  The phase takes place by giving each player a turn. Starting from the first player, in ascending ring
  order, the player in the turn:
    1. must resolve the effect of the face-up card (see card effect).
    2. can view the face-down card and optionally reveal/flip it (from face-down to face-up) to apply
    its effect. If it has already been discovered due to the effect of other cards, it will not be possible
    to apply its effect again.
    3. ends the turn and the play moves on to the next player. At the end of all players’ turns, the
    phase ends and whoever has no more lives is eliminated from the game.
      What does ascending ring order mean?
        • Suppose to have 3 player in game (P1, P2, P3)
          – If the first player is P1, the phase will follow the turns P1 → P2 → P3
          – If the first player is P2, the phase will follow the turns P2 → P3 → P1
          – If the first player is P3, the phase will follow the turns P3 → P1 → P2
6. Card Effect
  • Cards from 2 to 6: no effects.
  • Card 7: the player who holds this card (face-up) forces the next player to reveal the face-down
    card and apply its effect.
  • Card J: the player who holds this card (face-up) must give 1 life point to the previous player.
  • Card Q: the player who holds this card (face-up) must give 1 life point to the second following
    player. (i.e., skipping a player).
  • Card 1: the player who holds this card (face-up) drops 1 life point to the playing field (the
    life points on the playing field are not reset at each phase, so they remain even for the following
    ones if they have not been claimed).
  • Card K: the player who holds this card (face-up) must claim all the life points dropped until
    that time on the playing field.
7. End of the Game
    The game ends when only one player remains at the end of a phase and the others have all been
        eliminated from the game
