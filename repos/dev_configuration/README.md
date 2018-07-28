# dev_configuration
Puppet Manifest to apply locally to setup standard development environment

## Usage

```sh
puppet module install puppetlabs-git --version 0.5.0
puppet module install puppetlabs-concat
puppet module install frozenfoxx-vundle
git clone git@github.com:michael-christen/dev_configuration.git
cd dev_configuration
puppet apply manifests/site.pp --modulepath=modules/:~/.puppetlabs/etc/code/modules  # TBD whether this works
```
Should probably run with `sudo` also the modulepath is a bit weird and should probably be different for `sudo`.

Alright, this ^ is better than nothing.
