CREATE TABLE character (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    distanceTraveled INTEGER,
    gold INTEGER,
    level INTEGER,
    exp INTEGER,
    expNext INTEGER,
    strength INTEGER,
    vitality INTEGER,
    dexterity INTEGER,
    intelligence INTEGER,
    hp INTEGER,
    hpMax INTEGER,
    stamina INTEGER,
    damageMin INTEGER,
    damageMax INTEGER,
    accuracy INTEGER,
    defense INTEGER,
    luck INTEGER,
    statPoints INTEGER
);

CREATE TABLE weapon (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    damageMin INTEGER,
    damageMax INTEGER,
	buyValue INTEGER,
	sellValue INTEGER,
	level INTEGER,
	rarity INTEGER
);

CREATE TABLE armor (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    type INTEGER,
	defense INTEGER,
	buyValue INTEGER,
	sellValue INTEGER,
    level INTEGER,
	rarity INTEGER,
	typeStr TEXT
);

CREATE TABLE enemy(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    level INTEGER,
	hp INTEGER,
	hpMax INTEGER,
	damageMin INTEGER,
	damageMax INTEGER,
	dropChance INTEGER,
	defense INTEGER,
	accuracy INTEGER
);

INSERT INTO enemy (name, level, hp, hpMax, damageMin, damageMax, dropChance, defense, accuracy) 
           VALUES ("Goblin", 1, 100, 150, 15, 20, 3, 25, 4);