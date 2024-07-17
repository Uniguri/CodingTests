use std::io::{stdin, Read};

const MINIMUM_DAMAGE: u32 = 1;
const SPIKE_TRAP_DAMAGE: u32 = 5;

const PLAYER_HP_REGENERATION_VALUE: u32 = 3;

const PLAYER_DEFAULT_HP: u32 = 20;
const PLAYER_DEFAULT_ATT: u32 = 2;
const PLAYER_DEFAULT_DEF: u32 = 2;

const PLAYER_NEEDED_EXP_FACTOR: u32 = 5;
const PLAYER_LEVEL_UP_HP_GROWTH: u32 = 5;
const PLAYER_LEVEL_UP_ATT_GROWTH: u32 = 2;
const PLAYER_LEVEL_UP_DEF_GROWTH: u32 = 2;

enum ItemEnchant {
    HpRegeneration,
    Reincarnation,
    Courage,
    Experience,
    Dexterity,
    Hunter,
    Cursed,
}

enum ItemType {
    Weapon { attack_power: u32 },
    Armor { defense_power: u32 },
    Ornament { enchant: ItemEnchant },
    Empty,
}

struct Monster<'a> {
    name: &'a str,
    is_boss: bool,
    attack_power: u32,
    defense_power: u32,
    max_hp: u32,
    hp: u32,
    exp: u32,
}

impl Monster<'_> {
    fn empty_monster() -> Self {
        Self {
            name: "",
            is_boss: false,
            attack_power: 0,
            defense_power: 0,
            max_hp: 0,
            hp: 0,
            exp: 0,
        }
    }

    fn is_dead(&self) -> bool {
        return self.hp == 0;
    }

    fn is_alive(&self) -> bool {
        !self.is_dead()
    }

    fn attack_to(&self, player: &mut Player, attack_power_factor: u32) {
        player.take_damage(self.attack_power * attack_power_factor);
    }

    fn take_damage(&mut self, attack_damage: u32) {
        let damage = std::cmp::max(
            MINIMUM_DAMAGE,
            attack_damage.saturating_sub(self.defense_power),
        );
        self.hp = self.hp.saturating_sub(damage);
    }
}

