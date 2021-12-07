#![no_std]
#![no_main]
#![feature(alloc)]

extern crate alloc;

#[macro_use]
extern crate rcore_user;
use rcore_user::io::get_line;

#[no_mangle]
pub fn main() {
    let mut history = alloc::vec::Vec::new();
    print!("arm or disarm [arm/disarm]: ");
    let op = get_line(&mut history);
    match op.as_str() {
        "arm" => {
            print!("enter the address to hook: 0x");
            let addr = get_line(&mut history);
            let prog = include_bytes!("hello.bin");
            if rcore_user::syscall::sys_register_ebpf(
                usize::from_str_radix(&addr, 16).unwrap(),
                prog as *const u8,
                prog.len(),
            ) == 0
            {
                println!("hook successful");
            } else {
                println!("hook failed");
            }
        }
        "disarm" => {
            print!("enter the address to unhook: 0x");
            let addr = get_line(&mut history);
            if rcore_user::syscall::sys_unregister_ebpf(usize::from_str_radix(&addr, 16).unwrap())
                == 0
            {
                println!("unhook successful");
            } else {
                println!("unhook failed");
            }
        }
        _ => {
            println!("unknown operation: {}, exiting", op);
        }
    }
}
