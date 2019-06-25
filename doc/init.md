Sample init scripts and service configuration for cryptotalkcoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/cryptotalkcoind.service:    systemd service unit configuration
    contrib/init/cryptotalkcoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/cryptotalkcoind.openrcconf: OpenRC conf.d file
    contrib/init/cryptotalkcoind.conf:       Upstart service configuration file
    contrib/init/cryptotalkcoind.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "cryptotalkcoin" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes cryptotalkcoind will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, cryptotalkcoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, cryptotalkcoind will shut down promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that cryptotalkcoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If cryptotalkcoind is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running cryptotalkcoind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `share/examples/cryptotalkcoin.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/cryptotalkcoind`  
Configuration file:  `/etc/cryptotalkcoin/cryptotalkcoin.conf`  
Data directory:      `/var/lib/cryptotalkcoind`  
PID file:            `/var/run/cryptotalkcoind/cryptotalkcoind.pid` (OpenRC and Upstart) or `/run/cryptotalkcoind/cryptotalkcoind.pid` (systemd)
Lock file:           `/var/lock/subsys/cryptotalkcoind` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the cryptotalkcoin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
cryptotalkcoin user and group.  Access to cryptotalkcoin-cli and other cryptotalkcoind rpc clients
can then be controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the cryptotalkcoin group
access to files under it _if_ the files themselves give permission to the
cryptotalkcoin group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/cryptotalkcoin/cryptotalkcoin.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/cryptotalkcoin/cryptotalkcoin.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `CRYPTOTALKCOIND_DATADIR` for
OpenRC).

### macOS

Binary:              `/usr/local/bin/cryptotalkcoind`  
Configuration file:  `~/Library/Application Support/Cryptotalkcoin/cryptotalkcoin.conf`  
Data directory:      `~/Library/Application Support/Cryptotalkcoin`  
Lock file:           `~/Library/Application Support/Cryptotalkcoin/.lock`  

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start cryptotalkcoind` and to enable for system startup run
`systemctl enable cryptotalkcoind`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename cryptotalkcoind.openrc to cryptotalkcoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/cryptotalkcoind start` and configure it to run on startup with
`rc-update add cryptotalkcoind`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop cryptotalkcoind.conf in /etc/init.  Test by running `service cryptotalkcoind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy cryptotalkcoind.init to /etc/init.d/cryptotalkcoind. Test by running `service cryptotalkcoind start`.

Using this script, you can adjust the path and flags to the cryptotalkcoind program by
setting the CRYPTOTALKCOIND and FLAGS environment variables in the file
/etc/sysconfig/cryptotalkcoind. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.cryptotalkcoin.cryptotalkcoind.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.cryptotalkcoin.cryptotalkcoind.plist`.

This Launch Agent will cause cryptotalkcoind to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run cryptotalkcoind as the current user.
You will need to modify org.cryptotalkcoin.cryptotalkcoind.plist if you intend to use it as a
Launch Daemon with a dedicated cryptotalkcoin user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
