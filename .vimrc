:set number shiftwidth=4 softtabstop=4 expandtab showcmd lazyredraw
:set number shiftwidth=4 softtabstop=4 expandtab showcmd lazyredraw

:let mapleader = "-"

" Write, then quit
:nnoremap <leader>w :w<Enter>:q<Enter>
:nnoremap <leader>q :w<Enter>:q<Enter>

" Prepare to search globally
:nnoremap <leader>s :%s/

" Insert theano.
:nnoremap <leader>t itheano.
:nnoremap <leader>np inumpy.

" Move cursor to the character after the next underscore
:nnoremap <leader>- f_l

" Move cursor to the character after the second next underscore
:nnoremap <leader>= f_f_l

" Highlight all characters before the next underscore
:vnoremap <leader>- f_h

" Highlight all characters before the second next underscore
:vnoremap <leader>= f_f_h

" Edit ~/.vimrc
:nnoremap <leader>rc :sp $MYVIMRC<cr>

" Window navigation
:nnoremap <C-j> <C-W>j
:nnoremap <C-k> <C-W>k
:nnoremap <C-h> <C-W>h
:nnoremap <C-l> <C-W>l

" Insert :nnoremap <leader>
:nnoremap <leader>nl i:nnoremap<Space><leader<Space><Backspace>>

" Activate DOS format for .txt, then write, then quit
:nnoremap <leader>dos :w<Enter>:e<Space>++ff=dos<Enter>:w<Enter>:q<Enter>

" Write, then overwrite vimrc.txt, then quit
:nnoremap <leader>trc :w<Enter>:w!<Space>~/vimrc.txt<Enter>:q<Enter>

" Delete all characters from current position to end of line
" without moving next line
:nnoremap <leader>4d v$hd

" Cut all characters from current position to end of line
" without moving next line
:nnoremap <leader>4x v$hx

" Insert ) before the next whitespace
:nnoremap <leader>) Ea)<Esc>

" Insert ( after the next whitespace
:nnoremap <leader>( Bi(<Esc>

" Write, then suspend Vim
:nnoremap <leader><C-z> :w<Enter><C-z>
