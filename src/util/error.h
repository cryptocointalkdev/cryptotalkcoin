// Copyright (c) 2010-2018 The Cryptotalkcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CRYPTOTALKCOIN_UTIL_ERROR_H
#define CRYPTOTALKCOIN_UTIL_ERROR_H

/**
 * util/error.h is a common place for definitions of simple error types and
 * string functions. Types and functions defined here should not require any
 * outside dependencies.
 *
 * Error types defined here can be used in different parts of the cryptotalkcoin
 * codebase, to avoid the need to write boilerplate code catching and
 * translating errors passed across wallet/node/rpc/gui code boundaries.
 */

#include <string>

enum class TransactionError {
    OK, //!< No error
    MISSING_INPUTS,
    ALREADY_IN_CHAIN,
    P2P_DISABLED,
    MEMPOOL_REJECTED,
    MEMPOOL_ERROR,
    INVALID_PSBT,
    PSBT_MISMATCH,
    SIGHASH_MISMATCH,
};

std::string TransactionErrorString(const TransactionError error);

std::string AmountHighWarn(const std::string& optname);

std::string AmountErrMsg(const char* const optname, const std::string& strValue);

#endif // CRYPTOTALKCOIN_UTIL_ERROR_H
