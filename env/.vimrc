syntax enable
filetype indent on
colorscheme desert
set background=dark

set mouse=a
set history=700
set nu
set ruler
set t_vb=
set encoding=utf8

set autoread
set autowrite

set ai
set si

set ignorecase
set smartcase
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
nmap <F5> :!g++ % -g -Wall -o ./a.ao  && ./a.ao<CR>
