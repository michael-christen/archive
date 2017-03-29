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
	include git
  git::config { 'core.editor':
	  value => 'vim',
	}
  # git::config { 'alias.st':
	#   value => 'status --short --branch',
  #   user => $user,
	# }
  # git::config { 'alias.ci':
	#   value => 'commit',
  #   user => $user,
	# }
  # git::config { 'alias.br':
	#   value => 'branch',
  #   user => $user,
	# }
  # git::config { 'alias.co':
	#   value => 'checkout',
  #   user => $user,
	# }
  # git::config { 'alias.lo':
	#   value => 'log --oneline',
  #   user => $user,
	# }
  # git::config { 'alias.log-detail':
	#   value => 'log -p',
  #   user => $user,
	# }
  # git::config { 'alias.graph':
	#   value => 'log --graph --oneline --all',
  #   user => $user,
	# }
  # # Force push, but stop from overwriting future state
  # git::config { 'alias.please':
	#   value => 'push --force-with-lease',
  #   user => $user,
	# }
  # # Add file to previous commit
  # git::config { 'alias.commend':
	#   value => 'commit --amend --no-edit',
  #   user => $user,
	# }
	# # Only unstaged changes
  # git::config { 'stsh':
	# 	value => 'stash --keep-index',
  #   user => $user,
  # }
	# # untracked & tracked
  # git::config { 'staash':
	# 	value => 'stash --include-untracked',
  #   user => $user,
  # }
	# # ignored, untracked, tracked
  # git::config { 'staaash':
	# 	value => 'stash --all',
  #   user => $user,
  # }
  # # Sweet graph
  # git::config { 'grog':
	# 	value => 'log --graph --oneline --abbrev-commit --decorate --all',
  #   user => $user,
  # }
  # # Clean merged branches from repo
  # git::config { 'clean-remote':
	# 	value => "!for b in $(git br -r --merged master); do echo $b | awk '{split($0,a,\"/\"); print a[2]}' | xargs git push origin --delete; done",
  #   user => $user,
  # }
  # git::config { 'list-remote':
	# 	value => "!for b in $(git br -r --merged master); do echo $b | awk '{split($0,a,\"/\"); print a[2]}'; done",
  #   user => $user,
  # }
  # git::config { 'clean-local':
	# 	value => "!git br --merged master | grep -v master | xargs git br -d",
  #   user => $user,
  # }
  # git::config { 'list-local':
	# 	value => "!git br --merged master | grep -v master",
  #   user => $user,
  # }
}
