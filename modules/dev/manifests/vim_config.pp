define dev::vim_config (
  $user,
  $home_directory,
  $plugins = [],
) {
  vundle::installation { $user:
    viminstall => true,
    plugins => $plugins,
  }
  # concat on vundle concat target
  concat::fragment { "${user}-vimrc-custom":
    target => "${user}-vimrc",
    order  => 30,
    content => template('dev/vimrc-custom.erb'),
  }
}
