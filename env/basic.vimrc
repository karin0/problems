set mouse=a
set hi=1000
set nu
set ru
set ar
set ic
set si
set sta
set et
set sw=4
set ts=4
set sts=4
nmap ; :
imap {<CR> {<ESC>o}<ESC>O
nmap <F4> :!g++ % -DAKARI -O3 -Wall -Wextra -o ./a.ao <CR>
nmap <F5> :!g++ % -DAKARI -O3 -Wall -Wextra -o ./a.ao && ./a.ao <CR>
nmap <F7> :!g++ % -DAKARI -Og -g -Wall -Wextra -o ./a.ao && gdb a.ao <CR>
