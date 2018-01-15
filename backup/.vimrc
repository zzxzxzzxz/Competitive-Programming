syntax on

set undofile

set number
set hlsearch
set background=dark

set tabstop=4
set shiftwidth=4
set smarttab
set expandtab

"un-highlight by space
noremap <silent> <Space> :silent noh<Bar>echo<CR>

"block comment / uncomment map
autocmd FileType cpp vnoremap <C-n> :normal i//<CR>
autocmd FileType cpp vnoremap <C-m> :normal ^x^x<CR>
autocmd FileType python,sh,make vnoremap <C-n> :normal i#<CR>
autocmd FileType python,sh,make vnoremap <C-m> :normal ^x<CR>

"indent for filetypes
autocmd FileType python setlocal smartindent cinwords=if,elif,else,for,while,try,except,finally,def,class,with
autocmd FileType proto setlocal ts=2 sw=2
autocmd FileType make setlocal noexpandtab
autocmd FileType cpp setlocal autoindent smartindent

"last position
autocmd BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

"remove unwanted spaces
autocmd BufWritePre * %s/\s\+$//e

"paste / nopaste
noremap <C-i> :set invpaste paste?<CR>

" clipboard
set clipboard=unnamed
