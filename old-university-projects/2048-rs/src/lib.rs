#![feature(io)]

extern crate rand;

use rand::Rng;
use std::io::{self, Read, Write};

static BOARD_SIZE: u8 = 4;

struct Board {}

pub fn run() {
    generate_board();
}

fn get_empty_cells(board: &Vec<u32>) -> Vec<u32> {
    let mut empty_cells: Vec<u32> = Vec::new();
    for i in 0..board.len() {
        if board[i] == 0 {
            empty_cells.push(i);
        }
    }
    return empty_cells;
}

fn get_empty_position(empty_cells: &Vec<u32>) -> u32 {
    let rand_choice = rand::thread_rng().gen_range(0, empty_cells.len());
    return empty_cells[rand_choice];
}

fn spawn_new_number() -> u32 {
    let four_spawner_raw = rand::thread_rng().gen_range(0, 6);
    if four_spawner_raw > 4 {
        return 4;
    } else {
        return 2;
    }
}

fn generate_board() {
    let cell_count: u16 = (BOARD_SIZE as u16).pow(2);
    let mut board: Vec<u32> = vec![0; cell_count as usize];

    for i in 0..2 {}

    render_board(game_data, 'x');
}

fn render_board(game_data: Vec<u32>, movement: char) {
    let mut counter = 0;

    if movement == 'w' {}

    for i in 0..game_data.len() {
        if counter == BOARD_SIZE {
            print!("\n");
            counter = 0;
        }
        counter += 1;

        if game_data[i as usize] != 0 {
            print!("{}", game_data[i as usize].to_string());
        } else {
            print!(".");
        }
        io::stdout().flush();
    }
}
