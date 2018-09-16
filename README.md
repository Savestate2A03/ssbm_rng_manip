# ssbm_rng_manip
use the css to determine rng seed &amp; calculate distance of rng based events

# allstar
most folks here are interested in all-star mode rng.

the allstar command `ALLSTAR` in manip.cfg takes 24 paramaters, each is a bitmask determining which characters are allowed in each slot of a run. 

you'll usually do singles, doubles leaders, and trips leaders having masks, and allowing all chars on the rest. 


ssbm resets the run list to be in the order below (swapping ganon and gnw)

so the program inits its list to it as well. when you restart the program, you have to restart your console and vice versa

1. choose `y` when starting the program to find your seed by selecting random chars on the vs select screen
2. choose the config option for allstar
3. let it run (may take a long time (0-5 minutes) depending on how strict your config is)
4. open a cpu window for how long it says
5. close it and then choose `l` to continue from the last seed it detected you were at.
6. if you waited longer than 5 seconds or so, do 5 characters, otherwise 4 if less
7. continue this process until you are a few hundred iterations away.
8. random characters on the CSS to advance your rng two iterations, random a tag to advance it once. 
9. go into and out of allstar X times 
10. advance the rng by `delay` amount of times.

go into allstar and there u go. 

```
    | bit | id   | name
    |-----|------|---------------------------------------
    |   0 | 0xB1 | Rainbow Cruise (vs Mario)
    |   1 | 0xB2 | Kongo Jungle (vs Donkey Kong)
    |   2 | 0xB3 | Great Bay (vs Link)
    |   3 | 0xB4 | Brinstar (vs Samus)
    |   4 | 0xB5 | Yoshi's Story (vs Yoshi)
    |   5 | 0xB6 | Green Greens (vs Kirby)
    |   6 | 0xB7 | Corneria (vs Fox)
    |   7 | 0xB8 | Pokémon Stadium (vs Pikachu)
    |   8 | 0xB9 | Mushroom Kingdom I (vs Luigi)
    |   9 | 0xBA | Mute City (vs Captain Falcon)
    |  10 | 0xBB | Onett (vs Ness)
    |  11 | 0xBC | Poké Floats (vs Jigglypuff)
    |  12 | 0xBD | Icicle Mountain (vs Ice Climbers)
    |  13 | 0xBE | Princess Peach's Castle (vs Peach)
    |  14 | 0xBF | Temple (vs Zelda)
    |  15 | 0xC0 | Fountain of Dreams (Emblem Music) (vs Marth)
    |  16 | 0xC1 | Battlefield (Poké Floats song) (vs Mewtwo)
    |  17 | 0xC2 | Yoshi's Island (vs Bowser)
    |  18 | 0xC3 | Mushroom Kingdom II (Dr Mario Music) (vs Dr Mario)
    |  19 | 0xC4 | Jungle Japes (vs Young Link)
    |  20 | 0xC5 | Venom (vs Falco)
    |  21 | 0xC6 | Fourside (vs Pichu)
    |  22 | 0xC7 | Final Destination (Emblem Music) (vs Roy)
    |  23 | 0xC8 | Flat Zone (vs Team Game & Watch)
    |  24 | 0xC9 | Brinstar Depths (vs Ganondorf)
    |----------------------------------------------------
```

