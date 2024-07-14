use std::collections::HashMap;
use std::io::{stdin, Read};

/*
 * 많이 틀린 이유: cash의 범위가 u32를 벗어남 -> cash와 관련된 연산 수행시 u64로 바꿔서 수행 필요.
 */

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut tokens = input.split_ascii_whitespace();

    let number_of_company = tokens.next().unwrap().parse::<u32>().unwrap();
    let mut cash = tokens.next().unwrap().parse::<u64>().unwrap();
    let number_of_lines = tokens.next().unwrap().parse::<u32>().unwrap();

    let mut portfolio = HashMap::<&str, u32>::new();
    let mut stock_price = HashMap::<&str, u64>::new();
    let mut company_group = HashMap::<u32, Vec<&str>>::new();
    for _ in 0..number_of_company {
        let group_id = tokens.next().unwrap().parse::<u32>().unwrap();
        let company_name = tokens.next().unwrap();
        let price = tokens.next().unwrap().parse::<u64>().unwrap();

        portfolio.insert(company_name, 0);
        stock_price.insert(company_name, price);
        match company_group.get_mut(&group_id) {
            Some(v) => v.push(company_name),
            None => {
                company_group.insert(group_id, vec![company_name]);
            }
        }
    }

    for _ in 0..number_of_lines {
        let action = tokens.next().unwrap().parse::<u32>().unwrap();
        match action {
            1 => {
                let company_name = tokens.next().unwrap();
                let try_amount = tokens.next().unwrap().parse::<u32>().unwrap();

                let needed_cash = try_amount as u64 * *stock_price.get(company_name).unwrap();
                if cash >= needed_cash {
                    cash -= needed_cash;
                    *portfolio.get_mut(company_name).unwrap() += try_amount;
                }
            }
            2 => {
                let company_name = tokens.next().unwrap();
                let try_amount = tokens.next().unwrap().parse::<u32>().unwrap();
                let rportfolio_count = portfolio.get_mut(company_name).unwrap();
                let can_sell_amount = std::cmp::min(*rportfolio_count, try_amount);

                cash += can_sell_amount as u64 * *stock_price.get(company_name).unwrap();
                *rportfolio_count -= can_sell_amount;
            }
            3 => {
                let company_name = tokens.next().unwrap();
                let rise_or_fall_amount = tokens.next().unwrap().parse::<i64>().unwrap();

                let rprice = stock_price.get_mut(company_name).unwrap();
                *rprice = rprice.saturating_add_signed(rise_or_fall_amount);
            }
            4 => {
                let group_id = tokens.next().unwrap().parse::<u32>().unwrap();
                let rise_or_fall_amount = tokens.next().unwrap().parse::<i64>().unwrap();

                for company_name in company_group.get(&group_id).unwrap() {
                    let rprice = stock_price.get_mut(company_name).unwrap();
                    *rprice = rprice.saturating_add_signed(rise_or_fall_amount);
                }
            }
            5 => {
                let group_id = tokens.next().unwrap().parse::<u32>().unwrap();
                let rise_or_fall_ratio = tokens.next().unwrap().parse::<i64>().unwrap();

                for company_name in company_group.get(&group_id).unwrap() {
                    let rprice = stock_price.get_mut(company_name).unwrap();
                    let old_price: u64 = *rprice as u64;
                    let new_price = old_price * (100u64.saturating_add_signed(rise_or_fall_ratio));

                    *rprice = (new_price / 100 / 10) * 10;
                }
            }
            6 => {
                println!("{cash}");
            }
            7 => {
                let mut temp_cash = cash;
                for (company_name, amount) in &portfolio {
                    temp_cash += *stock_price.get(company_name).unwrap() as u64 * *amount as u64;
                }
                println!("{temp_cash}");
            }
            _ => (),
        }
    }
}
