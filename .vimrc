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

"copy to / paste from /tmp/vimcpbuf
"vnoremap y "+y:new +0put\ +<CR>G"_dd:wq! /tmp/vimcpbuf<CR>
"vnoremap d "+d:new +0put\ +<CR>G"_dd:wq! /tmp/vimcpbuf<CR>
"nnoremap yy "+yy:new +0put\ +<CR>G"_dd:wq! /tmp/vimcpbuf<CR>
"nnoremap dd "+dd:new +0put\ +<CR>G"_dd:wq! /tmp/vimcpbuf<CR>
"nnoremap p :r! cat /tmp/vimcpbuf<CR>

":vmap <silent> ,y "xy<CR>:wviminfo! ~/.viminfo
":nmap <silent> ,p :rviminfo! ~/.viminfo<CR>"xp
