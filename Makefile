ARGS=

all:
	@# Pass in home directory to puppet
	@# There's probably a better way of doing this.
	@export FACTER_user=$(USER)
	puppet apply manifests/site.pp $(ARGS)
