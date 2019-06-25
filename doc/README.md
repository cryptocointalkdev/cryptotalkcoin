Cryptotalkcoin Core
=============

Setup
---------------------
Cryptotalkcoin Core is the original Cryptotalkcoin client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Cryptotalkcoin transactions, which requires a few hundred gigabytes of disk space. Depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Cryptotalkcoin Core, visit [cryptotalkcoincore.org](https://cryptotalkcoincore.org/en/download/).

Running
---------------------
The following are some helpful notes on how to run Cryptotalkcoin Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/cryptotalkcoin-qt` (GUI) or
- `bin/cryptotalkcoind` (headless)

### Windows

Unpack the files into a directory, and then run cryptotalkcoin-qt.exe.

### macOS

Drag Cryptotalkcoin Core to your applications folder, and then run Cryptotalkcoin Core.

### Need Help?

* See the documentation at the [Cryptotalkcoin Wiki](https://en.cryptotalkcoin.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#cryptotalkcoin](http://webchat.freenode.net?channels=cryptotalkcoin) on Freenode. If you don't have an IRC client, use [webchat here](http://webchat.freenode.net?channels=cryptotalkcoin).
* Ask for help on the [CryptotalkcoinTalk](https://cryptotalkcointalk.org/) forums, in the [Technical Support board](https://cryptotalkcointalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build Cryptotalkcoin Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [FreeBSD Build Notes](build-freebsd.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Gitian Building Guide (External Link)](https://github.com/cryptotalkcoin-core/docs/blob/master/gitian-building.md)

Development
---------------------
The Cryptotalkcoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/cryptotalkcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [CryptotalkcoinTalk](https://cryptotalkcointalk.org/) forums, in the [Development & Technical Discussion board](https://cryptotalkcointalk.org/index.php?board=6.0).
* Discuss project-specific development on #cryptotalkcoin-core-dev on Freenode. If you don't have an IRC client, use [webchat here](http://webchat.freenode.net/?channels=cryptotalkcoin-core-dev).
* Discuss general Cryptotalkcoin development on #cryptotalkcoin-dev on Freenode. If you don't have an IRC client, use [webchat here](http://webchat.freenode.net/?channels=cryptotalkcoin-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [cryptotalkcoin.conf Configuration File](cryptotalkcoin-conf.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)
- [PSBT support](psbt.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
