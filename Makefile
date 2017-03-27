ARGS=

all:
	@# Pass in home directory to puppet
	@# There's probably a better way of doing this.
	@export FACTER_home_directory=~
	puppet apply --modulepath ./modules manifests/site.pp $(ARGS)
