set nocompatible
set laststatus=2 " Always display the statusline in all windows
set noshowmode

" Specify a directory for plugins
" - For Neovim: ~/.local/share/nvim/plugged
" - Avoid using standard Vim directory names like 'plugin'
call plug#begin('~/.config/nvim/plugged')

Plug 'flazz/vim-colorschemes'
Plug 'octol/vim-cpp-enhanced-highlight'
Plug 'godlygeek/tabular'
Plug 'plasticboy/vim-markdown'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'vim-scripts/fcitx.vim'
" Plug 'jiangmiao/auto-pairs'
Plug 'vim-syntastic/syntastic'
Plug 'chriskempson/base16-vim'
Plug 'noahfrederick/vim-hemisu'
Plug 'scrooloose/nerdcommenter'

" Initialize plugin system
call plug#end()

" execute pathogen#infect()
syntax on
filetype plugin indent on

set nocompatible
set t_Co=256
let g:airline_powerline_fonts = 1 

let g:NERDSpaceDelims = 1

let g:vim_markdown_math = 1
let g:vim_markdown_frontmatter = 1
let g:vim_markdown_toml_frontmatter = 1
let g:vim_markdown_folding_disabled = 1
 
let g:minBufExplForceSyntaxEnable = 1
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
let g:syntastic_quiet_messages = { "type": "style" }
autocmd FileType python let g:syntastic_quiet_messages = { "level": "warning" }

syntax enable
set mouse=a
set history=700
set nu
set ruler
set t_vb=

set autoread
set autowrite

set ignorecase
set hlsearch
set incsearch 
set showmatch

set si
set et
set sta
set sw=4
set ts=4
set sts=4
" set cursorline

au FocusLost * silent! wa
au InsertLeave * silent! wa

let mapleader=','
nmap ; :
nmap <SPACE> :nohl <CR>
nmap ' :w <CR>
vmap / <leader>c<SPACE>gv
vnoremap < <gv
vnoremap > >gv
vnoremap <leader>y "+ygv
vnoremap <leader>p "+pgv
" nmap . <ESC>:%s/。/．/g<CR><ESC>:%s/-- more --/--more--/g<CR>
autocmd FileType c,cc,cpp imap {<CR> {<CR>}<LEFT><CR><UP><TAB>


set encoding=utf8
nmap <F3> :vsp term://zsh <CR>
autocmd FileType cpp nmap <F4> :vsp term://g++ % -O2 -DAKARI -std=c++11 -Wall -Wshadow -o ./a.ao <CR>
autocmd FileType cpp nmap <F5> :vsp term://g++ % -O2 -DAKARI -std=c++11 -Wall -Wshadow -o ./a.ao&&./a.ao <CR>
autocmd FileType cpp nmap <c-F4> :vsp term://g++ % -O2 -DAKARI -Wall -Wshadow -o ./a.ao <CR>
autocmd FileType cpp nmap <c-F5> :vsp term://g++ % -O2 -DAKARI -Wall -Wshadow -o ./a.ao&&./a.ao <CR>
autocmd FileType python  nmap <F5> :vsp term://ipython % <CR>
autocmd FileType python  nmap <F7> :vsp term://ipython % -i <CR>
nmap <F6> :vsp term://ipython -i ~/cfgs/vf6.py <CR>
autocmd FileType cpp nmap <F7> :vsp term://g++ % -g -DAKARI -std=c++11 -Wall -Wshadow -o ./a.ao&&gdb a.ao <CR>
autocmd FileType cpp nmap <c-F7> :vsp term://g++ % -g -DAKARI -Wall -Wshadow -o ./a.ao&&gdb a.ao <CR>
nmap <F8> ggVG"+y

syntax enable
colorscheme solarized
"colorscheme Tomorrow
"colorscheme base16-solarized-light
set background=dark
" colorscheme hemisu
" set clipboard+=unnamedplus
" colorscheme desert
autocmd BufWinEnter,WinEnter term://* startinsert
autocmd BufLeave term://* stopinsert

if filereadable(expand("~/.vimrc_background"))
    let base16colorspace=256
source ~/.vimrc_background
endif

hi Normal ctermbg=NONE
hi Comment ctermfg=6