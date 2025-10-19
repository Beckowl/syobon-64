#ifndef LEVEL_ENUMS_H
#define LEVEL_ENUMS_H

// Names here are NOT meant to be accurate to character names' here
// I want this to be understandable by anyone reading.

// -------------------------
// Level Types (stagecolor)
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
    // Syobon 64 only!! do not use this in the og game! 
    MUSIC_NONE = 0,
    MUSIC_OVERWORLD = 1,
    MUSIC_UNDERGROUND = 2,
    MUSIC_BONUS = 3,
    MUSIC_CASTLE = 4,
    MUSIC_CREDITS = 5,
} MusicId;




// -------------------------
// Tile Types (ttypes)
// -------------------------

typedef enum {
    // Tiles 0–10 form the base set for a level type.
    // Adding multiples of 30 (up to +90) to these tile IDs switches to the
    // same block style in the next level type.
    // Example: In an overworld level, TILE_BRICK + 30 becomes the blue
    // underground version of the bricks.

    TILE_SOLID_COLOR = 0,
    TILE_BRICK = 1,
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
    TILE_BRICK_STAR = 104,

    // Invisible item block with infinite purple mushrooms
    TILE_ITEM_BLOCK_MUSHROOM_PURPLE = 110,
    // Same as above, but already open
    TILE_ITEM_BLOCK_MUSHROOM_PURPLE_OPEN = 111,

    // Has a ton of coins inside
    TILE_BRICK_COIN = 112,
    // Same as above but already open
    TILE_BRICK_COIN_OPEN = 113,

    // Item block with a single poisonous mushroom inside
    TILE_ITEM_BLOCK_POISON_SINGLE = 114,

    // Crumbles when stood on
    TILE_BRICK_BRITTLE = 115,
    TILE_ITEM_BLOCK_PSWITCH = 116,

    TILE_NOTE_BLOCK = 117,

    // Will push the player to its side when landed on
    TILE_PUSH_BLOCK = 118,
    TILE_TRAMPOLINE = 120,

    // will grow firebars when hit
    TILE_FIREBAR_GROW = 124,

    // Toggle blocks 
    // They're the same since game updates based on stageonoff
    TILE_ON_BLOCK = 130,
    TILE_OFF_BLOCK = 131,

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
// Enemy Types (atypes)
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

    ENEMY_FALLING_BLOCK = 51,
    ENEMY_FALLING_BLOCK_2 = 52,

    ENEMY_LASER = 79,
    
    ENEMY_EVIL_CLOUD = 80,
    ENEMY_EVIL_CLOUD_TOUCHED = 81,

    ENEMY_SPIKY_BLOCK = 82,
    ENEMY_SPIKY_BLOCK_TOUCHED = 83,
    ENEMY_LAVA_FROM_PIPE = 84,

    ENEMY_FAKE_POLE = 85,

    // falls and breaks blocks below
    ENEMY_FALLING_CAT = 86,

    ENEMY_FIREBAR_CLOCKWISE = 87,
    ENEMY_FIREBAR_COUNTERCLOCKWISE = 88,

    ENEMY_MUSHROOM_RED = 100,
    ENEMY_FIRE_FLOWER = 101,
    ENEMY_MUSHROOM_PURPLE = 102,

    // green "?" ball
    ENEMY_MYSTERY_BALL = 105,

    // The same as ENEMY_BALL but goes
    // right through the floor??
    ENEMY_BALL_NO_COLLISION = 200,
} EnemyType;




// -------------------------
// Decoration Types (ntypes)
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




// -------------------------
// Platform types (srtypes)
// -------------------------

typedef enum {
    PLATFORM_YELLOW = 0,
    PLATFORM_BREAKING = 1,

    // pushes you off when stood on
    PLATFORM_PUSH_LEFT = 2,
    PLATFORM_PUSH_RIGHT = 3,

    PLATFORM_PILLAR = 10,

    // Will start falling as soon as you get close to it
    PLATFORM_PILLAR_FALL = 11,
    PLATFORM_PILLAR_BOUNCY = 12,
    PLATFORM_PILLAR_BRICKS = 15,

    PLATFORM_GRAY = 21,

} PlatformType;




// -------------------------
// object types (stypes)
// -------------------------

typedef enum {
    // not sure what this is
    OBJECT_GREEN_BLOCK = 0,

    OBJECT_VERTICAL_PIPE_HEAD = 1,
    OBJECT_PIPE_BODY = 2,
    OBJECT_HORIZONTAL_PIPE_HEAD = 5,

    // It's the same as OBJECT_PIPE_BODY (???)
    OBJECT_PIPE_BODY_2 = 40,
    OBJECT_PIPE_TROLL = 50,

    // Falling brick ceiling
    OBJECT_FALLING_BRICKS = 51,
    OBJECT_FALLING_FLOOR = 52,

    OBJECT_TRIGGER_SEAL_UP = 100,
    OBJECT_TRIGGER_SEAL_DOWN = 101,
    OBJECT_TRIGGER_MISC = 102,
    OBJECT_TRIGGER_LASER = 103,
    OBJECT_TRIGGER_MULTI_LASER = 104,

    // This is what makes the brick platform split in 1-4
    OBJECT_TRIGGER_PLATFORM_SPLIT = 105,

    OBJECT_CASTLE_BRICKS = 200,

    OBJECT_GOAL_POLE = 300,

    // Makes lava come out of the pipe in 1-2
    OBJECT_LAVA_SPAWNER = 180,
    OBJECT_CHECKPOINT = 500,
} ObjectType;

#endif