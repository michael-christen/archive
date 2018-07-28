define dev::git_config (
	$key = $name,
	$ensure = 'present',
  $value,
  $user,
	$home_directory,
) {
	if $ensure == 'absent' {
		# Remove config if absent
		exec { "${user}-git-config-${key}":
			command => "git config --global --unset ${key}",
			unless  => "test ! $(git config --global --get ${key})",
			user    => $user,
			group   => $user,
			environment => ["HOME=${home_directory}"],
			path    => '/usr/bin/:/bin/',
			require => Class['git'],
		}
  } else {
		exec { "${user}-git-config-${key}":
			command => "git config --global ${key} \"${value}\"",
			unless  => "test \"$(git config --global --get ${key})\" = \"${value}\"",
			user    => $user,
			group   => $user,
			environment => ["HOME=${home_directory}"],
			path    => '/usr/bin/:/bin/',
			require => Class['git'],
		}
	}
}
