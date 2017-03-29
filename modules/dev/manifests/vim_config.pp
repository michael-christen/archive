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
  # Add root editor config to home directory
  file { "${home_directory}/.editorconfig":
    ensure  => file,
    owner   => $user,
    group   => $user,
    mode    => '0644',
    content => template('dev/editorconfig.erb'),
  }
}
