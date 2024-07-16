/*
 * Struct를 안 써서 코드가 더러움
 * 사실 그냥 코드가 더러움...
 */

use std::{
    io::{stdin, Read},
    process::exit,
    str::SplitAsciiWhitespace,
};

const NUMBER_OF_SPECIAL_TILES: usize = 4;

enum GoldenCard {
    Saving { amount: u32 },
    Withdraw { amount: u32 },
    Donation { amount: u32 },
    Moving { amount: u32 },
}

enum TileType {
    Start,
    Island,
    Welfare,
    Tesla,
    GoldenCard,
    Normal { price: u32 },
}

fn move_and_poll_salary(
    current_location: &mut u32,
    move_count: u32,
    cash: &mut u32,
    number_of_tiles: usize,
    salary: u32,
) {
    *current_location += move_count;
    while *current_location >= number_of_tiles as u32 {
        *current_location -= number_of_tiles as u32;
        *cash += salary;
    }
}

// Every calling this function can be replaced by "if cash >= amount".
// But I used match and u32::checked_sub because I wanna try to use rust's features.
fn pay_cash_and_check_lose(cash: &mut u32, amount: u32) {
    match cash.checked_sub(amount) {
        Some(new_cash) => {
            *cash = new_cash;
        }
        None => {
            println!("LOSE");
            exit(0);
        }
    }
}

