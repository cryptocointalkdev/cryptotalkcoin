#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

CRYPTOTALKCOIND=${CRYPTOTALKCOIND:-$BINDIR/cryptotalkcoind}
CRYPTOTALKCOINCLI=${CRYPTOTALKCOINCLI:-$BINDIR/cryptotalkcoin-cli}
CRYPTOTALKCOINTX=${CRYPTOTALKCOINTX:-$BINDIR/cryptotalkcoin-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/cryptotalkcoin-wallet}
CRYPTOTALKCOINQT=${CRYPTOTALKCOINQT:-$BINDIR/qt/cryptotalkcoin-qt}

[ ! -x $CRYPTOTALKCOIND ] && echo "$CRYPTOTALKCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($CRYPTOTALKCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for cryptotalkcoind if --version-string is not set,
# but has different outcomes for cryptotalkcoin-qt and cryptotalkcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$CRYPTOTALKCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $CRYPTOTALKCOIND $CRYPTOTALKCOINCLI $CRYPTOTALKCOINTX $WALLET_TOOL $CRYPTOTALKCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