enum MapTileType<'a> {
    Player,
    Empty,
    Wall,
    ItemBox { item: ItemType },
    SpikeTrap { is_player_on: bool },
    Monster { detail: Monster<'a> },
    BossMonster { detail: Monster<'a> },
}

enum TakeDamageResult {
    Alive,
    Dead,
    Reincarnated,
}

struct Player {
    max_hp: u32,
    hp: u32,
    exp: u32,
    level: u32,
    attack_power: u32,
    weapon_attack_power: u32,
    defense_power: u32,
    armor_defense_power: u32,
    number_of_equipped_ornaments: u32,
    has_enchant_hp_regeneration: bool,
    has_enchant_reincarnation: bool,
    has_enchant_courage: bool,
    has_enchant_experience: bool,
    has_enchant_dexterity: bool,
    has_enchant_hunter: bool,
    has_enchant_cursed: bool,
}

impl Player {
    fn default_player() -> Self {
        Self {
            max_hp: PLAYER_DEFAULT_HP,
            hp: PLAYER_DEFAULT_HP,
            exp: 0,
            level: 1,
            attack_power: PLAYER_DEFAULT_ATT,
            weapon_attack_power: 0,
            defense_power: PLAYER_DEFAULT_DEF,
            armor_defense_power: 0,
            number_of_equipped_ornaments: 0,
            has_enchant_hp_regeneration: false,
            has_enchant_reincarnation: false,
            has_enchant_courage: false,
            has_enchant_experience: false,
            has_enchant_dexterity: false,
            has_enchant_hunter: false,
            has_enchant_cursed: false,
        }
    }

    fn print_status(&self) {
        println!("LV : {}", self.level);
        println!("HP : {}/{}", self.hp, self.max_hp);
        println!("ATT : {}+{}", self.attack_power, self.weapon_attack_power);
        println!("DEF : {}+{}", self.defense_power, self.armor_defense_power);
        println!(
            "EXP : {}/{}",
            self.exp,
            self.level * PLAYER_NEEDED_EXP_FACTOR
        );
    }

    fn is_dead(&self) -> bool {
        self.hp == 0
    }

    fn is_alive(&self) -> bool {
        !self.is_dead()
    }

    fn can_level_up(&self) -> bool {
        self.exp >= self.level * PLAYER_NEEDED_EXP_FACTOR
    }

    fn has_ornament(&self, ornament: &ItemEnchant) -> bool {
        if self.number_of_equipped_ornaments == 0 {
            return false;
        }

        match ornament {
            ItemEnchant::HpRegeneration => self.has_enchant_hp_regeneration,
            ItemEnchant::Reincarnation => self.has_enchant_reincarnation,
            ItemEnchant::Courage => self.has_enchant_courage,
            ItemEnchant::Experience => self.has_enchant_experience,
            ItemEnchant::Dexterity => self.has_enchant_dexterity,
            ItemEnchant::Hunter => self.has_enchant_hunter,
            ItemEnchant::Cursed => self.has_enchant_cursed,
        }
    }

    fn level_up(&mut self) {
        self.exp = 0;
        self.level += 1;
        self.max_hp += PLAYER_LEVEL_UP_HP_GROWTH;
        self.hp = self.max_hp;
        self.attack_power += PLAYER_LEVEL_UP_ATT_GROWTH;
        self.defense_power += PLAYER_LEVEL_UP_DEF_GROWTH;
    }

    fn get_true_exp_and_level_up(&mut self, true_exp: u32) {
        self.exp += true_exp;
        if self.can_level_up() {
            self.level_up();
        }
    }

    fn get_exp_and_level_up(&mut self, original_exp: u32) {
        self.get_true_exp_and_level_up(if self.has_enchant_experience {
            (1.2 * original_exp as f64) as u32
        } else {
            original_exp
        });
    }

    fn equip_item(&mut self, item: &ItemType) -> bool {
        match item {
            ItemType::Armor { defense_power } => {
                self.armor_defense_power = *defense_power;
                true
            }
            ItemType::Weapon { attack_power } => {
                self.weapon_attack_power = *attack_power;
                true
            }
            ItemType::Ornament { enchant } => self.equip_ornament(enchant),
            ItemType::Empty => false,
        }
    }

    fn equip_ornament(&mut self, ornament: &ItemEnchant) -> bool {
        if self.number_of_equipped_ornaments >= 4 || self.has_ornament(ornament) {
            return false;
        }

        self.number_of_equipped_ornaments += 1;
        match ornament {
            ItemEnchant::HpRegeneration => {
                self.has_enchant_hp_regeneration = true;
            }
            ItemEnchant::Reincarnation => {
                self.has_enchant_reincarnation = true;
            }
            ItemEnchant::Courage => {
                self.has_enchant_courage = true;
            }
            ItemEnchant::Experience => {
                self.has_enchant_experience = true;
            }
            ItemEnchant::Dexterity => {
                self.has_enchant_dexterity = true;
            }
            ItemEnchant::Hunter => {
                self.has_enchant_hunter = true;
            }
            ItemEnchant::Cursed => {
                self.has_enchant_cursed = true;
            }
        }

        true
    }

    fn disarm_ornament(&mut self, ornament: &ItemEnchant) -> bool {
        if self.number_of_equipped_ornaments == 0 || !self.has_ornament(&ornament) {
            return false;
        }

        self.number_of_equipped_ornaments -= 1;
        match ornament {
            ItemEnchant::HpRegeneration => {
                self.has_enchant_hp_regeneration = false;
            }
            ItemEnchant::Reincarnation => {
                self.has_enchant_reincarnation = false;
            }
            ItemEnchant::Courage => {
                self.has_enchant_courage = false;
            }
            ItemEnchant::Experience => {
                self.has_enchant_experience = false;
            }
            ItemEnchant::Dexterity => {
                self.has_enchant_dexterity = false;
            }
            ItemEnchant::Hunter => {
                self.has_enchant_hunter = false;
            }
            ItemEnchant::Cursed => {
                self.has_enchant_cursed = false;
            }
        }

        true
    }

    fn attack_to(&self, monster: &mut Monster, attack_power_factor: u32) {
        monster.take_damage((self.attack_power + self.weapon_attack_power) * attack_power_factor);
    }

    fn take_true_damage(&mut self, true_damage: u32) {
        self.hp = self.hp.saturating_sub(true_damage);
    }

    fn take_damage(&mut self, attack_damage: u32) {
        let damage = std::cmp::max(
            MINIMUM_DAMAGE,
            attack_damage.saturating_sub(self.defense_power + self.armor_defense_power),
        );
        self.hp = self.hp.saturating_sub(damage);
    }

    fn take_spike_damage_and_poll_reincarnation(&mut self) -> TakeDamageResult {
        if self.has_enchant_dexterity {
            self.take_true_damage(MINIMUM_DAMAGE);
        } else {
            self.take_true_damage(SPIKE_TRAP_DAMAGE);
        }

        if self.is_alive() {
            return TakeDamageResult::Alive;
        } else {
            if self.has_enchant_reincarnation {
                self.disarm_ornament(&ItemEnchant::Reincarnation);
                self.hp = self.max_hp;
                return TakeDamageResult::Reincarnated;
            } else {
                return TakeDamageResult::Dead;
            }
        }
    }

    fn fight_and_poll_events(&mut self, monster: &mut Monster) -> TakeDamageResult {
        if self.has_enchant_hunter && monster.is_boss {
            self.hp = self.max_hp;
        }

        let player_first_attack_factor;
        if !self.has_enchant_courage {
            player_first_attack_factor = 1u32
        } else {
            if !self.has_enchant_dexterity {
                player_first_attack_factor = 2u32;
            } else {
                player_first_attack_factor = 3u32;
            }
        }

        self.attack_to(monster, player_first_attack_factor);
        if monster.is_alive() && !(self.has_enchant_hunter && monster.is_boss) {
            monster.attack_to(self, 1);
        }

        while self.is_alive() && monster.is_alive() {
            self.attack_to(monster, 1);
            if monster.is_alive() {
                monster.attack_to(self, 1);
            }
        }

        if self.is_alive() {
            if self.has_enchant_hp_regeneration {
                self.hp += PLAYER_HP_REGENERATION_VALUE;
                if self.hp > self.max_hp {
                    self.hp = self.max_hp;
                }
            }
            self.get_exp_and_level_up(monster.exp);
            return TakeDamageResult::Alive;
        } else {
            if self.has_enchant_reincarnation {
                self.disarm_ornament(&ItemEnchant::Reincarnation);
                self.hp = self.max_hp;
                monster.hp = monster.max_hp;
                return TakeDamageResult::Reincarnated;
            } else {
                return TakeDamageResult::Dead;
            }
        }
    }
}

struct Map<'a> {
    width: usize,
    height: usize,
    tiles: Vec<Vec<MapTileType<'a>>>,
    player_start_x: u32,
    player_start_y: u32,
    player_x: u32,
    player_y: u32,
    is_boss_dead: bool,
}