fn poll_map_event(
    token: &mut SplitAsciiWhitespace,
    current_location: &mut u32,
    cash: &mut u32,
    salary: u32,
    welfare_balance: &mut u32,
    number_of_left_normal_tiles: &mut usize,
    current_golden_card_location: &mut u32,
    tiles: &Vec<TileType>,
    number_of_tiles: usize,
    tiles_need_to_buy: &mut Vec<bool>,
    golden_cards: &Vec<GoldenCard>,
    number_of_golden_card: usize,
) {
    match tiles[*current_location as usize] {
        TileType::Start => (),
        TileType::Island => {
            for _ in 0..3 {
                let d1;
                match token.next() {
                    // Consider when game is over at island. I think this is not good but it's convenient.
                    Some(x) => {
                        d1 = x.parse::<u32>().unwrap();
                    }
                    None => {
                        return;
                    }
                }
                let d2 = token.next().unwrap().parse::<u32>().unwrap();
                if d1 == d2 {
                    break;
                }
            }
        }
        TileType::Welfare => {
            *cash += *welfare_balance;
            *welfare_balance = 0;
        }
        TileType::Tesla => {
            *current_location = 0;
            *cash += salary;
        }
        TileType::GoldenCard => {
            match golden_cards[*current_golden_card_location as usize] {
                GoldenCard::Saving { amount } => {
                    pay_cash_and_check_lose(cash, amount);
                }
                GoldenCard::Withdraw { amount } => {
                    *cash += amount;
                }
                GoldenCard::Donation { amount } => {
                    pay_cash_and_check_lose(cash, amount);
                    *welfare_balance += amount;
                }
                GoldenCard::Moving { amount } => {
                    move_and_poll_salary(current_location, amount, cash, number_of_tiles, salary);
                    poll_map_event(
                        token,
                        current_location,
                        cash,
                        salary,
                        welfare_balance,
                        number_of_left_normal_tiles,
                        current_golden_card_location,
                        tiles,
                        number_of_tiles,
                        tiles_need_to_buy,
                        golden_cards,
                        number_of_golden_card,
                    );
                }
            }
            *current_golden_card_location += 1;
            if *current_golden_card_location >= number_of_golden_card as u32 {
                *current_golden_card_location = 0;
            }
        }
        TileType::Normal { price } => {
            if tiles_need_to_buy[*current_location as usize] && *cash >= price {
                *cash -= price;
                tiles_need_to_buy[*current_location as usize] = false;
                *number_of_left_normal_tiles -= 1;
            }
        }
    }
}

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut token = input.split_ascii_whitespace();

    let n = token.next().unwrap().parse::<usize>().unwrap();
    let number_of_tiles = 4 * n - 4;
    let mut cash = token.next().unwrap().parse::<u32>().unwrap();
    let salary = token.next().unwrap().parse::<u32>().unwrap();
    let number_of_golden_card = token.next().unwrap().parse::<usize>().unwrap();

    let mut current_location = 0u32;
    let mut welfare_balance = 0u32;

    let mut golden_cards = Vec::<GoldenCard>::with_capacity(number_of_golden_card);
    for _ in 0..number_of_golden_card {
        let card_type = token.next().unwrap().parse::<u32>().unwrap();
        let arg = token.next().unwrap().parse::<u32>().unwrap();
        match card_type {
            1 => {
                golden_cards.push(GoldenCard::Withdraw { amount: arg });
            }
            2 => {
                golden_cards.push(GoldenCard::Saving { amount: arg });
            }
            3 => {
                golden_cards.push(GoldenCard::Donation { amount: arg });
            }
            4 => {
                golden_cards.push(GoldenCard::Moving { amount: arg });
            }
            _ => {
                assert!(false);
            }
        }
    }
    assert_eq!(number_of_golden_card, golden_cards.len());

    let mut tiles = Vec::<TileType>::with_capacity(number_of_tiles);
    let mut tiles_need_to_buy = Vec::<bool>::with_capacity(number_of_tiles);
    let mut number_of_golden_tiles = 0usize;
    for i in 0..number_of_tiles {
        if i == 0 {
            tiles.push(TileType::Start);
            tiles_need_to_buy.push(false);
        } else if i == n - 1 {
            tiles.push(TileType::Island);
            tiles_need_to_buy.push(false);
        } else if i == 2 * n - 2 {
            tiles.push(TileType::Welfare);
            tiles_need_to_buy.push(false);
        } else if i == 3 * n - 3 {
            tiles.push(TileType::Tesla);
            tiles_need_to_buy.push(false);
        } else {
            let specifier = token.next().unwrap().parse::<char>().unwrap();
            match specifier {
                'G' => {
                    number_of_golden_tiles += 1;
                    tiles.push(TileType::GoldenCard);
                    tiles_need_to_buy.push(false);
                }
                'L' => {
                    let tile_price = token.next().unwrap().parse::<u32>().unwrap();
                    tiles.push(TileType::Normal { price: tile_price });
                    tiles_need_to_buy.push(true);
                }
                _ => {
                    assert!(false);
                }
            }
        }
    }
    assert_eq!(number_of_tiles, tiles.len());
    assert_eq!(number_of_tiles, tiles_need_to_buy.len());

    let mut current_golden_card_location = 0u32;
    let mut number_of_left_normal_tiles =
        number_of_tiles - number_of_golden_tiles - NUMBER_OF_SPECIAL_TILES;
    assert_eq!(
        number_of_left_normal_tiles,
        tiles_need_to_buy.iter().filter(|&&x| x == true).count()
    );

    let dice_count = token.next().unwrap().parse::<u32>().unwrap();
    // I think it will be better code if I use while and used_dice_count for polling dice.
    for _ in 0..dice_count {
        let d1;
        match token.next() {
            // Consider dice when island. I think this is not good but it's convenient.
            Some(x) => {
                d1 = x.parse::<u32>().unwrap();
            }
            None => {
                break;
            }
        }
        let d2 = token.next().unwrap().parse::<u32>().unwrap();
        let total_value = d1 + d2;

        move_and_poll_salary(
            &mut current_location,
            total_value,
            &mut cash,
            number_of_tiles,
            salary,
        );
        poll_map_event(
            &mut token,
            &mut current_location,
            &mut cash,
            salary,
            &mut welfare_balance,
            &mut number_of_left_normal_tiles,
            &mut current_golden_card_location,
            &tiles,
            number_of_tiles,
            &mut tiles_need_to_buy,
            &golden_cards,
            number_of_golden_card,
        );
    }

    if number_of_left_normal_tiles == 0 {
        println!("WIN");
    } else {
        println!("LOSE");
    }
}
