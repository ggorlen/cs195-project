# Project Proposals

### What's the proposal?

Our proposal is to create an implementation of a puzzle game in C++ that will be compiled to [WASM](https://en.wikipedia.org/wiki/WebAssembly) with [Emscripten](https://en.wikipedia.org/wiki/Emscripten) to power a HTML5/JS/CSS user interface.

### How will it be tested?

Unit testing will be performed on the C++ game engine code using [`utest.h`](https://github.com/sheredom/utest.h). The browser user interface will be tested with [Jest](https://github.com/facebook/jest) and [Puppeteer](https://github.com/puppeteer/puppeteer/).

### Why is this a good idea?

The main selling point is that the turn-based nature of puzzle/strategy games and the HTML user interface makes it very easy to test our code (a key deliverable for the course), as opposed to a live action game on a screen where it'd be very difficult to programmatically provide input and assert on game state. Real-time graphics-based games can be math-heavy and asset-heavy.

Furthermore, the web-based UI makes the product much more accessible to the average user than more esoteric interfaces like the console, SDL2 or SFML which are hard to install. We get the best of JS/HTML, which I have a good amount of experience in, plus C++ for those who are more comfortable with it.

Puzzle/board games also generally don't require the investment in developing story, characters and assets which could be a major time sink if we pursued an interactive turn-based RPG (although that would be easy to test).

There is a very clear separation between front- and back-ends, so we can delegate disjoint tasks and responsibilities. The back-end game logic can be written in C++ without any knowledge of JS (and could ideally be modular enough to couple with a command-line front-end that might be useful for development), and Greg will link the JS and C++ components together.

Finally, all of these technologies are popular and industry-relevant, and the scope of the project is flexible. It should be educational!

### Do you have a proof of concept?

Greg built a simple proof-of-concept that illustrates the concept/workflow and relevant technologies interoperating: <https://github.com/ggorlen/wasm-click-counter>.

### Division of responsibilities

We can divide responsibilities up for the project roughly as follows (feel free to weigh in on your preferred role -- I'm just guessing for now):

- Greg will be responsible for project management, the HTML/JS user interface, Puppeteer integration testing, and any other JS needs. He'll be responsible for keeping the project glued together. He might also be involved in the C++ engine as needed. He's happy to share any of these duties if there's interest.
- Severin will focus on C++ game engine mechanics and some HTML/JS
- Juan will focus on C++ game engine mechanics and assets
- Irvin will focus on C++ game engine mechanics and assets.

### Gameplay Requirements

World generation. The world will have a square dimension with a maxium 30 x 30 tiles. The world will have an aerial perspective (viewed from above). The world elements will consist of tiled floors, walls or holes. Each level will have a predetermined map with increasing difficulty.

Character. The main character will have four main movements: forward, backward,
left and right. These movements will be controlled by keyboard presses. If the user presses the UP button, the character will move one tile to the north, or if the user presses DOWN button, the character will move one tile to the south. The character can only move within the constraints of the map. The character can push on an existing box but can't go beyond any immovable obstacles (like the walls).

### Game Mechanics


### Stretch goals
* In world generation, we can build a randomized map based on specified level of difficulty. In the beginning of the game, the user can input an integer which will represent the level of difficulty. We can pass that input to a function (e.g. mapgenerator(level)) to build a new map. This randomized map generator can replace the pre-determined maps that we used in the beginning phase of our development.
* In character, we can add an option of selecting three different type of characters to use.
* AI generated optimized solution. With the given world, we can implement Dijkstra's algorightm to find the shortest path to a goal. We can use that to add as a HINT feature or some sort.

### Further details

We've decided on a one-player [puzzle game](https://en.wikipedia.org/wiki/List_of_puzzle_video_games) like Sokoban or Qualio.

### Architecture diagram

```
           BACKEND (game engine)

       .-------.
       | uTest |
       `-------`
           |
           v        [emscripten compilation]
.-----------------.          |
| C++ game engine |----------+--+
`-----------------`             |
                                |
................................|.............
                                |
.------.   FRONTEND (browser)   |
| User |                        |
`------`                        |
   |                            |
[click events]    [API calls]   |
   |                   |        v
   |   .----------.~~~~+~~~>.------.
   +-->| HTML5 UI |         | WASM |<--compiled backend engine
       `----------`<~~~+~~~~`------`
            ^          |
            |     [game state]
            |
            |
.----------------------.
| Jest/Puppeteer tests |
`----------------------`
```

