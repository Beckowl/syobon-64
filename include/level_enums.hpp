#ifndef LEVEL_ENUMS_H
#define LEVEL_ENUMS_H

// Names here are NOT meant to be accurate to character names' here
// I want this to be understandable by anyone reading.

// -------------------------
// Level Types
// -------------------------

typedef enum {
    LEVEL_TYPE_OVERWORLD = 1,
    LEVEL_TYPE_UNDERGROUND = 2,
    LEVEL_TYPE_SKY = 3,
    LEVEL_TYPE_CASTLE = 4,
    LEVEL_TYPE_ICY = 5,
} LevelType;




// -------------------------
// Music IDs
// -------------------------

typedef enum {
    MUSIC_NONE = 0,
    MUSIC_OVERWORLD = 1,
    MUSIC_UNDERGROUND = 2,
    MUSIC_BONUS = 3,
    MUSIC_CASTLE = 4,
    MUSIC_CREDITS = 5,
} MusicId;




// -------------------------
// Tile Types
// -------------------------

typedef enum {
    // Tiles 0–10 form the base set for a level type.
    // Adding multiples of 30 (up to +90) to these tile IDs switches to the
    // same block style in the next level type.
    // Example: In an overworld level, TILE_BRICKS + 30 becomes the blue
    // underground version of the bricks.

    TILE_SOLID_COLOR = 0,
    TILE_BRICKS = 1,
    TILE_ITEM_BLOCK_COIN = 2,
    TILE_ITEM_BLOCK_OPEN = 3,
    TILE_HARD_BLOCK = 4,
    TILE_GROUND_TOP = 5,
    TILE_GROUND_BOTTOM = 6,

    // Has a coin inside
    TILE_ITEM_BLOCK_HIDDEN = 7,

    // Only visible in overworld or sky stages
    TILE_CLOUD_BLOCK = 8,

    // A literal invisible solid block (not a hidden block)
    TILE_INVISIBLE_BLOCK = 9,
    TILE_SPIKE = 10,

    // A trampoline that you can't interact with
    TILE_TRAMPOLINE_BROKEN = 16,

    // A fake item block that you can't hit
    // (block at the start of 1-1)
    TILE_ITEM_BLOCK_DODGE = 100,

    // Item block with a goomba
    TILE_ITEM_BLOCK_ENEMY = 101,
    TILE_ITEM_BLOCK_MUSHROOM = 102,   // "Delicious!"
    TILE_ITEM_BLOCK_MUSHROOM_2 = 103, // "Not poisonous, but..."
    TILE_ITEM_BLOCK_STAR = 104,

    // Invisible item block with infinite poisonous mushrooms
    TILE_ITEM_BLOCK_POISON = 110,
    // Same as above, but already open
    TILE_ITEM_BLOCK_POISON_OPEN = 111,

    // Has a ton of coins inside
    TILE_COIN_BRICK = 112,
    // Same as above but already open
    TILE_COIN_BRICK_OPEN = 113,

    // Item block with a single poisonous mushroom inside
    TILE_ITEM_BLOCK_POISON_SINGLE = 114,

    // Crumbles when stood on
    TILE_BRITTLE_BRICK = 115,
    TILE_ITEM_BLOCK_PSWITCH = 116,

    TILE_NOTE_BLOCK = 117,

    // Will push the player to its side when landed on
    TILE_PUSH_BLOCK = 118,
    TILE_TRAMPOLINE = 120,

    // Plays a P-switch sound when hit???
    TILE_SWITCH_BLOCK = 124,

    // Toggle blocks 
    // They're the same since game updates based on stageonoff
    TILE_OFF_BLOCK = 130,
    TILE_ON_BLOCK = 131,

    // Alias for clarity
    TILE_ON_OFF_BLOCK = TILE_OFF_BLOCK,  
    TILE_SWORD = 140,
    TILE_BRIDGE_ROPE = 141,
    TILE_ARTICHOKE = 142,

    // Hitting this will display the test message (id 0)
    TILE_MESSAGE_BLOCK = 300,
    TILE_MESSAGE_BLOCK_BREAKABLE = 301,
    TILE_PSWITCH = 400,
    TILE_COIN = 800,
} TileType;




// -------------------------
// Enemy Types
// -------------------------

typedef enum {
    ENEMY_BALL = 0,
    ENEMY_BALL_SHELLED = 1,
    ENEMY_SHELL = 2,
    ENEMY_SEAL = 3,
    ENEMY_BALL_SPIKY = 4,
    ENEMY_BEAR = 5,
    ENEMY_ROBOT = 6,
    ENEMY_BALL_ROCKET = 7,
    ENEMY_CAPE_GUY = 8,
    ENEMY_MAGMA = 9,
    ENEMY_FLAME = 10,

    // Enemy at the end of 1-4 on the bridge
    // Called "ボス" (boss) in Chiku's comments
    ENEMY_BOSS = 30,
    ENEMY_MOLALA = ENEMY_BOSS,

    ENEMY_CHICKEN = 31,
    ENEMY_KUKKURU = ENEMY_CHICKEN,

    // ID exists in the code but doesn't do anything??
    ENEMY_50 = 50,

    ENEMY_LASER = 79,
    
    ENEMY_EVIL_CLOUD = 80,
    ENEMY_SPIKY_BRICK = 82,
    ENEMY_FAKE_POLE = 85,

    // falls and breaks blocks below
    ENEMY_FALLING_CAT = 86,

    ENEMY_FIREBAR_CLOCKWISE = 87,
    ENEMY_FIREBAR_COUNTERCLOCKWISE = 88,

    // green "?" ball
    ENEMY_MYSTERY_BALL = 105,
} EnemyType;




// -------------------------
// Decoration Types
// -------------------------

typedef enum {
    DECORATION_HILL = 0,
    DECORATION_GRASS = 1,
    DECORATION_CLOUD = 2,
    DECORATION_CASTLE = 3,
    DECORATION_CLOUD_SMALL = 4,
    DECORATION_TREE = 5,
    DECORATION_LAVA = 6,

    DECORATION_TEXT_51 = 100,
    DECORATION_TEXT_GAME_CLEAR = 101,
    DECORATION_TEXT_THANKS_FOR_PLAYING = 102,
} DecorationType;

#endif