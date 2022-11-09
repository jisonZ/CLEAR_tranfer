use std::io;
// mod print;

fn main() {
    // print::run();
    println!("How old r u");
    let mut user_input = String::new();
    let stdin = io::stdin(); // We get `Stdin` here.
    stdin.read_line(&mut user_input);
    println!("first input {}", user_input);

    let mut second_user_input = String::new();
    if user_input == String::from("0\n") {
        println!("really, how old are you");
        let stdin = io::stdin(); // We get `Stdin` here.
        stdin.read_line(&mut second_user_input);
        println!("second input {}", second_user_input);
        if second_user_input == "1\n" {
            println!("you lied, DIE");
        } else {
            println!("good boi");
        }
    } else {
        println!("Good, now how old is I");
        let stdin = io::stdin(); // We get `Stdin` here.
        stdin.read_line(&mut second_user_input);
        if second_user_input == "1" {
            println!("good guess, but no, DIE");
        } else {
            println!("That's right, good for u");
        }
    }
}
