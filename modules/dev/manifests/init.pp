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
	dev::git_config { 'core.editor':
		value					 => 'vim',
		user           => $user,
		home_directory => $home_directory,
	}
  dev::git_config { 'alias.st':
	  value          => 'status --short --branch',
    user            => $user,
		home_directory => $home_directory,
	}
  dev::git_config { 'alias.ci':
	  value => 'commit',
    user => $user,
		home_directory => $home_directory,
	}
  dev::git_config { 'alias.br':
	  value => 'branch',
    user => $user,
		home_directory => $home_directory,
	}
  dev::git_config { 'alias.co':
	  value => 'checkout',
    user => $user,
		home_directory => $home_directory,
	}
  dev::git_config { 'alias.lo':
	  value => 'log --oneline',
    user => $user,
		home_directory => $home_directory,
	}
  dev::git_config { 'alias.log-detail':
	  value => 'log -p',
    user => $user,
		home_directory => $home_directory,
	}
  dev::git_config { 'alias.graph':
	  value => 'log --graph --oneline --all',
    user => $user,
		home_directory => $home_directory,
	}
  # Force push, but stop from overwriting future state
  dev::git_config { 'alias.please':
	  value => 'push --force-with-lease',
    user => $user,
		home_directory => $home_directory,
	}
  # Add file to previous commit
  dev::git_config { 'alias.commend':
	  value => 'commit --amend --no-edit',
    user => $user,
		home_directory => $home_directory,
	}
	# Only unstaged changes
  dev::git_config { 'alias.stsh':
		value => 'stash --keep-index',
    user => $user,
		home_directory => $home_directory,
  }
	# untracked & tracked
  dev::git_config { 'alias.staash':
		value => 'stash --include-untracked',
    user => $user,
		home_directory => $home_directory,
  }
	# ignored, untracked, tracked
  dev::git_config { 'alias.staaash':
		value => 'stash --all',
    user => $user,
		home_directory => $home_directory,
  }
  # Sweet graph
  dev::git_config { 'alias.grog':
		value => 'log --graph --oneline --abbrev-commit --decorate --all',
    user => $user,
		home_directory => $home_directory,
  }
  # # Clean merged branches from repo
  # dev::git_config { 'alias.clean-remote':
	# 	value => "!for b in \\$(git br -r --merged master); do echo \\$b | awk '{split(\$0,a,\"/\"); print a[2]}' | xargs git push origin --delete; done",
  #   user => $user,
	# 	home_directory => $home_directory,
  # }
  # dev::git_config { 'alias.list-remote':
	# 	value => "!for b in \\$(git br -r --merged master); do echo \\$(b) | awk '{split(\$0,a,\"/\"); print a[2]}'; done",
  #   user => $user,
	# 	home_directory => $home_directory,
  # }
  dev::git_config { 'alias.clean-local':
		value => "!git br --merged master | grep -v master | xargs git br -d",
    user => $user,
		home_directory => $home_directory,
  }
  dev::git_config { 'alias.list-local':
		value => "!git br --merged master | grep -v master",
    user => $user,
		home_directory => $home_directory,
  }
}
