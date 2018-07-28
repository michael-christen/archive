class dev::params {
  $user = 'michael'  # $::user
  # TODO: adjust for Mac
  $base_path = '/home'
  $home_directory = "${base_path}/${user}"
}
