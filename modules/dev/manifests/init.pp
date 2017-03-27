class dev(
  $home_directory = $dev::params::home_directory
) inherits dev::params {
  # Demonstrate passing in home_directory
  notice("Hello ${home_directory}")
  file { '/tmp/hw':
      ensure => present,
      mode   => '0777',
      content => 'hello mike',
  }
}
