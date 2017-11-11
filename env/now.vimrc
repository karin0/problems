set laststatus=2
set noshowmode

syntax enable
set mouse=a
set history=700
set nu
set ruler
set t_vb=

set autoread
set autowrite

set ci
set ai
set si

set ignorecase
set hlsearch
set incsearch 
set showmatch

set expandtab
set smarttab
set shiftwidth=4
set tabstop=4

au FocusLost * silent! wa
au InsertLeave * silent! wa

nmap ; :
imap <PAGEUP> (
imap <PAGEDOWN> )

if has('win32')
    set guifont=Consolas:h17
    set backspace=indent,eol,start
    nmap <F4> :!g++ % -O2 -Wall -Wshadow -o ./a.exe<CR>
    nmap <F5> :!g++ % -O2 -Wall -Wshadow -o ./a.exe && ./a.exe<CR>
    nmap <F6> :!python -i %<CR>
    nmap <F7> :!g++ % -g -Wall -Wshadow -o ./a.exe && gdb a.exe<CR>
    nmap <F8> :!type % \| clip<CR>
else
    set encoding=utf8
    set guifont=Monaco\ 17
    nmap <F4> :!g++ % -O2 -Wall -Wshadow -o ./a.ao<CR>
    nmap <F5> :!g++ % -O2 -Wall -Wshadow -o ./a.ao && ./a.ao<CR>
    nmap <F6> :!python3 -i %<CR>
    nmap <F7> :!g++ % -g -Wall -Wshadow -o ./a.ao && gdb a.ao<CR>
    nmap <F8> ggVG"+y<CR>
    nmap <F9> :!python -i %<CR>
    nmap <F10> :!lua5.3 %<CR>
endif

syntax enable
set background=dark
colorscheme solarized
" colorscheme desert
