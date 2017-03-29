class dev(
  $user = $dev::params::user,
  $home_directory = $dev::params::home_directory
) inherits dev::params {
  dev::vim_config { "${user}":
    user => $user,
    home_directory => $home_directory,
    plugins  => [
        # General Configuration
        'editorconfig/editorconfig-vim',
        'christoomey/vim-tmux-navigator',
        'altercation/vim-colors-solarized',
        'flazz/vim-colorschemes',

        # 'godlygeek/tabular',
        # tabular must come before vim-markdown
        # 'plasticboy/vim-markdown',

        # Language based plugins
        'nathanielc/vim-tickscript',
        'vimwiki/vimwiki',
        'lepture/vim-jinja',
        'davidhalter/jedi-vim',
        'rust-lang/rust.vim',
        'kchmck/vim-coffee-script',
    ],
  }
}
