set history=700
set nu
set mouse=a
set autoread
set autowrite
set ruler
set ignorecase
set smartcase
set hlsearch
set incsearch 
set showmatch
set t_vb=
syntax enable
filetype indent on
set ai
set si
colorscheme desert
set background=dark
set encoding=utf8
set nobackup
set noswapfile
set expandtab
set smarttab
set shiftwidth=4
set tabstop=4
nmap ; :
au FocusLost * silent! wa
au InsertLeave * silent! wa
nnoremap <F5> :!g++ % -g -Wall -o ~/a.ao && clear && ~/a.ao<CR>
