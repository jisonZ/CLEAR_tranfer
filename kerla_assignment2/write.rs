use super::MAX_READ_WRITE_LEN;
use crate::prelude::*;
use crate::{fs::opened_file::Fd, user_buffer::UserBuffer};
use crate::{process::current_process, syscalls::SyscallHandler};
use core::cmp::min;
use kerla_runtime::address::UserVAddr;

impl<'a> SyscallHandler<'a> {
    pub fn sys_write(&mut self, fd: Fd, uaddr: UserVAddr, len: usize) -> Result<isize> {
        let len = min(len, MAX_READ_WRITE_LEN);

        let opened_file = current_process().get_opened_file_by_fd(fd)?;
        trace!(
            "[{}:{}] write(file={:?}, len={})",
            current_process().pid().as_i32(),
            current_process().cmdline().argv0(),
            opened_file.inode(),
            len
        );

        // -------- SYSCALL: echo --------
        // -------------------------------
        // read bytes from address
        let mut buf_array: [u8; 100] = [0; 100];
        uaddr.read_bytes(&mut buf_array);

        let mut a_string = String::from("");
        for idx in 0..len-1 {
            a_string.push(buf_array[idx] as char);
        }
        // println!("final string:{}", a_string);
        

        let mut split = a_string.as_str().split("_");
        // split string into iterative strings
        let split: Vec<&str> = split.collect();
        let mut v1_iter = split.iter();
        let mut firstVal = v1_iter.next();
        let mut sum = 1;
        if (firstVal.unwrap() == &"add") {
            firstVal = v1_iter.next();
            while (firstVal != None) {
                let cur_val = firstVal.unwrap();
                let my_int: i32 = cur_val.parse::<i32>().unwrap();
                sum += my_int;
                firstVal = v1_iter.next();
            }
            println!("add sum: {}", sum-1);
        }
        // -----------------------------------
        // -------- end SYSCALL: echo --------

        let written_len = opened_file.write(UserBuffer::from_uaddr(uaddr, len))?;

        // MAX_READ_WRITE_LEN limit guarantees total_len is in the range of isize.
        Ok(written_len as isize)
    }
}
