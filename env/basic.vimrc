set mouse=a
set history=700
set nu
set ruler
set autoread
set ignorecase
set si
set sta
set et
set sw=4
set ts=4
set sts=4
nmap ; :
imap {<CR> {<ESC>o}<ESC>O
autocmd FileType cpp nmap <F4> :!g++ % -O2 -Wall -Wshadow -o ./a.ao <CR>
autocmd FileType cpp nmap <F5> :!g++ % -O2 -Wall -Wshadow -o ./a.ao && ./a.ao <CR>
autocmd FileType cpp nmap <F7> :!g++ % -Og -g -Wall -Wshadow -o ./a.ao && gdb a.ao <CR>