impl Map<'_> {
    fn empty_map(width: usize, height: usize, player_start_x: u32, player_start_y: u32) -> Self {
        Self {
            tiles: Vec::<Vec<MapTileType>>::with_capacity(height),
            width: width,
            height: height,
            player_start_x: player_start_x,
            player_start_y: player_start_y,
            player_x: player_start_x,
            player_y: player_start_y,
            is_boss_dead: false,
        }
    }

    fn print_map(&self) {
        for map_y in self.tiles.iter() {
            for tile in map_y {
                match tile {
                    MapTileType::Player => {
                        print!("@");
                    }
                    MapTileType::Empty => {
                        print!(".");
                    }
                    MapTileType::Wall => {
                        print!("#");
                    }
                    MapTileType::SpikeTrap { is_player_on } => {
                        print!("{}", if *is_player_on { "@" } else { "^" });
                    }
                    MapTileType::ItemBox { item: _ } => {
                        print!("B");
                    }
                    MapTileType::Monster { detail: _ } => {
                        print!("&");
                    }
                    MapTileType::BossMonster { detail: _ } => {
                        print!("M");
                    }
                }
            }
            println!("");
        }
    }
}

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut token = input.split_ascii_whitespace();

    let map_height = token.next().unwrap().parse::<usize>().unwrap();
    let map_width = token.next().unwrap().parse::<usize>().unwrap();

    let mut number_of_item_boxes = 0usize;
    let mut number_of_monsters = 0usize;
    let mut map = Map::empty_map(map_width, map_height, 0, 0);
    {
        let tiles = &mut map.tiles;
        for y in 0..map_height {
            tiles.push(Vec::<MapTileType>::with_capacity(map_width));
            let tiles_y = &mut tiles[y];

            let tiles_y_str = token.next().unwrap();
            for (x, tile) in tiles_y_str.chars().enumerate() {
                match tile {
                    '@' => {
                        map.player_start_x = x as u32;
                        map.player_x = map.player_start_x;
                        map.player_start_y = y as u32;
                        map.player_y = map.player_start_y;
                        tiles_y.push(MapTileType::Player);
                    }
                    '.' => {
                        tiles_y.push(MapTileType::Empty);
                    }
                    '#' => {
                        tiles_y.push(MapTileType::Wall);
                    }
                    'B' => {
                        tiles_y.push(MapTileType::ItemBox {
                            item: ItemType::Empty,
                        });
                        number_of_item_boxes += 1;
                    }
                    '^' => {
                        tiles_y.push(MapTileType::SpikeTrap {
                            is_player_on: false,
                        });
                    }
                    '&' => {
                        tiles_y.push(MapTileType::Monster {
                            detail: Monster::empty_monster(),
                        });
                        number_of_monsters += 1;
                    }
                    'M' => {
                        tiles_y.push(MapTileType::BossMonster {
                            detail: Monster::empty_monster(),
                        });
                        number_of_monsters += 1;
                    }
                    _ => (),
                }
            }
        }
    }

    let player_move = token.next().unwrap();

    for _ in 0..number_of_monsters {
        let monster_y = token.next().unwrap().parse::<usize>().unwrap() - 1;
        let monster_x = token.next().unwrap().parse::<usize>().unwrap() - 1;
        let monster_name = token.next().unwrap();
        let att = token.next().unwrap().parse::<u32>().unwrap();
        let def = token.next().unwrap().parse::<u32>().unwrap();
        let hp = token.next().unwrap().parse::<u32>().unwrap();
        let exp = token.next().unwrap().parse::<u32>().unwrap();
        let monster_tile = &mut map.tiles[monster_y][monster_x];
        if let MapTileType::Monster { detail: monster } = monster_tile {
            *monster = Monster {
                name: monster_name,
                is_boss: false,
                attack_power: att,
                defense_power: def,
                max_hp: hp,
                hp: hp,
                exp: exp,
            };
        } else if let MapTileType::BossMonster { detail: monster } = monster_tile {
            *monster = Monster {
                name: monster_name,
                is_boss: true,
                attack_power: att,
                defense_power: def,
                max_hp: hp,
                hp: hp,
                exp: exp,
            };
        }
    }

    for _ in 0..number_of_item_boxes {
        let y = token.next().unwrap().parse::<usize>().unwrap() - 1;
        let x = token.next().unwrap().parse::<usize>().unwrap() - 1;
        let item_type = token.next().unwrap().parse::<char>().unwrap();
        match item_type {
            'W' => {
                let att = token.next().unwrap().parse::<u32>().unwrap();
                map.tiles[y][x] = MapTileType::ItemBox {
                    item: ItemType::Weapon { attack_power: att },
                };
            }
            'A' => {
                let def = token.next().unwrap().parse::<u32>().unwrap();
                map.tiles[y][x] = MapTileType::ItemBox {
                    item: ItemType::Armor { defense_power: def },
                };
            }
            'O' => {
                let enchant = token.next().unwrap();
                if enchant.eq("HR") {
                    map.tiles[y][x] = MapTileType::ItemBox {
                        item: ItemType::Ornament {
                            enchant: (ItemEnchant::HpRegeneration),
                        },
                    };
                } else if enchant.eq("RE") {
                    map.tiles[y][x] = MapTileType::ItemBox {
                        item: ItemType::Ornament {
                            enchant: (ItemEnchant::Reincarnation),
                        },
                    };
                } else if enchant.eq("CO") {
                    map.tiles[y][x] = MapTileType::ItemBox {
                        item: ItemType::Ornament {
                            enchant: (ItemEnchant::Courage),
                        },
                    };
                } else if enchant.eq("EX") {
                    map.tiles[y][x] = MapTileType::ItemBox {
                        item: ItemType::Ornament {
                            enchant: (ItemEnchant::Experience),
                        },
                    };
                } else if enchant.eq("DX") {
                    map.tiles[y][x] = MapTileType::ItemBox {
                        item: ItemType::Ornament {
                            enchant: (ItemEnchant::Dexterity),
                        },
                    };
                } else if enchant.eq("HU") {
                    map.tiles[y][x] = MapTileType::ItemBox {
                        item: ItemType::Ornament {
                            enchant: (ItemEnchant::Hunter),
                        },
                    };
                } else if enchant.eq("CU") {
                    map.tiles[y][x] = MapTileType::ItemBox {
                        item: ItemType::Ornament {
                            enchant: (ItemEnchant::Cursed),
                        },
                    };
                }
            }
            _ => (),
        }
    }

    let mut player = Player::default_player();
    let mut passed_turn = 0u32;
    for current_move in player_move.chars() {
        let mut next_x = map.player_x;
        let mut next_y = map.player_y;
        match current_move {
            'U' => {
                if map.player_y > 0 {
                    next_y -= 1;
                }
            }
            'R' => {
                if map.player_x + 1 < map.width as u32 {
                    next_x += 1;
                }
            }
            'D' => {
                if map.player_y + 1 < map.height as u32 {
                    next_y += 1;
                }
            }
            'L' => {
                if map.player_x > 0 {
                    next_x -= 1;
                }
            }
            _ => (),
        }
        if let MapTileType::Wall = &mut map.tiles[next_y as usize][next_x as usize] {
            next_x = map.player_x;
            next_y = map.player_y;
        }

        let current_tile = &mut map.tiles[map.player_y as usize][map.player_x as usize];
        if let MapTileType::SpikeTrap { is_player_on } = current_tile {
            *is_player_on = false;
        } else {
            *current_tile = MapTileType::Empty;
        }

        let mut new_tile = &mut map.tiles[next_y as usize][next_x as usize];
        match new_tile {
            MapTileType::Player | MapTileType::Wall | MapTileType::Empty => {}
            MapTileType::SpikeTrap { is_player_on } => {
                match player.take_spike_damage_and_poll_reincarnation() {
                    TakeDamageResult::Alive => {
                        *is_player_on = true;
                    }
                    TakeDamageResult::Dead => {
                        *is_player_on = false;
                    }
                    TakeDamageResult::Reincarnated => {
                        *is_player_on = false;
                        next_x = map.player_start_x;
                        next_y = map.player_start_y;
                        new_tile = &mut map.tiles[next_y as usize][next_x as usize];
                    }
                }
            }
            MapTileType::ItemBox { item } => {
                player.equip_item(item);
            }
            MapTileType::Monster { detail: monster } => {
                match player.fight_and_poll_events(monster) {
                    TakeDamageResult::Alive | TakeDamageResult::Dead => {}
                    TakeDamageResult::Reincarnated => {
                        next_x = map.player_start_x;
                        next_y = map.player_start_y;
                        new_tile = &mut map.tiles[next_y as usize][next_x as usize];
                    }
                }
            }
            MapTileType::BossMonster { detail: monster } => {
                match player.fight_and_poll_events(monster) {
                    TakeDamageResult::Alive => {
                        map.is_boss_dead = true;
                    }
                    TakeDamageResult::Dead => {}
                    TakeDamageResult::Reincarnated => {
                        next_x = map.player_start_x;
                        next_y = map.player_start_y;
                        new_tile = &mut map.tiles[next_y as usize][next_x as usize];
                    }
                }
            }
        }

        passed_turn += 1;

        if player.is_alive() {
            map.player_x = next_x;
            map.player_y = next_y;
            if let MapTileType::SpikeTrap { is_player_on: _ } = new_tile {
            } else {
                *new_tile = MapTileType::Player;
            }

            if map.is_boss_dead {
                map.print_map();
                println!("Passed Turns : {}", passed_turn);
                player.print_status();
                println!("YOU WIN!");
                break;
            }
        } else {
            let dead_reason: &str;
            if let MapTileType::SpikeTrap { is_player_on: _ } = new_tile {
                dead_reason = "SPIKE TRAP";
            } else if let MapTileType::Monster { detail: monster } = new_tile {
                dead_reason = monster.name;
            } else if let MapTileType::BossMonster { detail: monster } = new_tile {
                dead_reason = monster.name;
            } else {
                dead_reason = "ERROR";
            }

            map.print_map();
            println!("Passed Turns : {}", passed_turn);
            player.print_status();
            println!("YOU HAVE BEEN KILLED BY {}..", dead_reason);
            break;
        }
    }

    if player.is_alive() && !map.is_boss_dead {
        map.print_map();
        println!("Passed Turns : {}", passed_turn);
        player.print_status();
        println!("Press any key to continue.");
    }
}
