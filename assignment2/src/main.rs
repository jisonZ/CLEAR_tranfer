use rand::Rng;
use std::io;

fn printCards(card: &Vec<i32>) {
    for c in card {
        print!("{c} ");
    }
}

fn main() {
    
    println!("The BlackJack Game has begin!\n");
    // initialize dealer cards
    let mut dealer = Vec::new();
    let mut rng = rand::thread_rng();
    dealer.push(rng.gen_range(1..12));
    dealer.push(rng.gen_range(1..12));
    let dealer_sum = dealer[0] + dealer[1];
    // initialize user cards
    let mut user = Vec::new();
    user.push(rng.gen_range(1..12));
    user.push(rng.gen_range(1..12));
    let mut user_sum = user[0] + user[1];

    // display user cards
    println!("Your Cards are");
    printCards(&user);
    println!("\nHit(h) or Stand(s)?");

    let mut user_input = String::new();
    let stdin = io::stdin(); // We get `Stdin` here.
    stdin.read_line(&mut user_input);

    while (user_input.trim() == String::from("h")) {
        user_input.clear();
        let nxt_card = rng.gen_range(1..12);
        user_sum += nxt_card;
        user.push(nxt_card);

        // display user cards
        println!("Your Cards are");
        printCards(&user);

        // bust condition
        if (user_sum > 21) {
            println!("\nBUST! You lose");
            return;
        }
        println!("\nHit(h) or Stand(s)?");
        stdin.read_line(&mut user_input);
    }

    println!("The Dealers Cards are:");
    printCards(&dealer);
    println!("\nDealer Card Sum to {dealer_sum}");
    println!("The Users Cards are:");
    printCards(&user);
    println!("\nYour Card Sum to {user_sum}");

    if (21-dealer_sum <= 21-user_sum) {
        println!("Dealer Wins!");
    } else {
        println!("You Win!");
    }

}
